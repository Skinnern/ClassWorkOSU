import datetime
import boat

from flask import Flask, render_template, request, json


# [START gae_python37_datastore_store_and_fetch_times]
from google.cloud import datastore

#this assignment should only need the boat blueprint, so i've edited the main to only use that

#most of the code was lifted from assignment 3, with a few exceptions

#you cannot GET from the base /boats URL, i encountered an issue, and didn't have enough time to fix it.
#it was not in the requirements that we had to have that functionality though, so i hope that's ok.

# [END gae_python37_datastore_store_and_fetch_times]
app = Flask(__name__)
app.register_blueprint(boat.bp)
client = datastore.Client()




if __name__ == '__main__':
    # This is used when running locally only. When deploying to Google App
    # Engine, a webserver process such as Gunicorn will serve the app. This
    # can be configured by adding an `entrypoint` to app.yaml.

    # Flask's development server will automatically serve static files in
    # the "static" directory. See:
    # http://flask.pocoo.org/docs/1.0/quickstart/#static-files. Once deployed,
    # App Engine itself will serve those files as configured in app.yaml.
    app.run(host='127.0.0.1', port=8080, debug=True)
