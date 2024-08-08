import requests
from tkinter import Tk
from tkinter.filedialog import askdirectory
import time
import os

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
    # print(request.status_code)
    
    data = request.json()
    print(data)
    contentID = data['id']
    print(contentID) #
    
    #Gets progress for Content Download
    progressURL = data['progress_url']
    progressID = progressURL.rsplit('/', 1)[-1]
    
    progressBar = 0
    progressRequestRAW = requests.get(f'https://webcourses.ucf.edu/api/v1/progress/{progressID}', headers = headers)
    # print(progressRequestRAW.status_code)
    progressRequest = progressRequestRAW.json()

    print(progressRequest)
    #Until Download Completes, update progress completion
    while(progressBar != 100):
        time.sleep(2)
        progressRequestRAW = requests.get(f'https://webcourses.ucf.edu/api/v1/progress/{progressID}', headers = headers)
        progressRequest = progressRequestRAW.json()
        progressBar = progressRequest['completion']
        print(str(progressBar) + '%')
        
    
    
    #gets url for content download
    contentURLRAW = requests.get(f'https://webcourses.ucf.edu/api/v1/courses/{courseID}/content_exports/{contentID}', headers=headers)
    # print(contentURL.status_code)
    contentURL = contentURLRAW.json()
    print(contentURL)
    
    downloadURL = contentURL['attachment']['url']
    fileName = contentURL['attachment']['filename']
    savePath = os.path.join(filePath, fileName)
    
    downloadContent = requests.get(downloadURL)
    #Download File from URL and save to Directory
    with open(savePath, 'wb') as file:
        file.write(downloadContent.content)
    
    
    
    