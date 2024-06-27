import PIL
import numpy as np
from PIL import Image, ImageDraw


# Задача 1
def triangle(img, x0, y0, x1, y1, x2, y2, thickness, color, fill_color):
    draw = ImageDraw.Draw(img)
    filler=None
    if fill_color != None:
        filler = tuple(fill_color)
    draw.polygon([(x0, y0), (x1, y1), (x2, y2)], fill=filler,outline = tuple(color), width=thickness)
    return img

# Задача 2
def change_color(img, color):
    new_img=img
    w = img.size[0]
    h = img.size[1]
    k = dict()
    for i in range(h):
        for j in range(w):
            pix_color=new_img.getpixel((j, i))
            if pix_color in k:
                k[pix_color]+=1
            else:
                k[pix_color]=1
    max_color = max(k, key=k.get)
    drawing = ImageDraw.Draw(new_img)
    for i in range(h):
        for j in range(w):
            if new_img.getpixel((j, i)) == max_color:
                drawing.point((j, i), tuple(color))
    return new_img




# Задача 3
def collage(img, N, M):
    w = img.size[0]
    h = img.size[1]
    new_w = w * M
    new_h = h * N
    new_img = Image.new('RGB', (new_w, new_h), 'black')
    for i in range(0, N):
        for j in range(0, M):
            new_img.paste(img, (j * w, i * h))
    return new_img