from flask import Blueprint, request
from google.cloud import datastore
import json
import constants
from urllib.parse import urlparse

client = datastore.Client()

bp = Blueprint('load', __name__, url_prefix='/loads') # blueprint to reference load


@bp.route('', methods=['POST', 'GET'])	# base url, we can post and get from here
def loads_get_post():
    if request.method == 'POST': # if the method is post, we will want the information we want to add to the datastore
        content = request.get_json() # request the content sent by the client
        errObj = {"Error": "The request object is missing at least one of the required attributes"} # requested object is missing some components
        if "weight" not in content:
            return (json.dumps(errObj), 400) # weight is missing, error
        elif "content" not in content:
            return (json.dumps(errObj), 400) # content is missing, error
        elif "delivery_date" not in content:
            return (json.dumps(errObj), 400) # delivery date is missing, error
        new_load = datastore.entity.Entity(key=client.key(constants.loads)) #new load to add to our datastore
        new_load.update({"weight": content["weight"], "content": content["content"], "carrier": None, "delivery_date": content["delivery_date"]}) #set the values of our new object
        client.put(new_load) #put into the datastore
        new_load["id"] = new_load.key.id # get the id to make the self link, also add it to the base object
        new_load["self"] = str(request.base_url) + "/" + str(new_load.key.id) # make the self link and add to the object
        return (json.dumps(new_load), 201) # return 201, successful add to the datastore
    elif request.method == 'GET': # if we're getting an object
        query = client.query(kind=constants.loads) # prep our query
        q_limit = int(request.args.get('limit', '3')) #set our limit for the number of objects for pagnation
        q_offset = int(request.args.get('offset', '0')) # set the current offset for pagnation
        g_iterator = query.fetch(limit=q_limit, offset=q_offset) # fetch the current results with the current offset
        pages = g_iterator.pages # number of pages
        results = list(next(pages)) # results to return to the client
        if g_iterator.next_page_token: # if there is a next page, we will want to notify the client with a link
            next_offset = q_offset + q_limit # get the current offset and the limit to create the new offset
            next_url = request.base_url + "?limit=" + str(q_limit) + "&offset=" + str(next_offset) # create the url for the next 3 obbjects from our list
        else: # if there are no more objects, we do not need to create a new url
            next_url = None # no next url
        for e in results: # for each result, we will want to print the id, the self list, as well as the loads associated with the project
            e["id"] = e.key.id # add the id to the json object
            e["self"] = str(request.base_url) + "/" + str(e.key.id) # add the self url to the json object
        output = {"loads": results} #output is loads: followed by our results
        if next_url: # if we have a next URL, we will want to add that before we send the outpur
            output["next"] = next_url
        return json.dumps(output) # send output


@bp.route('/<id>', methods=['GET', 'PUT', 'DELETE']) # steps to movify an individual load.
def loads_get_put_delete(id):
    if request.method == 'GET': # get an individual load
        load_key = client.key(constants.loads, int(id)) #get the key
        load = client.get(load_key) # get the load information
        errObj = {"Error": "No load with this load_id exists"} # error for non existing load
        if load is None:
            return (json.dumps(errObj), 404) #if the result is null, and the load does not exist, we tell the client with a 404
        else:
            load["id"] = load.key.id # get the id
            load["self"] = str(request.base_url) # make the self url
            return (json.dumps(load), 200) # send it back to the client
    elif request.method == 'PUT': # if we're putting a load into the datastore
        content = request.get_json() # get our content from the request
        load_key = client.key(constants.loads, int(id)) # get the load key
        load = client.get(key=load_key) # get the load
        load.update({"name": content["name"]}) # update the content
        client.put(load) # put the load into the datastore
        return (json.dumps(load), 204) # return 204, the load now exists in the datastore
    elif request.method == 'DELETE': # if we want to delete the object
        load_key = client.key(constants.loads, int(id)) # load the key
        load = client.get(key=load_key) # get the load
        errObj = {"Error": "No load with this load_id exists"} # prep error statement
        if load is None: # if the load does not exist, we will want to 404 out
            return (json.dumps(errObj), 404) 
        else: # if it does exist, we will want to delete both the load, and then remove any associations it had
            if load["carrier"] is None: # if there are no carriers, we can just delete and move on
                client.delete(load_key)# delete the load
                return ('', 204) # send a 204
            else: #if there are carriers, we will need to unload them, and then delete the load
                boat_id = load["carrier"]["id"] #get the carrier id
                boat_key = client.key(constants.boats, int(boat_id)) # the key will be our boats boat id
                boat = client.get(key=boat_key) # our boat
                if boat is not None: # if the boat exists
                    if boat["loads"] is not None: # if the boat loads exists
                        for each in boat["loads"]: # if the id for our current load exists in the boat, we will want to remove it
                            if int(each["id"]) == int(id): # check each id in the boat
                                boat["loads"].remove(each) #remove the load from the boat
                                client.put(boat) # but the boat back into the datastore, now updated
                client.delete(load_key) # delete the client load
                return ('', 204) # send a 204 success
    else:
        return 'Method not recognized'


