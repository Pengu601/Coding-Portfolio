import requests
from authentication import *
from tkinter import Tk
from tkinter.filedialog import askdirectory
import time
import os
import sys
from tqdm import tqdm
import zipfile


def getCourses(headers, params):
    response = requests.get('https://webcourses.ucf.edu/api/v1/users/self/favorites/courses', headers=headers, params = params)
    data = response.json()
    
    courses = []
    for i in data:
        courses.append(i['id'])
        courses.append(i['name'].rsplit('-', 1)[0])
    return courses


def getDueDates(courseID, headers):
    request = requests.get("https://webcourses.ucf.edu/api/v1/courses/" + str(courseID) + "/permissions", headers=headers)
    data = request.json()
    for i in data:
        print(i)
        
def downloadCourseFiles(courseID, courseName, headers):
    #get directory path of where user wants to download course files
    root = Tk()
    root.withdraw()
    root.wm_attributes('-topmost', 1)
    filePath = askdirectory(title='Select Folder to Download Course Files to') 

    #get request to download content from course
    request = requests.post(f'https://webcourses.ucf.edu/api/v1/courses/{courseID}/content_exports', headers=headers, params= {'export_type': 'zip'} )
    # print(request.status_code)
    
    data = request.json()
    print(data)
    contentID = data['id'] #ID for content export job
    
    #Gets progress for Content Download
    progressURL = data['progress_url']
    progressID = progressURL.rsplit('/', 1)[-1] #gets the progress ID by taking the numbers after the last / in the url string
    
    progressBar = 0
    progressRequestRAW = requests.get(f'https://webcourses.ucf.edu/api/v1/progress/{progressID}', headers = headers)
    progressRequest = progressRequestRAW.json()
    
    
    #Until Download Completes, update progress completion
    if100 = 0
    while(True): 
        progressRequestRAW = requests.get(f'https://webcourses.ucf.edu/api/v1/progress/{progressID}', headers = headers)
        progressRequest = progressRequestRAW.json()
        progressBar = progressRequest['completion']

        if(str(progressRequest['workflow_state']) == 'completed'):
            time.sleep(1)
            break
        
        if(if100 == 1):
            continue
        
        if(progressBar == '100'):
            if100 = 1
        sys.stdout.write(f"\r {progressBar}%")
        sys.stdout.flush()
        time.sleep(.05)
        

    #gets paginated list for content export
    contentURLRAW = requests.get(f'https://webcourses.ucf.edu/api/v1/courses/{courseID}/content_exports/{contentID}', headers=headers)
    contentURL = contentURLRAW.json()

    # print(contentURL)
    #gets download url and file name from paginated list, and assign save path to the os to download the export to
    downloadURL = contentURL['attachment']['url']
    fileName = contentURL['attachment']['filename']
    savePath = os.path.join(filePath, fileName)
    
    with requests.get(downloadURL, stream=True) as downloadContent:
        # Get the total file size from the headers
        total_size = int(downloadContent.headers.get('content-length', 0))
        
        # Open the file to write in binary mode
        with open(savePath, 'wb') as file, tqdm(
            total=total_size, unit='B', unit_scale=True, desc=f"Writing {fileName} to Directory", ascii=True
        ) as pbar:
            # Iterate over the response in chunks
            for chunk in downloadContent.iter_content(chunk_size=1024):
                if chunk:  # filter out keep-alive chunks
                    file.write(chunk)
                    pbar.update(len(chunk))  # Update progress bar with chunk size
    
    print(f'Success! Downloaded to {filePath}')

   
    extractFileContents(savePath, filePath, courseName)
    
    root.destroy()
    
def extractFileContents(savePath, filePath, courseName):
    newPath = os.path.join(filePath, courseName)  #gets the new path for the extract folder
    
    if not os.path.exists(newPath):
        os.makedirs(newPath) #if folder doesnt already exist, create it

    with zipfile.ZipFile(savePath,'r') as zip_ref:
        zip_ref.extractall(newPath) #extract downloaded zip contents to folder
    
    os.remove(savePath)
    os.startfile(filePath)
    
    