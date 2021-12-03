#This program was made to convert 100x75px png images into an Edputer compatible data format

from PIL import Image
import sys
img = Image.open(sys.argv[1])
rgb = img.convert("RGB")
sequence=[]
for y in range(75):
  for x in range(100):
    c=rgb.getpixel((x,y))
    sequence = sequence + [(int(c[0]/85)<<4)|(int(c[1]/85)<<2)|(int(c[2]/85))]    
print(sequence)


    
