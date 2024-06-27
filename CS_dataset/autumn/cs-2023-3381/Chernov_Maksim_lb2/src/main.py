import numpy as np
from PIL import *
# Задача 1
def triangle(img, x0, y0, x1, y1, x2, y2, thickness, color, fill_color):
    draw = ImageDraw.Draw(img)
    if fill_color == None:
        draw.polygon([(x0,y0), (x1, y1), (x2,y2)], fill = None, outline = tuple(color), width=thickness)
    else:
        draw.polygon([(x0,y0), (x1, y1), (x2,y2)], fill = tuple(fill_color), outline = tuple(color), width=thickness)
    return img
# Задача 2
def change_color(img, color):
    newimg = img
    x, y = img.size
    count_pix = dict()
    for i in newimg.getdata():
        if i in count_pix:
            count_pix[i] += 1
        else:
            count_pix[i] = 1
    maximumcolor = max(count_pix, key=count_pix.get)
    draw = ImageDraw.Draw(newimg)
    for i in range (x):
        for j in range (y):
            if newimg.getpixel((i, j)) == maximumcolor:
                draw.point((i, j), tuple(color))
    return newimg
# Задача 3
def collage(img, N, M):
    w, h = img.size
    newimg = Image.new("RGB", (w * M, h * N), 'white')
    w1, h1 = newimg.size
    for i in range (0, w1, w):
    	for j in range (0, h1, h):
    	    newimg.paste(img, (i, j))
    return newimg
