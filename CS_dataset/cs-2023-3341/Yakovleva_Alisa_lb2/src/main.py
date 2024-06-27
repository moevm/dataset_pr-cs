import PIL
import numpy as np
from PIL import Image, ImageDraw

# Задача 1
def user_func(image, x0, y0, x1, y1, fill, width):
    ImageDraw.Draw(image).line(((x0,y0),(x1,y1)), fill, width)
    return image

# Задача 2
def check_coords(image, x0, y0, x1, y1):
    return (0 <= x0 < x1 <= image.size[0]) and (0 <= y0 < y1 <= image.size[1])

def set_black_white(image, x0, y0, x1, y1):
    if check_coords(image, x0, y0, x1, y1):
        image.paste(image.crop((x0, y0, x1, y1)).convert("1"), (x0, y0))
    return image

# Задача 3
def find_rect_and_recolor(image, old_color, new_color):
    pixdata = image.copy().load()
    width, height, max_s = image.size[0], image.size[1], 0  
    for x in range(width):
        for y in range(height):
            if pixdata[x, y] == old_color:
                coords = find_rect(x, y, width, height, pixdata, old_color)
                s = (coords[2] - coords[0] + 1) * (coords[3] - coords[1] + 1)
                if s > max_s:
                    max_s = s
                    coords_max = coords
    res_img = image.load()                    
    for x in range(coords_max[0], coords_max[2] + 1):
        for y in range(coords_max[1], coords_max[3] + 1):
            res_img[x, y] = new_color
    return image

def find_rect(x, y, width, height, pixdata, old_color):
    x0, y0 = width, height
    x2, y2 = 0, 0
    curr = [(x, y)]
    while len(curr)>0:
        x1, y1 = curr.pop()
        if (0 <= x1 < width and 0 <= y1 < height and pixdata[x1, y1] == old_color):
            x0 = min(x0, x1)
            y0 = min(y0, y1)
            x2 = max(x2, x1)
            y2 = max(y2, y1)
            curr +=[(x1-1,y1),(x1+1,y1),(x1,y1-1),(x1,y1+1)]
            pixdata[x1, y1] = (0, 0, 0)
    return (x0, y0, x2, y2)
