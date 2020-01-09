# Copyright 2018 Google LLC
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.


# i ended up switching my project from node.js to python, because I was having trouble catching if the boat id was valid or not.
# i also had difficulties with getting my client secret setup, so this only works on the gcloud environment, and not on localhost

import datetime

from flask import Flask, render_template, request, json

# [START gae_python37_datastore_store_and_fetch_times]
from google.cloud import datastore

datastore_client = datastore.Client()

# [END gae_python37_datastore_store_and_fetch_times]
app = Flask(__name__)
client = datastore.Client()


# [START gae_python37_datastore_store_and_fetch_times]
def store_time(dt):
    entity = datastore.Entity(key=datastore_client.key('visit'))
    entity.update({
        'timestamp': dt
    })

    datastore_client.put(entity)


def fetch_times(limit):
    query = datastore_client.query(kind='visit')
    query.order = ['-timestamp']

    times = query.fetch(limit=limit)

    return times


# [END gae_python37_datastore_store_and_fetch_times]


# [START gae_python37_datastore_render_times]
@app.route('/')
def root():
    # Store the current access time in Datastore.
    store_time(datetime.datetime.now())

    # Fetch the most recent 10 access times from Datastore.
    times = fetch_times(10)

    return render_template(
        'index.html', times=times)


# [END gae_python37_datastore_render_times]

def validate_boat_create(request):
    return "name" not in request.json or \
            "length" not in request.json or \
            "type" not in request.json

def validate_slip_create(request):
    return "number" not in request.json

# send our post to boats
@app.route('/boats', methods=['POST'])
def boat_create():
	#check if it is a valid request
    if validate_boat_create(request):
        failed = {"Error": "The request object is missing at least one of the required attributes"}
        response = app.response_class(
            response=json.dumps(failed),
            status=400,
            mimetype='application/json'
        ) #close if
        return response

    content = request.get_json()
    mk_new_boat = datastore.entity.Entity(key=client.key("boat"))
	#create new boat in our datastore
    mk_new_boat.update({
        "name": content["name"],
        "length": content["length"],
        "type": content["type"]
    })
    client.put(mk_new_boat)
	# make our url and ID
    mk_new_boat["id"] = mk_new_boat.key.id
    mk_new_boat["self"] = "http://skinnern-cs493-project3.appspot.com/boats/" + str(mk_new_boat.key.id)
	# I couldn't figure out how to get the base url so it would be generic, so I just used a string for it instead
    response = app.response_class(
        response=json.dumps(mk_new_boat),
        status=201,
        mimetype='application/json'
    )
    return response

# get a specific boat
#----------------------------------------------------------------------------------
@app.route('/boats/<id>', methods=['GET'])
def boat_show(id):
    key_for_boat = client.key("boat", int(id))
    boat = client.get(key=key_for_boat)
	#check if it is a valid request
    if boat:
        data = dict(boat)
		# make our url and ID
        data["id"] = boat.key.id
        data["self"] = "http://skinnern-cs493-project3.appspot.com/boats/" + str(boat.key.id)
		# I couldn't figure out how to get the base url so it would be generic, so I just used a string for it instead
        response = app.response_class(
            response=json.dumps(data),
            status=200,
            mimetype='application/json'
        ) #close if
        return response
    else:
        response = app.response_class(
            response=json.dumps({"Error": "No boat with this boat_id exists"}),
            status=404,
            mimetype='application/json'
        ) #close else
        return response

#----------------------------------------------------------------------------------
# end get a specific boat



# edit the boat with a patch
#----------------------------------------------------------------------------------
@app.route('/boats/<id>', methods=['PATCh'])
def boat_edit(id):
	#check if it is a valid request
    if validate_boat_create(request):
        failed = {"Error": "The request object is missing at least one of the required attributes"}
        response = app.response_class(
            response=json.dumps(failed),
            status=400,
            mimetype='application/json'
        ) # close if
        return response

    key_for_boat = client.key("boat", int(id))
    boat = client.get(key=key_for_boat)
	#check if it is a valid request
    if not boat:
        failed = {"Error": "No boat with this boat_id exists"}
        response = app.response_class(
            response=json.dumps(failed),
            status=404,
            mimetype='application/json'
        ) #close if
        return response

    content = request.get_json()
    boat.update({
        "name": content["name"],
        "length": content["length"],
        "type": content["type"]
    })
    client.put(boat)
	# make our url and ID
    boat["id"] = boat.key.id
    boat["self"] = "http://skinnern-cs493-project3.appspot.com/boats/" + str(boat.key.id)
	# I couldn't figure out how to get the base url so it would be generic, so I just used a string for it instead
    response = app.response_class(
        response=json.dumps(boat),
        status=200,
        mimetype='application/json'
    )
    return response

