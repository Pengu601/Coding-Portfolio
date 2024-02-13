#pdf translator 
#translate pdf docs to another language with a custom GUI
import sys
import io
import fitz
from PIL import Image
import pytesseract
from translate import Translator
#import requests
from langdetect import detect

#from langdetect import detect_langs

def convert_scanned_pdf_to_text(pdf_path):
    doc = fitz.open(pdf_path)
    text = ""

    for page_num in range(doc.page_count):
        page = doc[page_num]
        image_list = page.get_images(full=True)

        for img_index, img_info in enumerate(image_list):
            base_image = doc.extract_image(img_info)
            image_bytes = base_image["image"]

            image = Image.open(io.BytesIO(image_bytes))
            text += pytesseract.image_to_string(image)

    return text

def main():
    try:
        droppedFile = sys.argv[1]
    except IndexError:
        print("no file dropped")
    
    pdf_path = droppedFile
    print(pdf_path)
    # text_content = convert_scanned_pdf_to_text(pdf_path)

    # with open("output.txt", "w", encoding="utf-8") as output_file:
    #     output_file.write(text_content)

    # print("Conversion complete. Text saved to output.txt.")



    # string = "usted tiene unos ojos muy bonitos mi señora"
    # baseLang = detect(string)
    # print(baseLang)
    # translator = Translator(from_lang=baseLang, to_lang="en")
    

    # translation = translator.translate(string)
    # print(translation)

    

main()