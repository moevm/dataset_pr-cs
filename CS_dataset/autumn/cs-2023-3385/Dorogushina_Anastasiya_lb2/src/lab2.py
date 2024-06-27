import PIL
from PIL import Image, ImageDraw
import numpy as np


# Задача 1
def user_func(image, x0, y0, x1, y1, fill, width):
    drawing = ImageDraw.Draw(image)
    drawing.line((x0, y0, x1, y1), fill, width)
    return image


# Задача 2
def check_coords(image, x0, y0, x1, y1):
    width, height = image.size
    return width >= x1 > x0 >= 0 and height >= y1 > y0 >= 0

def set_black_white(image, x0, y0, x1, y1):
    if check_coords(image, x0, y0, x1, y1):
        crop_img = image.crop((x0, y0, x1, y1))
        crop_img = crop_img.convert('1')
        image.paste(crop_img, (x0, y0))
    return image


# Задача 3
def find_rect(image, color):
    array = np.array(image).tolist()
    for i in range(len(array)):
        for j in range(len(array[i])):
            array[i][j] = int(array[i][j] == list(color))

    for i in range(1, len(array)):
        for j in range(len(array[i])):
            if array[i][j] != 0:
                array[i][j] += array[i - 1][j]

    coords = (0, 0, 0, 0)
    square_max = 0

    for i in range(len(array)):
        square = 0
        for n in set(array[i]):
            for j in range(len(array[i])):
                if n <= array[i][j]:
                    square += n
                if j == len(array[i]) - 1 or array[i][j + 1] < n:
                    if square > square_max:
                        square_max = square
                        coords = (j - square // n + 1, i - n + 1, j, i)
                    square = 0
    return coords

def find_rect_and_recolor(image, old_color, new_color):
    coords = find_rect(image, old_color)
    if coords != (0, 0, 0, 0):
        array = np.array(image)
        array[coords[1]:coords[3] + 1, coords[0]:coords[2] + 1, :3] = list(new_color)
        image = Image.fromarray(array)
    return image