@bp.route('/<load_id>/boats/<boat_id>', methods=['GET', 'PUT', 'DELETE']) # we will be getting, putting, and deleting
def loads_boat_get_put_delete(load_id, boat_id):
    if request.method == 'GET': # for our get
        load_key = client.key(constants.loads, int(load_id)) #get the key
        load = client.get(load_key) #get the load
        errObj = {"Error": "No load with this load_id exists"} # prep an error statement
        if load is None: # if load was not found, return the error message with a 404
            return (json.dumps(errObj), 404)
        else: # if the load was found
            load["id"] = load.key.id # add the id to the load
            load["self"] = str(request.base_url) # add a self referencing url to the load
            return (json.dumps(load), 200) # send the load to the client with a 200 success
    elif request.method == 'PUT': # if we are putting
        load_key = client.key(constants.loads, int(load_id)) #get the load key
        load = client.get(key=load_key) # get the specific load
        boat_key = client.key(constants.boats, int(boat_id)) # get the boat key
        boat = client.get(key=boat_key) # get the boat
        errObj = {"Error": "The specified boat or load do not exist"} #prep error case
        if load is None or boat is None: #if either returns nothing, then we want to error out
            return (json.dumps(errObj), 404) #404, object was missing
        elif load["carrier"] is None: # if carrier is empty, we can easily set the object
            parsed_uri = urlparse(str(request.base_url))
            boat_self = '{uri.scheme}://{uri.netloc}/'.format(uri=parsed_uri)
            boat_self = boat_self + "boats/" + str(boat.key.id)
            load.update({"carrier": {"id": boat_id, "name": boat["name"], "self": boat_self}})
            client.put(load)
            parsed_uri = urlparse(str(request.base_url))
            load_self = '{uri.scheme}://{uri.netloc}/'.format(uri=parsed_uri)
            load_self = load_self + "loads/" + str(load.key.id)
            boat["loads"].append({"id": load_id, "self": str(load_self)})
            client.put(boat)
            return (json.dumps(load), 204)
        else:
            errObj = {"Error": "Load currently has a carrier"}
            return (json.dumps(errObj), 403)
    elif request.method == 'DELETE': # delete method
        load_key = client.key(constants.loads, int(load_id)) # get the load key
        load = client.get(key=load_key) # get the load
        boat_key = client.key(constants.boats, int(boat_id)) # get the boat key
        boat = client.get(key=boat_key) # get the boat 
        if load is None or boat is None: # if either is null, we will error out
            errObj = {"Error": "The specified boat or load do not exist"} # prep an error statement
            return (json.dumps(errObj), 404) # send a 404 error with our message
        elif load["carrier"] is None: # if carrier is none, there is no boat assigned to the load
            errObj = {"Error": "No boat is assigned the load."} # error statement
            return (json.dumps(errObj), 404) #send the error statemnt with a 404
        elif int(load["carrier"]["id"]) != int(boat.key.id): # check if the boat w/ the boat id is assigned to the load
            errObj = {"Error": "No boat with this boat_id is assigned the load with this load_id"} # prep error message
            return (json.dumps(errObj), 404) # send error message with 404
        else: # if non error, then we will go through our process
            for each in boat["loads"]: # we will be removing the load from the boat
                if int(each["id"]) == int(load_id): # if the id matches between boat and load
                    boat["loads"].remove(each) # remove the item from boat
            client.put(boat) # update boat
            load.update({"carrier": None}) # set the carrier of the load to none
            client.put(load) # update the datastore for the load
            return ('', 204) # return 204, successful delete. no return needed
    else:
        return 'Method not recognized' # catch all for other methods used on this method
