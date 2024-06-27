import numpy as np
import PIL
from PIL import Image, ImageDraw

def triangle(img, x0, y0, x1, y1, x2, y2, thickness, color, fill_color):
    drawing = ImageDraw.Draw(img)
    if fill_color == None:
        drawing.polygon([(x0,y0), (x1, y1), (x2,y2)], fill = None, outline = tuple(color), width=thickness)
    else:
        drawing.polygon([(x0,y0), (x1, y1), (x2,y2)], fill = tuple(fill_color), outline = tuple(color), width=thickness)
    return img

def change_color(img, color):
    img1 = img
    x, y = img.size
    count_pix = dict()
    for i in img1.getdata():
        if i in count_pix:
            count_pix[i] += 1
        else:
            count_pix[i] = 1
    max_color = max(count_pix, key=count_pix.get)
    drawing = ImageDraw.Draw(img1)
    for i in range (x):
        for j in range (y):
            if img1.getpixel((i, j)) == max_color:
                drawing.point((i, j), tuple(color))
    return img1

def collage(img, N, M):
    width, height = img.size
    img1 = Image.new("RGB", (width * M, height * N), 'white')
    width1, height1 = img1.size
    for i in range (0, width1, width):
    	for j in range (0, height1, height):
    	    img1.paste(img, (i, j))
    return img1

