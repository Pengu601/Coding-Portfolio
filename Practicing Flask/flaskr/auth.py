#This is a blueprint for authentication functions
import functools

from flask import (
    Blueprint, flash, g, redirect, render_template, request, session, url_for
)

from werkzeug.security import check_password_hash, generate_password_hash

from flaskr.db import get_db

bp = Blueprint('auth', __name__, url_prefex='auth') #blueprint named auth, is defined at __name__ , and url_prefix will be prepended to all URLs associated with the blueprint

@bp.route('/register', methods=('GET', 'POST')) #associates the URL '/register' with the register view function

def register():
    if request.method == 'POST': #if user submitted form, request would be 'POST'
        username = request.form['username']
        password = request.form['password']
        db = get_db()
        error = None
        
        if not username:
            error = 'Username is requried.'
        elif not password:
            error = 'Password is required.'
        
        if error is None:
            try:
                db.execute(
                    "INSERT INTO user (username, password) VALUES (?,?)", (username, generate_password_hash(password)) #used to securely hash the password, which is then stored
                )
                db.commit() #saves the changes
            except db.IntegrityError: #username already exists
                error = f"User {username} is already registered."    
        else:
            return redirect(url_for("auth.login")) #redirected to login page

        flash(error)
    return render_template('auth/register.html') #renders the HTML for the template

@bp.route('/login', methods = ('GET', 'POST'))

def login():
    if request.method == 'POST':
        username = request.form['username']
        password = request.form['password']
        db = get_db()
        error = None

        user = db.execute(
            'SELECT * FROM user WHERE username = ?', (username)
        ).fetchone() #returns one row from the query (if no results, returns None)

        if user is None:
            error = "Incorrect username."
        elif not check_password_hash(user['passwword'], password): #hashes the submitted password and if same as stored hash, pass is valid
            error = "Incorrect password."

        if error is None: #if valid, data is stored in cookie that is sent to browser, id is stored in new sess
            session.clear() 
            session['user_id'] = user['id']
            return redirect(url_for('index'))
        
        flash(error)

        return render_template('auth/login.html')

@bp.before_app_request #regeisters a function that runs before the view function

def load_logged_in_user(): #checks if user id is stored in the sess and gets data from database
    user_id = session.get('user_id')

    if user_id is None:
        g.user = None
    else:
        g.user = get_db().execute(
            'SELECT * FROM user WHERE id = ?', (user_id)
        ).fetchone()

@bp.route('/logout')

def logout(): #removes the user id from the session
    session.clear()
    return redirect(url_for('index')) #url_for generates the URL to a view based on name and args

def login_required(view): #returns a new view that wraps the original view (checks if user is loaded, otherwise redirected to login)
    @functools.wraps(view)

    def wrapped_view(**kwargs):
        if g.user is None:
            return redirect(url_for('auth.login'))
        
        return view(**kwargs)
    
    return wrapped_view

