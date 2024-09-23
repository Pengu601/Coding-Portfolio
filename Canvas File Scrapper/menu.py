from operations import *

def mainMenu(headers, params):
    print("--------------------------------")
    print("1. Download Course Files")
    print("2. TBD")    
    print("3. TBD")
    print("4. TBD")    
    print("5. Exit")
    print("--------------------------------")
    choice = input(">> ")
    print(choice)
    if(choice == '1'):
        print('test')
        courseFileMenu(headers, params)
    
    if(choice == '5'):
        return -1
        
    
def courseFileMenu(headers, params):
    courses = getCourses(headers, params)
    print("--------------------------------")
    print("1. Download Course Files")
    print("2. TBD")    
    print("3. TBD")
    print("4. TBD")    
    print("--------------------------------")
    