#----------------------------------------------------------------------------------
#end edit the boat with a patch
	
# delete a boat
#----------------------------------------------------------------------------------
@app.route('/boats/<id>', methods=['DELETE'])
def boat_delete(id):
    key_for_boat = client.key("boat", int(id))
    boat = client.get(key=key_for_boat)
	#check if it is a valid request
    if not boat:
        failed = {"Error": "No boat with this boat_id exists"}
        response = app.response_class(
            response=json.dumps(failed),
            status=404,
            mimetype='application/json'
        )
        return response
    client.delete(key_for_boat)

    # Check if the boat is in a slip
    query = client.query(kind="slip")
    query.current_boad = boat.key.id
    slips = query.fetch()
    for slip in slips:
        slip.update({
            "current_boat": None,
        }) # if it is in a slip, we will update the slip to no longer be associated with the boat
        client.put(slip)

    response = app.response_class(
        status=204,
        mimetype='application/json'
    )
    return response

#----------------------------------------------------------------------------------
#end delete a boat
	
# get all boats
#----------------------------------------------------------------------------------
@app.route('/boats', methods=['GET'])
def boat_index():
    query = datastore_client.query(kind="boat")
    boats = list(query.fetch())
    for boat in boats:
		# make our url and ID
        boat["id"] = boat.key.id
        boat["self"] = "http://skinnern-cs493-project3.appspot.com/boats/" + str(boat.key.id)
		# I couldn't figure out how to get the base url so it would be generic, so I just used a string for it instead
    response = app.response_class(
        response=json.dumps(boats),
        status=200,
        mimetype='application/json'
    )
    return response
#----------------------------------------------------------------------------------
#end get all boats

# post our slip
#----------------------------------------------------------------------------------
@app.route('/slips', methods=['POST'])
def slip_create():
	#check if it is a valid request
    if validate_slip_create(request):
        failed = {"Error": "The request object is missing the required number"}
        response = app.response_class(
            response=json.dumps(failed),
            status=400,
            mimetype='application/json'
        ) #close if
        return response

    content = request.get_json()
    mk_new_slip = datastore.entity.Entity(key=client.key("slip"))
    mk_new_slip.update({
        "number": content["number"],
        "current_boat": None,
    })
    client.put(mk_new_slip)
	# make our url and ID
    mk_new_slip["id"] = mk_new_slip.key.id
    mk_new_slip["self"] = "http://skinnern-cs493-project3.appspot.com/slips/" + str(mk_new_slip.key.id)
	# I couldn't figure out how to get the base url so it would be generic, so I just used a string for it instead
    response = app.response_class(
        response=json.dumps(mk_new_slip),
        status=201,
        mimetype='application/json'
    )
    return response

#----------------------------------------------------------------------------------
#end post our slip

#get slip with specific id
#----------------------------------------------------------------------------------
@app.route('/slips/<id>', methods=['GET'])
def slip_show(id):
    key_for_slip = client.key("slip", int(id))
    slip = client.get(key=key_for_slip)

    if slip:
        data = dict(slip)
		# make our url and ID
        data["id"] = slip.key.id
        data["self"] = "http://skinnern-cs493-project3.appspot.com/slips/" + str(slip.key.id)
		# I couldn't figure out how to get the base url so it would be generic, so I just used a string for it instead
        response = app.response_class(
            response=json.dumps(data),
            status=200,
            mimetype='application/json'
        ) #close if
        return response
    else:
        response = app.response_class(
            response=json.dumps({"Error": "No slip with this slip_id exists"}),
            status=404,
            mimetype='application/json'
        ) #close else
        return response

