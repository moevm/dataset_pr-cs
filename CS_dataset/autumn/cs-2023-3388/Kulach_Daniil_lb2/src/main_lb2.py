import numpy as np
from PIL import Image, ImageDraw

# Задача 1
def triangle(img, x0, y0, x1, y1, x2, y2, thickness, color,
fill_color):
    drawing = ImageDraw.Draw(img)
    if fill_color is None:
        drawing.polygon(((x0, y0), (x1, y1), (x2, y2)), fill=None,
outline=tuple(color), width=thickness)
    else:
        drawing.polygon(((x0, y0), (x1, y1), (x2, y2)),
fill=tuple(fill_color), outline=tuple(color), width=thickness)
    return img
    
# Задача 2
def change_color(img, color):
    color_count = {}
    img1 = img.copy()
    pixels = img1.load()
    for i in range(img1.size[0]):
        for j in range(img1.size[1]):
            if pixels[i, j] not in color_count:
                color_count[pixels[i, j]] = 1
            else:
                color_count[pixels[i, j]] += 1
    max_count_color = max(color_count, key=color_count.get)
    for i in range(img1.size[0]):
        for j in range(img1.size[1]):
            if pixels[i, j] == max_count_color:
                pixels[i, j] = tuple(color)
    return img1
    
# Задача 3
def collage(img, N, M):
    width_img = img.size[0]
    height_img = img.size[1]
    img_new = Image.new("RGB", (width_img * M, height_img * N), (0,
0 ,0))
    new_width = img_new.size[0]
    new_height = img_new.size[1]
    for i in range(0, new_width, width_img):
        for j in range(0, new_height, height_img):
            img_new.paste(img, (i, j))
    return img_new
