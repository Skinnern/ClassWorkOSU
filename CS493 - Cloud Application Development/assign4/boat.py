from flask import Blueprint, request
from google.cloud import datastore
import json
import constants

client = datastore.Client()

bp = Blueprint('boat', __name__, url_prefix='/boats')

#post and get the boat
#i learned that you can combine commands that share a similar route,
#so i took advantage of this, but i think it made my code a lot harder to read
@bp.route('', methods=['POST', 'GET'])
def boats_get_post(): #define our get/post for boats
    if request.method == 'POST': #if we're posting, we will want to do some error checking
        content = request.get_json()
        errObj = {"Error": "The request object is missing at least one of the required attributes"}
        if "name" not in content:
            return (json.dumps(errObj), 400) #if name is not in the json object, we want to return
        elif "type" not in content:
            return (json.dumps(errObj), 400) #if type is not in the json object, we want to return
        elif "length" not in content:
            return (json.dumps(errObj), 400) #if length is not in the json object, we want to return
        else: #if we have everything we need, then we can create the object
            new_boat = datastore.entity.Entity(key=client.key(constants.boats)) # new datastore entry for boats
            new_boat.update({"name": content["name"], "type": content["type"], "length": content["length"], "loads": [], "id": None, "self": None})
            client.put(new_boat)#get the client to put the new boat into the datastore
            new_boat["id"] = new_boat.key.id #grab the id to return to the client
            new_boat["self"] = str(request.base_url) + "/" + str(new_boat.key.id) #get the referential 'self' url
            return (json.dumps(new_boat), 201) #return with response code & message

    elif request.method == 'GET': #if we're getting, we want to enable pagnation
        query = client.query(kind=constants.boats) #new query for the boats
        q_limit = int(request.args.get('limit', '3')) #limit of 3 at a time
        q_offset = int(request.args.get('offset', '0')) #the offset currently used, goes up in increments of 3
        l_iterator = query.fetch(limit=q_limit, offset=q_offset) #fetches the base query
        pages = l_iterator.pages 
        results = list(next(pages)) #
        if l_iterator.next_page_token: #if there are more results, we need to make a url to reach them
            next_offset = q_offset + q_limit #set our next offset equal to our current + the limit per page
            next_url = request.base_url + "?limit=" + str(q_limit) + "&offset=" + str(next_offset)
        else: #if there are no more results, we no longer need to make url's
            next_url = None #no url needed
        for e in results:
            e["id"] = e.key.id #get id for boat
            e["self"] = str(request.base_url) + "/" + str(e.key.id) # append id and make self url for each boat
        output = {"boats": results} #output lists the word boats + actual boats results
        if next_url: #if next_url is not none, we will want to append it to the json object
            output["next"] = next_url #add the 'next' component of the url to the json object
        return json.dumps(output) #send the json object to the client
    else: # if not posting or getting
        return 'Method not recognized' #catch-all for other methods that are unintended for this method


@bp.route('/<id>', methods=['GET', 'PATCH', 'DELETE']) #these methods are for individually viewing and editing boats.
def boats_patch_delete(id): # method definition needs boat id
    if request.method == 'GET': # if we're sending a get command, do these steps
        boat_key = client.key(constants.boats, int(id)) #grab data
        boat = client.get(boat_key)#query to get boat info
        errObj = {"Error": "No boat with this boat_id exists"} # error message for boat that doesn't exist
        if boat is None:
            return (json.dumps(errObj), 404) #if there is no boat, we return a 404
        else:
            boat["id"] = boat.key.id #give the boat's id in the datastore
            boat["self"] = str(request.base_url) #give the boat's self url
            return (json.dumps(boat), 200) # send the info on boat, and return 200, a successful request
    elif request.method == 'PATCH': # if we want to patch an existing boat
        content = request.get_json() #get the json from the client request
        errObj = {"Error": "The request object is missing at least one of the required attributes"} #error message for missing attributes
        if "name" not in content:
            return (json.dumps(errObj), 400) # error for name missing
        elif "type" not in content:
            return (json.dumps(errObj), 400) # error for type missing 
        elif "length" not in content:
            return (json.dumps(errObj), 400) # error for length missing
        boat_key = client.key(constants.boats, int(id)) #get key
        boat = client.get(key=boat_key) # get the boat information
        if boat is None:
            errObj = {"Error": "No boat with this boat_id exists"} # if the boat does not exist, tell the client
            return (json.dumps(errObj), 404) #send error message with 404
        else: #if the object exists in the datastore, we will update it
            boat.update({"name": content["name"], "type": content["type"], "length": content["length"]})#update each attribute
            client.put(boat)#put the boat into the boat object
            boat["id"] = boat.key.id #grab the id
            boat["self"] = str(request.base_url)#make the self link
            return (json.dumps(boat), 200) #return the new boat object with status code 200
    elif request.method == 'DELETE': #if the user wants to delete a boat
        boat_key = client.key(constants.boats, int(id)) # get the key
        boat = client.get(key=boat_key) # get the boat
        errObj = {"Error": "No boat with this boat_id exists"} #error checking message 404
        if boat is None:
            return (json.dumps(errObj), 404) #if the boat was not found, send 404 error message
        else: #if the boat was found, we will want to check the loads associated with the boat and remove that relationship
            if len(boat["loads"]) > 0: # if the number of boats is greater than 0
                for each in boat["loads"]: # for each load
                    load_id = each["id"] # get the load id's 
                    load_key = client.key(constants.loads, int(load_id)) # load key
                    load = client.get(key=load_key) #load load
                    if load is not None: # if load is not null, we want to iterate and remove all the associated loads
                        load["carrier"] = None # set the carrier for a specified load to none
                        client.put(load) # put the new load info into our datastore
                client.delete(boat_key) # delete the boat key we made
                return ('', 204) # return 204, a successful delete, no other return is required (with load version)
            else:
                client.delete(boat_key)
                return ('', 204) # return 204, a successful delete, no other return is required
    else:
        return 'Method not recognized' # catch all for unintended method

@bp.route('/<id>/loads', methods=['GET']) # boats/boatid/loads
def get_boat_loads(id):#this new method needs to display all of the loads associated with a boat
    boat_key = client.key(constants.boats, int(id)) #get the boat id specified by the client
    boat = client.get(key=boat_key) #send query with boat id to check if it contains loads
    if len(boat["loads"]) > 0: #if the boat has loads, we want to print them
        return json.dumps(boat["loads"])#print the loads
    else: #if the boat has no loads, we will still send empty json
        return json.dumps([]) #empty string for loads associated with boat
