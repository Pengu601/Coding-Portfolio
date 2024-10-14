
import sqlite3
from operations import *
from cryptography.fernet import Fernet
import os

def getToken():
    key = loadKey()
    authToken = checkTokens(key)
    if(authToken == ""):
        authToken = input("Please enter Token: ")
        headers ={'Authorization': f'Bearer {authToken}'}
        storeToken(authToken, key)
    else:
        headers = {'Authorization': f'Bearer {authToken}'}    
    
    return headers

def storeToken(authToken, key): #stores token into table if it doesn't exist already
    connection = sqlite3.connect('users.db')
    cursor = connection.cursor()

    fernet = Fernet(key)
    encryptedAuthToken = fernet.encrypt(authToken.encode())
    cursor.execute("CREATE TABLE IF NOT EXISTS auth_token (id INTEGER PRIMARY KEY, user_token TEXT)")

    cursor.execute("INSERT INTO auth_token (user_token) VALUES (?)", (encryptedAuthToken.decode(),))
    connection.commit()
    
    connection.close()
    
def checkTokens(key):
    connection = sqlite3.connect('users.db')
    cursor = connection.cursor()
    
    cursor.execute("SELECT name FROM sqlite_master ")
    tables = cursor.fetchall()
   
    if len(tables) == 0:
        return ""
    
    
    cursor.execute("SELECT * FROM auth_token")
    users = []
    fernet = Fernet(key)
    for row in cursor.fetchall():
        user = fernet.decrypt(row[1].encode()).decode()
        users.append(tokenToUser(user))
    
    
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
    
    connection.close()

    decryptedToken = fernet.decrypt(row[1].encode()).decode()
    return decryptedToken

KEY_FILE_PATH = os.path.expanduser("~/.my_app_encryption_key")

def generateKey(): #generates an encryption key if not already existed on user's machine
    key = Fernet.generate_key()
    with open(KEY_FILE_PATH, 'wb') as key_file:
        key_file.write(key)
    
    os.chmod(KEY_FILE_PATH, 0o600)

    print(f'Encryption key stored at {KEY_FILE_PATH}')

def loadKey(): #loads key if found on user's machine, else generates a new key
    if not os.path.exists(KEY_FILE_PATH):
        generateKey()
    
    with open(KEY_FILE_PATH, 'rb') as key_file:
        key = key_file.read()
    
    return key