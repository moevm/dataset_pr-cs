import PIL
import numpy as np
import math
from PIL import Image, ImageDraw
def user_func(image, x0, y0, x1, y1, fill, width):
    draw = ImageDraw.Draw(image)
    draw.line(((x0, y0), (x1, y1)), fill, width)
    return image

def check_coords(image, x0, y0, x1, y1):
    width, height = image.size
    if (x0 < x1 and y0 < y1) and (x0 >= 0 and y0 >= 0) and (x1 <= width and y1 <= height):
        return True
    else:
        return False

def set_black_white(image, x0, y0, x1, y1):
    check = check_coords(image, x0, y0, x1, y1)
    if check is True:
        img = image.crop((x0, y0, x1, y1))
        img = img.convert('1')
        image.paste(img, (x0, y0))
        return image
    else:
        return image

def find_rect_and_recolor(image, old_color, new_color):
    picture = image.load()
    width, height = image.size
    coords_start = (0, 0)
    coords_end = (0, 0)
    max_area = 0
    for x in range(width):
        for y in range(height):
            if picture[x, y] == old_color:
                x_new = x
                y_new = y
                while x_new < width and picture[x_new, y] == old_color:
                    x_new += 1
                while y_new < height and picture[x, y_new] == old_color:
                    y_new += 1
                if (x_new - x) * (y_new - y) > max_area:
                    max_area = (x_new - x) * (y_new - y)
                    coords_start = (x, y)
                    coords_end = (x_new-1, y_new-1)
    draw = ImageDraw.Draw(image)
    draw.rectangle((coords_start, coords_end), new_color)
    return image