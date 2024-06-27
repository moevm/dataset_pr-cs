import numpy as np
from PIL import Image, ImageDraw


def user_func(image, x0, y0, x1, y1, fill, width):
    Drawing = ImageDraw.Draw(image)
    Drawing.line([(x0, y0), (x1, y1)], fill, width)
    return image

def check_coords(image, x0, y0, x1, y1):
    x, y = image.size
    return (0 <= x0 < x1 and 0 <= y0 < y1 and x1 <= x and y1 <= y)

def set_black_white(image, x0, y0, x1, y1):
    if check_coords(image, x0, y0, x1, y1):
        crop = image.crop(((x0, y0, x1, y1))).convert("1")
        image.paste(crop, (x0, y0))
    return image

def find_rect(image, color):
    im = image.load()
    sizex, sizey = image.size
    arr = np.zeros((sizex, sizey, 2), dtype=int)
    s = 0
    rect = (0, 0, sizex, sizey)
    for i in range(sizex):
        for j in range(sizey):
            if im[i, j] == color:
                arr[i][j] = [1, 1]
                if i > 0:
                    arr[i][j][0] += arr[i-1][j][0]
                if j > 0:
                    arr[i][j][1] += arr[i][j-1][1]
                if s < arr[i][j][0] * arr[i][j][1]:
                    s = arr[i][j][0] * arr[i][j][1]
                    rect = (i - arr[i][j][0] + 1, j - arr[i][j][1] + 1, i + 1, j + 1)
    return rect
    

def find_rect_and_recolor(image, old_color, new_color):
    rect = find_rect(image, old_color)
    size = (rect[2] - rect[0], rect[3] - rect[1])
    colored_rect = Image.new("RGB", size, new_color)
    image.paste(colored_rect, (rect[0], rect[1]))
    return image
