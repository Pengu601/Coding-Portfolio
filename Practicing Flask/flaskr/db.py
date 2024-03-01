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
    