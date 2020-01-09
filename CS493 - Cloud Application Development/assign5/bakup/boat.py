from flask import Blueprint, request, Response, redirect, render_template
from google.cloud import datastore
import json
from cerberus import Validator

#found the cerberus validator, i use it to validate my boat schema


#i am using templates for the html send, i should have a file located in the zip directory, but its just a layout for sending the data


#start up the datastore
datastore_client = datastore.Client()
client = datastore.Client()




#this is our blueprint for the boats url, where the prefix is /boats
bp = Blueprint('boat', __name__, url_prefix='/boats')


#the general schema for a boat
#---------------------------------------------------------------------------------------
#we will want to follow a general pattern
#name
#length
#type

#there is a minimum length and a maximum length of each datatype
boat_schema = {
    'name': {
        'type': 'string',
        'minlength': 3,
        'maxlength': 256,
        'regex': '[a-zA-Z][a-zA-Z ]+[a-zA-Z]$'

    },
    'length': {
        'type': 'integer',
        'min': 1,

    },
    'type': {
        'type': 'string',
        'minlength': 3,
        'maxlength': 256,
        'regex': '[a-zA-Z][a-zA-Z ]+[a-zA-Z]$'
    },
}
#---------------------------------------------------------------------------------------


#our boat validator will use the schema that we provide to test if a boat is allowed to be placed into the datastore
boat_validator = Validator(boat_schema, purge_unknown=True)


#if we're posting a new boat
#we can error through 
#400 - doesn't follow our specs
#403 - non unique
#406 - malformed body

#we can accept through 201
#---------------------------------------------------------------------------------------
@bp.route('', methods=['POST']) 
def post_boat_creation(): #here we're gonna create a boat with the post method
    #we need to make sure that all the data is in the request, or else we will need to reject
    boat_validator.require_all = True #set default bool value


	#if statement that checks that tje request is not empty
	#checks that the request data and the boat validator's result are not none
    if request.get_json() is None\
            or not request.data \
            or not boat_validator.validate(request.get_json()):
		#if we encounter any of these errors, we will send an error message
        failed = {"Error": "the request object doesn't follow our specifications."} # error message construction
        response = Response(response=json.dumps(failed), status=400, mimetype='application/json') #craft the response
        return response # send the response


	#get the request header accept type, if its not application/json we will reject, as we cannot parse it
    print(request.headers.get("Accept")) #print the header
    print(request.headers.get("Accept") != "")#check not empty
	#this if will need to check if we're sending an application/json
	#if not, it checks if its none, or empty
	#if it is neither of those, we will error out, as that can indicate that the content type is not an acceptable format
    if "application/json" not in request.accept_mimetypes \
            and request.headers.get("Accept") is not None\
            and request.headers.get("Accept") != "":
        response = Response(response=json.dumps({"Error": "This body type is not supported."}), status=406, mimetype='application/json') #error out, telling the user that the format is not acceptable
        return response

	#if we've made it this far, we will get the json content to check against our existing datastore
    content = request.get_json() #grab the json content

    #check against our current datastore to make sure no other boat has the same name as the current one
    query = client.query(kind="boat") #send out a query on the boat datatype
    query.add_filter("name", "=", content["name"]) #where name = the request name
    results = list(query.fetch()) #send the query off to be checked
    if len(results) > 0: #if we have more than 0 responses, thats a big nono. we will need to reject the add
        response = Response(response= json.dumps({"Error": "Boat names must be unique."}), status=403, mimetype='application/json') #craft the json response
        return response # send the response



    new_boat = datastore.entity.Entity(key=client.key("boat"))
    new_boat.update(boat_validator.document)
    client.put(new_boat)

    new_boat["id"] = new_boat.key.id
    new_boat["self"] = request.url_root + "boats/" + str(new_boat.key.id)

    response = Response(
        response=json.dumps(new_boat),
        status=201,
        mimetype='application/json'
    )
    return response
#---------------------------------------------------------------------------------------



# illegal arguments for the base URL /boats
#---------------------------------------------------------------------------------------
@bp.route('', methods=['DELETE', 'PUT', 'PATCH']) #these are methods we dont allow on the base /boats url
def illegal_types(): #illegal actions , only need to send a response that we dont' do that here
    response = Response(json.dumps({"Error": "This is action is disallowed in this location."}), status = 405, mimetype = 'application/json') # craft our response
    return response #send the response
#---------------------------------------------------------------------------------------








# get an individual boat

#we can error out through:
#400 - request doesn't follow our specs
#404 - boat was not found
#406 - body type is malformed

