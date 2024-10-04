import requests
from authentication import *
from operations import *
from operations import downloadCourseFiles
from menu import *
# from authentication import *
#headers used to get access to user account
# headers = {
#     'Authorization': 'Bearer 1158~WVPhPyWU4Qve4ZwB9rFeBJkLG7Zy2L8u6FLFmwtxHvJDWhEVQmTUXNwEyRaJWVEr',
# }

headers = getToken()
#params used to filter for specific info 
print(headers)
params = {
    'enrollment_state' : 'active', #used to only get courses that are currently active
}

end = 0
while(end != -1):
    end = mainMenu(headers, params)
    
#Todo - make the header parameter a user input
# response = requests.get('https://webcourses.ucf.edu/api/v1/users/self/favorites/courses', headers=headers, params = params)

# #check if authentication is successfull
# print(response.status_code)

# data = response.json() #turn the response into a json object to be able to store data

# courses = [] #stores course id
# for i in data:
#     courses.append(i['id'])51







#downloadCourseFiles(courses[0], headers)


