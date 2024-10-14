import requests
import sqlite3
from operations import *
import time
def getToken():
    authToken = checkTokens()
    if(authToken == ""):
        authToken = input("Please enter Token: ")
        headers ={'Authorization': f'Bearer {authToken}'}
        storeToken(authToken)
    else:
        headers = {'Authorization': f'Bearer {authToken}'}    
    
    return headers

def storeToken(authToken): #stores token into table if it doesn't exist already
    connection = sqlite3.connect('users.db')
    cursor = connection.cursor()
    cursor.execute("CREATE TABLE IF NOT EXISTS auth_token (id INTEGER PRIMARY KEY, user_token TEXT)")

    cursor.execute("INSERT INTO auth_token (user_token) VALUES (?)", (str(authToken),))
    connection.commit()
    
    cursor.execute("SELECT * FROM auth_token")
    # for row in cursor.fetchall():
    #     print(row)
    
    connection.close()
    
def checkTokens():
    connection = sqlite3.connect('users.db')
    cursor = connection.cursor()
    
    cursor.execute("SELECT COUNT(*) FROM auth_token")
    count = cursor.fetchone()[0]
    
    if(count == 0):
        return ""
    
    cursor.execute("SELECT * FROM auth_token")
    users = []
    for row in cursor.fetchall():
        users.append(tokenToUser(row[1]))
    
    
    for i in range(len(users)):
        print(f"{i+1}. {users[i]}")   
        if(i == (len(users))-1):
            print(f"{i+2}. Add New User") 
        
    print("--------------------------------")
    user = input(">> ")
    if(user == str(len(users)+1)):
        return ""
    
    cursor.execute("SELECT * FROM auth_token WHERE id = ?", (user,))
    row = cursor.fetchone()
    
    return row[1]
    connection.close()
    