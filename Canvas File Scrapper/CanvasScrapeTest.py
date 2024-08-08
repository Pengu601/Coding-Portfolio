import requests

from operations import *
#headers used to get access to user account
headers = {
    'Authorization': 'Bearer 1158~WVPhPyWU4Qve4ZwB9rFeBJkLG7Zy2L8u6FLFmwtxHvJDWhEVQmTUXNwEyRaJWVEr',
}
#params used to filter for specific info 
params = {
    'enrollment_state' : 'active', #used to only get courses that are currently active
}

# def getDueDates(courseID):
#     request = requests.get("https://webcourses.ucf.edu/api/v1/courses/" + str(courseID) + "/permissions", headers=headers)
#     data = request.json()
#     for i in data:
#         print(i)


#Todo - make the header parameter a user input
response = requests.get('https://webcourses.ucf.edu/api/v1/users/self/favorites/courses', headers=headers, params = params)

#check if authentication is successfull
print(response.status_code)

data = response.json() #turn the response into a json object to be able to store data

courses = [] #stores course id
for i in data:
    courses.append(i['id'])
    
downloadCourseFiles(courses[0])


