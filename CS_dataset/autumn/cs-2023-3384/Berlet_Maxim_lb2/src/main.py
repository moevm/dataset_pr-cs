import PIL
import numpy as np
import math
from PIL import Image, ImageDraw


# Задача 1
def user_func(image, x0, y0, x1, y1, fill, width):
    drawing = ImageDraw.Draw(image)
    drawing.line(((x0, y0), (x1, y1)), fill=fill, width=width)
    return image


# Задача 2
def check_coords(image, x0, y0, x1, y1):
    width = image.width
    height = image.height
    if (x0 >= 0 and y0 >= 0) and (x1 >= 0 and y1 >= 0):
        if (x0 <= width and x1 <= width) and (y0 <= height and y1 <= height):
            if (x1 >= x0) and (y1 >= y0):
                return True
            else:
                return False
        else:
            return False
    else:
        return False


def set_black_white(image, x0, y0, x1, y1):
    if check_coords(image, x0, y0, x1, y1):
        temp = image.crop((x0, y0, x1, y1))
        temp = temp.convert('1')
        image.paste(temp, (x0, y0))
        return image
    else:
        return image


# Задача 3
def find_rect_and_recolor(image, old_color, new_color):
    width = image.width
    height = image.height
    max_area = 0
    largest_rect_coord = (0, 0, 0, 0)
    for x in range(width):
        for y in range(height):
            if image.getpixel((x, y)) == old_color:
                x0, y0 = x, y
                x1, y1 = x, y
                while x1 < width and image.getpixel((x1, y)) == old_color:
                    x1 += 1
                while y1 < height and image.getpixel((x0, y1)) == old_color:
                    y1 += 1
                area = (x1 - x0) * (y1 - y0)
                if area > max_area:
                    max_area = area
                    largest_rect_coord = (x0, y0, x1 - 1, y1 - 1)
    drawing = ImageDraw.Draw(image)
    drawing.rectangle(largest_rect_coord, fill=new_color)
    return image