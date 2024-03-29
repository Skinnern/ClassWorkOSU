from google.cloud import datastore
from flask import Flask, request
import json
import constants
import boat
import load

#import our blueprints for boat and load
app = Flask(__name__)
app.register_blueprint(boat.bp)
app.register_blueprint(load.bp)
client = datastore.Client()

#we want to redirect the user to where to go to use our api

@app.route('/')
def index():
    return "Please navigate to /boats to use this API"


if __name__ == '__main__':
    app.run(host='127.0.0.1', port=8080, debug=True)
