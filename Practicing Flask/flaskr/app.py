import os

from flask import Flask

def create_app(test_config=None):
    #create and configure the app
    app = Flask(__name__, instance_relative_config=True)
    app.config.from_mapping(SECRET_KEY='dev', DATABASE = os.path.join(app.instance_path, 'flaskr.sqlite'))
    
    if test_config is None:
        #load the instance config if it exists when not testing
        app.config.from_pyfile('config.py', silent=True)
    else:
        #load the test config if passed in the
        app.config.from_mapping(test_config)
        
    #ensure the instance folder exists
    try:
        os.makedirs(app.instance_path) #checks that the instance path exists, ask flask doesn't create the instance folder automatically
    except OSError:
        pass
    
    #a simple page that says hello
    @app.route('/')
    def hello():
        return "Hello, World!"
    
    return app