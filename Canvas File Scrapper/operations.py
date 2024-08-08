import requests
from tkinter import Tk
from tkinter.filedialog import askdirectory
import time

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
    # print(filePath)
    
    #get request to download content from course
    request = requests.post(f'https://webcourses.ucf.edu/api/v1/courses/{courseID}/content_exports', headers=headers, params= {'export_type': 'zip'} )
    print(request.status_code)
    
    data = request.json()
    print(data)
    contentID = data['id']
    print(contentID) #
    
    progressURL = data['progress_url']
    progressID = progressURL.rsplit('/', 1)[-1]
    # #gets progress of content download - todo
    
    # contentProgress = data['progress_url']
    # showExportRequest = requests.get(contentProgress, headers=headers)
    # # print(showExportRequest.status_code)
    # print(showExportRequest)
    # # data1 = showExportRequest.json()
    # # print(data1)
    
    progressBar = 0.0
    progressRequestRAW = requests.get(f'https://webcourses.ucf.edu/api/v1/progress/{progressID}', headers = headers)
    print(progressRequestRAW.status_code)
    progressRequest = progressRequestRAW.json()

    print(progressRequest)
    while(progressBar != 100.0):
        progressRequestRAW = requests.get(f'https://webcourses.ucf.edu/api/v1/progress/{progressID}', headers = headers)
        progressRequest = progressRequestRAW.json()
        progressBar = progressRequest['completion']
        print(progressBar)
        time.sleep(2)
    
    
    #gets url for content download
    contentURL = requests.get(f'https://webcourses.ucf.edu/api/v1/courses/{courseID}/content_exports/{contentID}', headers=headers)
    print(contentURL.status_code)
    data3 = contentURL.json()
    print(data3)
    
    