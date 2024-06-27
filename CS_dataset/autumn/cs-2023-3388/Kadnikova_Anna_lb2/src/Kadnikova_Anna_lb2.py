import numpy as np
from PIL import Image,  ImageDraw
import collections

def triangle(img, x0,y0,x1,y1,x2,y2, thickness, color, fill_color ):
    drawing = ImageDraw.Draw(img)
    if fill_color == None:
        drawing.polygon([(x0,y0), (x1, y1), (x2,y2)], fill = None, outline = tuple(color), width=thickness)
    else:
        drawing.polygon([(x0,y0), (x1, y1), (x2,y2)], fill = tuple(fill_color), outline = tuple(color), width=thickness)
    return img


def change_color(img, color):
    image = img
    x, y = img.size
    count_pix = collections.Counter(image.getdata())
    max_color = max(count_pix, key=count_pix.get)
    drawing = ImageDraw.Draw(image)
    for i in range (x):
        for j in range (y):
            if image.getpixel((i, j)) == max_color:
                drawing.point((i, j), tuple(color))
    return image

def collage(img, N, M):
    width, height = img.size
    image = Image.new("RGB", (width * M, height * N), 'white')
    currWidth, currHeight = image.size
    for i in range (0, currWidth, width):
        for j in range (0, currHeight, height):
            image.paste(img, (i, j))   
    return image

