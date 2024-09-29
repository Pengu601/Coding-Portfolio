from operations import *

def mainMenu(headers, params):
    print("--------------------------------")
    print("1. Courses")
    print("2. TBD")    
    print("3. TBD")
    print("4. TBD")    
    print("5. Exit")
    print("--------------------------------")
    choice = input(">> ")
    # print(choice)
    
    if(choice == '1'):
        courseFileMenu(headers, params)
    
    if(choice == '5'):
        return -1
        
    
def courseFileMenu(headers, params):
    courses = getCourses(headers, params)
    
    for i in range(len(courses)):
        if (i) %2 == 0:
            continue
        print(courses[i])
    while(1):
        print("--------------------------------")
        print("1. Download Course Files")
        print("2. TBD")    
        print("3. TBD")
        print("4. TBD")    
        print("5. Exit")
        print("--------------------------------")
        choice = input(">> ")
        if(choice == '5'):
            break
    