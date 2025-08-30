from PIL import ImageOps,Image
import sys
def main():
    command_check()
    try:
        img1_shirt = Image.open("shirt.png")
        img2_person = Image.open(sys.argv[1])
        person_resize = ImageOps.fit(img2_person,img1_shirt.size,method=Image.Resampling.BICUBIC,bleed=0.0,centering=(0.5,0.5))
        person_resize.paste(img1_shirt,(0,0),img1_shirt)
        person_resize.save(sys.argv[2])
    except FileNotFoundError:
        sys.exit(f"Invalid Input")


def command_check():
 formats = ['jpg','jpeg' ,'png']
 if  len(sys.argv) < 3  :
     sys.exit("Too few command-line arguments")
 if len(sys.argv) > 3  :
     sys.exit("Too many command-line arguments")
 if not sys.argv[1].lower().endswith(tuple(formats)):
     sys.exit(f"Invalid Input")
 for format in formats:
     if not sys.argv[1].lower().endswith(format) == sys.argv[2].lower().endswith(format):
         sys.exit("Input and output have different extensions")
 

if __name__ ==  "__main__":
    main()
