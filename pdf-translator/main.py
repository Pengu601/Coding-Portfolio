#pdf translator 
#translate pdf docs to another language with a custom GUI
import sys
import glob
import pytesseract
from pdf2image import convert_from_path
from translate import Translator
#import requests
from langdetect import detect
#from windowBuilder import *
#from langdetect import detect_langs
def main():

    pdfs = glob.glob("")

    for pdf_path in pdfs:
        pages = convert_from_path(pdf_path, 500)

        for pageNum, imgBlob in enumerate(pages):
            text = pytesseract.image_to_string(imgBlob, lang = "eng")

            with open(f'{pdf_path[:-4]}_page{pageNum}.txt', 'w') as the_file:
                the_file.write(text)




    string = "usted tiene unos ojos muy bonitos mi señora"
    baseLang = detect(string)
    print(baseLang)
    translator = Translator(from_lang=baseLang, to_lang="en")
    

    translation = translator.translate(string)
    print(translation)

    

main()