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
    filePath = askdirectory(title='Select Folder') 
    
    #get request to download content from course
    request = requests.post(f'https://webcourses.ucf.edu/api/v1/courses/{courseID}/content_exports', headers=headers, params= {'export_type': 'zip'} )
    # print(request.status_code)
    
    data = request.json()
    contentID = data['id'] #ID for content export job
    
    #Gets progress for Content Download
    progressURL = data['progress_url']
    progressID = progressURL.rsplit('/', 1)[-1] #gets the progress ID by taking the numbers after the last / in the url string
    
    progressBar = 0
    progressRequestRAW = requests.get(f'https://webcourses.ucf.edu/api/v1/progress/{progressID}', headers = headers)
    progressRequest = progressRequestRAW.json()
    
    
    #Until Download Completes, update progress completion
    while(progressBar != 100):
        time.sleep(2)
        progressRequestRAW = requests.get(f'https://webcourses.ucf.edu/api/v1/progress/{progressID}', headers = headers)
        progressRequest = progressRequestRAW.json()
        progressBar = progressRequest['completion']
        print(str(progressBar) + '%')
    
    print(f'Success! Downloaded to {filePath}')

    #gets paginated list for content export
    contentURLRAW = requests.get(f'https://webcourses.ucf.edu/api/v1/courses/{courseID}/content_exports/{contentID}', headers=headers)
    contentURL = contentURLRAW.json()
    
    #gets download url and file name from paginated list, and assign save path to the os to download the export to
    downloadURL = contentURL['attachment']['url']
    fileName = contentURL['attachment']['filename']
    savePath = os.path.join(filePath, fileName)
    
    downloadContent = requests.get(downloadURL)
    
    #Download File from URL and save to Directory
    with open(savePath, 'wb') as file:
        file.write(downloadContent.content)
    
    
    
    