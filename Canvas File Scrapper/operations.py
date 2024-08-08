import requests
from tkinter import Tk
from tkinter.filedialog import askdirectory


headers = {
    'Authorization': 'Bearer 1158~WVPhPyWU4Qve4ZwB9rFeBJkLG7Zy2L8u6FLFmwtxHvJDWhEVQmTUXNwEyRaJWVEr',
}

def getDueDates(courseID):
    request = requests.get("https://webcourses.ucf.edu/api/v1/courses/" + str(courseID) + "/permissions", headers=headers)
    data = request.json()
    for i in data:
        print(i)
        
def downloadCourseFiles(courseID):
    #get directory path of where user wants to download course files
    filePath = askdirectory(title='Select Folder') #gets folder path for assignments to download to
    print(filePath)
    
    request = requests.post(f'https://webcourses.ucf.edu/api/v1/courses/{courseID}/content_exports', headers=headers, params= {'export_type': 'zip'} )
    print(request.status_code)
    
    data = request.json()
    print(data)
    
    