# we can accpet through
#200 - application/json - send the user a json string with the values
#200 - text/html - send the user a html text series with the values
#---------------------------------------------------------------------------------------
@bp.route('/<int:id>', methods=['GET']) #get method for grabbing an individual boat
def get_the_boat(id): 

    if id is None or request.data: #if the id does not exist, or the request data is not populated
        failed = {"Error": "the request object doesn't follow our specifications."} #craft error message telling the user that it is wrong
        response = Response(response=json.dumps(failed), status=400, mimetype='application/json') #craft our response
        return response # send the response


	#next we will want to check that the boat actually exists within the datastore
    boat_key = client.key("boat", int(id)) # make our key to get the boat
    boat = client.get(key=boat_key) #get the boat

    #check that the boat actually exists
    if not boat: #if we don't get anything in the reply, the boat does not exist, we can send an error message telling this to the user
        response = Response(response=json.dumps({"Error": "No boat with this boat_id exists"}), status=404, mimetype='application/json') # craft our response
        return response # send the response
    #since we've made it here, that means the boat exists, we will want to start encapsulating it in a response to the user
    boat["id"] = boat.key.id #grab the boat id to use in creating the self url
    boat["self"] = request.url_root + "boats/" + str(boat.key.id) #craft the self url with the boat id 
    print(str(len(request.accept_mimetypes)) + " in the accept_mimtypes") #grab the accept from the request, and format a string checking if it is in the mimetypes
    print(request.accept_mimetypes) #print the accepted mimetypes
	
	
	#we will want to accept either application/json, or text/html. we will error out on anything else
    best = request.accept_mimetypes.best_match(["application/json", 'text/html']) #check accept mimetype 
    #if accept is null, we will just accept it, and then send back a json string to the client
    if request.headers.get("Accept") is None or request.headers.get("Accept") == "": #if to check null
        print("Accept isn't set") #the accept isnt set
        response = Response(response=json.dumps(boat), status=200, mimetype='application/json') #craft the default response for no accept
		
    elif best == "text/html": #else if html
        print("HTML")
        return render_template('boat.html', boat=boat) #render the html form
		
    elif best == "application/json": #elseif json
        response = Response(response=json.dumps(boat),status=200,mimetype='application/json') #just crafting the json response again
		
    else: #if the accept type is not one of our defined types, or null, we will error out
        response = Response(response=json.dumps({"Error": "This body type is not supported."}), status=406,mimetype='application/json')
		
    return response#return the response (whichever type it may be)
#---------------------------------------------------------------------------------------

#delete should be easy enough
#we can error through:
#400 - doesn't follow our specs
#404 - not found

#we can accept through
#204 - no reply needed, successful delete
#---------------------------------------------------------------------------------------
@bp.route('/<int:id>', methods=['DELETE']) #we want a specific id on a boat that we will delete
def delete_the_boat(id):
    boat_key = client.key("boat", int(id)) #get our boat key
    boat = client.get(key=boat_key) # get the individual boat
    if not boat: #if it is empty, we will send back an error 404, boat not found
        failed = {"Error": "No boat with this boat_id exists"} #craft error message for response`
        response = Response(response=json.dumps(failed), status=404, mimetype='application/json') # craft response
        return response #send the response

    #if there is data in the request body, we can throw a 400 error
    if request.data: #if there is data in request
        failed = {"Error": "the request object doesn't follow our specifications"} #this request is abnormal, we create an error message
        response = Response(response=json.dumps(failed), status=400, mimetype='application/json') # create the response
        return response #send the response


	#if the boat exists, and the body for the request doesn't have anything strange in in, we can continue deleting
    client.delete(boat_key) #delete the boat

    response = Response(status=204,mimetype='application/json') #return a 204, no reply other than the status code
    return response # send it to the client
#---------------------------------------------------------------------------------------

#patch and put our boat
#we should be able to use a redirect for put
#errors should be:
#400
#403 - non-unique
#406 - the body type is not supported

#the following redirect should be accepted:
#303 - redirects put

#the following accepts should be allowed:
#200 - patching the boat with the new data


#---------------------------------------------------------------------------------------
@bp.route('/<int:id>', methods=['PATCH', 'PUT']) # we can patch or put the boats to modify them
def edit_the_boat(id):
    # Not all data is required for PATCH
    if request.method == "PATCH": #if the request is a patch, we will not require everything to be present
        boat_validator.require_all = False #toggle if everything is needed
		
    else: #if the request is a put, everything must be present
        boat_validator.require_all = True #toggle if everything is needed

	#if the request is empty, with no request data at any point, or we have a weird content type request, we will fail
    if request.get_json() is None\
            or not request.data \
            or not boat_validator.validate(request.get_json())\
            or not request.content_type == 'application/json':
        failed = {"Error": "the request object doesn't follow our specifications."} # craft the error message
        response = Response(response=json.dumps(failed), status=400, mimetype='application/json') #craft the response
        return response #send the response


    if len(request.accept_mimetypes) != 0 and "application/json" not in request.accept_mimetypes: # if we've got an accept type that isnt allowed we will want to error out
        response = Response( response=json.dumps({"Error": "This body type is not supported."}), status=406, mimetype='application/json') #error out telling the user the body type isnt accepted
        return response #send the response


    #if we've made it this far, we can start checking the actual boat
	#first we will check that the boat name is unique
    if "name" in request.json: #if the name is in json
        query = client.query(kind="boat") #query the boat type
        query.add_filter("name", "=", request.get_json()["name"]) # add a where clause with the name of the given boat
        results = query.fetch() #send the query
        results = list(results) #grab our results
        if len(results) > 0 and results[0].key.id != int(id): #if there is even once item with this name, we cant user it, and will error out
            response = Response(response= json.dumps({"Error": "the Boat name must be unique."}), status=403, mimetype='application/json') #craft the response
            return response #send the response to the client
	
	
	#if no other boat has the same name, and the request follows our specifications, we can continue
    boat_key = client.key("boat", int(id))#gre boat key
    boat = client.get(key=boat_key) #get the boat
	
	

    if not boat: #if the boat does not exist, we will inform the user
        failed = {"Error": "No boat with this boat_id exists"} #craft the failure message
        response = Response(response=json.dumps(failed), status=404, mimetype='application/json') #craft the 404 response
        return response #return our response to the user 


	#we will want to use the validator on the boat
    boat.update(boat_validator.document)
    client.put(boat) #we will put the boat into our datastore

    boat["id"] = boat.key.id #get the id to make the self url
    boat["self"] = request.url_root + "boats/" + str(boat.key.id) #use the id to make the self-referential url

    # return the updated boat if we're patching
    if request.method == "PATCH": #if the method is patch, we will return our response
        response = Response(response=json.dumps(boat), status=200, mimetype='application/json' ) # craft our response for the patch
        return response # send the response
		
		
    else: #if we have a put
        return redirect(boat["self"], code=303) #return a 303 code for redirect
#---------------------------------------------------------------------------------------





