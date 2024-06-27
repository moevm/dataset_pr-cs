import PIL
import numpy as np
import math
from PIL import Image, ImageDraw


def triangle(img, x0, y0, x1, y1, x2, y2, thickness, color, fill_color):
    drawing= ImageDraw.Draw(img)
    if fill_color:
        drawing.polygon(((x0,y0),(x1,y1),(x2,y2)), fill=tuple(fill_color), outline=tuple(color), width = thickness)
    else:
        drawing.polygon(((x0,y0),(x1,y1),(x2,y2)), fill=None, outline=tuple(color), width = thickness)
        
    return img
    
    
    
def change_color(img, color):
    img_new = img
    pixels = img_new.getdata()
    colors = dict()
    for x in pixels:
        if x in colors:
            colors[x] +=1
        else:
            colors[x] = 1
    max_color = max(colors, key=colors.get)
    width,height = img_new.size
    for x in range(width):
        for y in range(height):
            if img_new.getpixel((x,y)) == max_color:
                img_new.putpixel((x,y), tuple(color))
    return img_new

def collage(img, N, M):
    width, height = img.size
    img_new = Image.new('RGB', (width*M, height*N), 'white')
    new_width, new_height = img_new.size
    for x in range(0, new_width, width):
        for y in range(0, new_height, height):
            img_new.paste(img, (x,y))
            
    return img_new

