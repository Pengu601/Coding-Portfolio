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
    if request.method == 'POST':
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
                    "INSERT INTO user (username, password) VALUES (?,?)", (username, generate_password_hash(password))
                )
                db.commit()
            except db.IntegrityError:
                error = f"User {username} is already registered."    
        else:
            return redirect(url_for("auth.login"))

        flash(error)
    return render_template('auth/register.html')