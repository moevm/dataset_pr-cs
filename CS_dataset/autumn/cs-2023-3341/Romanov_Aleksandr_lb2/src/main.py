import PIL
import numpy as np
from PIL import Image, ImageDraw
def user_func(image, x0, y0, x1, y1, fill, width):
    art = ImageDraw.Draw(image)
    art.line((x0, y0, x1, y1), fill, width)
    return image

def check_coords(image, x0, y0, x1, y1):
    coords = [x0, x1, y0, y1]
    size = image.size
    if all(x>=0 for x in coords):
        if all(x<=size[0] for x in coords[0:2]) and all(x<=size[1] for x in coords[3:]):
            return x1>x0 and y1>y0
               
def set_black_white(image, x0, y0, x1, y1):
    if check_coords(image, x0, y0, x1, y1):
        edit = image.crop((x0,y0,x1,y1))
        edit = edit.convert("1")
        image.paste(edit, (x0,y0))
    return image

def find_rect_and_recolor (image, old_color, new_color):
    pix_data = image.load()
    size = image.size
    wd, hg = size[0], size[1]
    matrix = np.zeros((wd, hg))
    for x in range (wd):
        for y in range(hg):
            if image.getpixel((x, y))  == old_color:
                matrix[x, y] = 1
    max_rect_coordinates = (0, 0, 0, 0)
    max_rect_size = 0

    for x in range (wd):
        for y in range(hg):
            if matrix[x, y]== 1:
                rect_coordinates = filler(x, y, wd, hg, matrix)
                rect_size = (rect_coordinates[2] - rect_coordinates[0]) * (rect_coordinates[3] - rect_coordinates[1])
                if rect_size > max_rect_size:
                    max_rect_size = rect_size
                    max_rect_coordinates = rect_coordinates
    for x in range(max_rect_coordinates[0], max_rect_coordinates[2]):
        for y in range(max_rect_coordinates[1], max_rect_coordinates[3]):
            pix_data[x, y] = new_color
    return image


def filler (x ,y, wd, hg, matrix):
    stack = [(x, y)]
    coord_mn = [wd, hg]
    coord_mx = [0, 0]

    while stack:
        x_cur, y_cur = stack.pop()
        if 0 <= x_cur < wd and 0 <= y_cur < hg and matrix[x_cur, y_cur] == 1:
            matrix[x_cur, y_cur] = 2
            coord_mn = [min(coord_mn[0], x_cur), min(coord_mn[1], y_cur)]
            coord_mx = [max(coord_mx[0], x_cur), max(coord_mx[1], y_cur)]
            stack.append((x_cur + 1, y_cur))
            stack.append((x_cur - 1, y_cur))
            stack.append((x_cur, y_cur + 1))
            stack.append((x_cur, y_cur - 1))
    return (coord_mn[0], coord_mn[1], coord_mx[0]+1, coord_mx[1]+1)

