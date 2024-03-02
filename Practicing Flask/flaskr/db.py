import sqlite3 #database using sqlite 

import click
from flask import current_app, g #g is a special object unique for each request | current_app points to the Flask application handling the request

def get_db():
    if 'db' not in g:
        g.db = sqlite3.connect(current_app.config['DATABASE'], detect_types = sqlite3.PARSE_DECLTYPES) #establishes a connection to the file pointed at by the DATAASE configuration key (doesn't exist yet)
        g.db.row_factory = sqlite3.Row #tells the connection to returns rows that behave like dicts (allows accessing the columns by name)
    
    return g.db

def close_db(e=None): #checks if a connection was created by checking if g.db was set
    db = g.pop('db', None)
    
    if db is not None: #if connection exists, close it
        db.close()

def init_db():
    db = get_db() #get_db() returns a database connection, which is used to execute the commands read from the file
    
    with current_app.open_resource('schema.sql') as f: #open_resource() opens a file relative to the flaskr package, since you won't know where the location is 
        db.executescript(f.read().decode('utf-8'))     

@click.command('init-db') #defines a command line command called 'init-db' that calls the init_db function and shows a success message to the user

def init_db_command():
    #clear existing data and create new tables
    init_db()
    click.echo('Initialized the database.')

def init_app(app):
    app.teardown_appcontext(close_db) #tells Flask to call that function when cleaning up after returning the response
    app.cli.add_command(init_db_command) #adds a new command that can be called with the 'flask' command