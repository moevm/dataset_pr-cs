from PIL import ImageDraw
import numpy as np


# Задача 1
def user_func(image, x0, y0, x1, y1, fill, width):
    drawing = ImageDraw.Draw(image)

    drawing.line((x0, y0, x1, y1), fill, width)

    return image


# Задача 2
def check_coords(image, x0, y0, x1, y1):
    img_width, img_height = image.size
    return all(((x0 >= 0), (y0 >= 0), (x1 > x0), (y1 > y0), (img_width >= x1), (img_height >= y1)))


def set_black_white(image, x0, y0, x1, y1):
    if not check_coords(image, x0, y0, x1, y1): 
        return image

    image_to_convert = image.crop((x0, y0, x1, y1))
    image_converted = image_to_convert.convert('1')
    image.paste(image_converted, (x0, y0))

    return image


# Задача 3
def find_max_rect(image, color):
    width, height = image.size
    arr = np.array([[int(image.getpixel((j, i)) == color) for j in range(width)] for i in range(height)])

    for i in range(1, len(arr)):
        for j in range(len(arr[i])):
            if arr[i][j] == 0:
                arr[i][j] = 0
            else:
                arr[i][j] += arr[i-1][j]

    max_area = 0
    coords = (0, 0, 0, 0)
    for i in range(len(arr)):
        cur_area = 0
        for k in set(arr[i]):
            for j in range(len(arr[i])):
                if k <= arr[i][j]:
                    cur_area += k
                if j == len(arr[i]) - 1 or arr[i][j + 1] < k:
                    if max_area < cur_area:
                        max_area = cur_area
                        coords = (j - cur_area // k + 1, i - k + 1, j, i)
                    cur_area = 0

    return coords


def find_rect_and_recolor(image, old_color, new_color):
    coords = find_max_rect(image, old_color)
    drawing = ImageDraw.Draw(image)
    drawing.rectangle(coords, new_color)
    
    return image

