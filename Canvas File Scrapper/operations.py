import requests
from authentication import *
from tkinter import Tk
from tkinter.filedialog import askdirectory
import time
import os
from tqdm import tqdm



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
        
def downloadCourseFiles(courseID, headers):
    #get directory path of where user wants to download course files
    root = Tk()
    root.withdraw()
    root.wm_attributes('-topmost', 1)
    filePath = askdirectory(title='Select Folder to Download Course Files to') 

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
    while(True):
        time.sleep(2)
        progressRequestRAW = requests.get(f'https://webcourses.ucf.edu/api/v1/progress/{progressID}', headers = headers)
        progressRequest = progressRequestRAW.json()
        
        progressBar = progressRequest['completion']
        print(str(progressBar) + '%')
        if(str(progressRequest['workflow_state']) == 'completed'):
            break
    
    

    #gets paginated list for content export
    contentURLRAW = requests.get(f'https://webcourses.ucf.edu/api/v1/courses/{courseID}/content_exports/{contentID}', headers=headers)
    contentURL = contentURLRAW.json()

    
    print(contentURL)
    #gets download url and file name from paginated list, and assign save path to the os to download the export to
    downloadURL = contentURL['attachment']['url']
    fileName = contentURL['attachment']['filename']
    savePath = os.path.join(filePath, fileName)
    
    # downloadContent = requests.get(downloadURL)
    
    # #Download File from URL and save to Directory
    # with open(savePath, 'wb') as file:
    #     file.write(downloadContent.content)
    
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
    os.startfile(filePath)
    root.destroy()
    
    
    
    