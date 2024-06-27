import numpy as np
from collections import Counter
from PIL import Image, ImageDraw

def triangle(img, x0, y0, x1, y1, x2, y2, thickness, color, fill_color):
    drawing = ImageDraw.Draw(img)
    koord = [(x0, y0),(x1, y1),(x2, y2)]
    if fill_color is None:
        drawing.polygon(koord, outline=tuple(color), width=thickness)
    else:
        drawing.polygon(koord, fill=tuple(fill_color), outline=tuple(color), width=thickness)
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
    a, b = img.size
    img1 = Image.new("RGB", (a * M, b * N))
    for i in range(M):
        for j in range(N):
            img1.paste(img, (i * a, j * b))
    return img1