#----------------------------------------------------------------------------------
#end get slip woth specific id
		
# get all of our slips
#----------------------------------------------------------------------------------
@app.route('/slips', methods=['GET'])
def slip_index():
    query = datastore_client.query(kind="slip")
    slips = list(query.fetch())
    for slip in slips:
		# make our url and ID
        slip["id"] = slip.key.id
        slip["self"] = "http://skinnern-cs493-project3.appspot.com/slips/" + str(slip.key.id)
	# I couldn't figure out how to get the base url so it would be generic, so I just used a string for it instead
    response = app.response_class(
        response=json.dumps(slips),
        status=200,
        mimetype='application/json'
    )
    return response

#----------------------------------------------------------------------------------
#end get all of our slips

# put a boat inside a slip
#----------------------------------------------------------------------------------
@app.route('/slips/<slip_id>/<boat_id>', methods=["PUT"])
def boat_arrives(slip_id, boat_id):
    # Get objects
    key_for_slip = client.key("slip", int(slip_id))
    slip = client.get(key=key_for_slip)
    key_for_boat = client.key("boat", int(boat_id))
    boat = client.get(key=key_for_boat)
    if not slip or not boat:
        response = app.response_class(
            response=json.dumps({"Error": "The specified boat and/or slip don’t exist"}),
            status=404,
            mimetype='application/json'
        ) #close if
        return response

    if slip["current_boat"]:
        response = app.response_class(
            response=json.dumps({"Error": "The slip is not empty"}),
            status=403,
            mimetype='application/json'
        ) #close if
        return response

    slip.update({
        "current_boat": boat.key.id
    })
    client.put(slip)
    response = app.response_class(
        status=204,
        mimetype='application/json'
    )
    return response
#----------------------------------------------------------------------------------
#end put a boat inside of a slip
	
	
# delete a specific slip
#----------------------------------------------------------------------------------
@app.route('/slips/<slip_id>', methods=["DELETE"])
def slip_delete(slip_id):
    key_for_slip = client.key("slip", int(slip_id))
    slip = client.get(key=key_for_slip)
    if not slip:
		# error message that no slip with this slipid exists
        failed = {"Error": "No slip with this slip_id exists"}
		#craft our response
        response = app.response_class(
            response=json.dumps(failed),
            status=404,
            mimetype='application/json'
        ) #close if
        return response
    client.delete(key_for_slip)
    response = app.response_class(
        status=204,
        mimetype='application/json'
    )
    return response
#----------------------------------------------------------------------------------
# end delete a specific slip


# delete a boat from the slip
#----------------------------------------------------------------------------------
@app.route('/slips/<slip_id>/<boat_id>', methods=["DELETE"])
def boat_departs(slip_id, boat_id):
    # get the object slip
    key_for_slip = client.key("slip", int(slip_id))
    slip = client.get(key=key_for_slip)
	#get the object boat
    key_for_boat = client.key("boat", int(boat_id))
    boat = client.get(key=key_for_boat)
	#check if it is a valid request
    if not slip or not boat or "current_boat" not in slip or slip["current_boat"] != boat.key.id:
        response = app.response_class(
			# error out with nothing exists
            response=json.dumps({"Error": "No boat with this boat_id is at the slip with this slip_id"}),
            status=404,
            mimetype='application/json'
        ) #close if
        return response
	#update the slip to have no ship inside of it
    slip.update({
        "current_boat": None
    })
	#put our slip, which will overwrite what was there
    client.put(slip)
    response = app.response_class(
        status=204,
        mimetype='application/json'
    )
    return response
#----------------------------------------------------------------------------------
#end delete a boat from the slip



if __name__ == '__main__':
    # This is used when running locally only. When deploying to Google App
    # Engine, a webserver process such as Gunicorn will serve the app. This
    # can be configured by adding an `entrypoint` to app.yaml.
    # Flask's development server will automatically serve static files in
    # the "static" directory. See:
    # http://flask.pocoo.org/docs/1.0/quickstart/#static-files. Once deployed,
    # App Engine itself will serve those files as configured in app.yaml.
    app.run(host='127.0.0.1', port=8080, debug=True)
