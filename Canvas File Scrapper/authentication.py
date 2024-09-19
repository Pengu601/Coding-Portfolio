import requests

def getToken():
    authToken = input("Please enter Token: ")
    headers ={'Authorization': f'Bearer {authToken}'}
    return headers

