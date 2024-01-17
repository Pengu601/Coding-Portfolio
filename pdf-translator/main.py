#pdf translator 
#translate pdf docs to another language with a custom GUI
import pytesseract
from translate import Translator
import requests
from langdetect import detect
from windowBuilder import *
#from langdetect import detect_langs
def main():
    string = "usted tiene unos ojos muy bonitos mi señora"
    baseLang = detect(string)
    print(baseLang)
    translator = Translator(from_lang=baseLang, to_lang="en")
    

    translation = translator.translate(string)
    print(translation)

    draw_Canvas()
    

main()