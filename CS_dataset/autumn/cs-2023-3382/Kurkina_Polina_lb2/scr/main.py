import math
from PIL import Image, ImageDraw
import numpy as np
# draw line

def user_func(image, x0, y0, x1, y1, fill, width):
    drawing = ImageDraw.Draw(image)
    drawing.line(((x0, y0), (x1, y1)), fill, width)
    return image
def check_coords(image, x0, y0, x1, y1):
    width, height = image.size
    return (0 <= x0 <= x1 <= width) and (0 <= y0 <= y1 <= height)
def set_black_white(image, x0, y0, x1, y1):
    if not(check_coords(image, x0, y0, x1, y1)):
        return image
    else:
        img1 = image.crop((x0, y0, x1, y1))
        img2 = img1.convert('1')
        image.paste(img2, (x0, y0))
        return image

def find_rect_and_recolor(image, old_color, new_color):
    img_array = np.array(image)
    height, width, _ = img_array.shape
    visited = np.zeros((height, width))
    max_rect_y0 = 0
    max_rect_y1 = 0
    max_rect_x0 = 0
    max_rect_x1 = 0
    max_rect_area = 0
    for y in range(height):
        for x in range(width):
            if (visited[y, x] != 1) and tuple(img_array[y, x]) == old_color:
                y0, x0 = y, x
                y1, x1 = find_rectangle(img_array, visited, y, x, old_color)
                rect_area = (y1 - y0 + 1) * (x1 - x0 + 1)
                if rect_area > max_rect_area:
                    max_rect_y0 = y0
                    max_rect_y1 = y1
                    max_rect_x0 = x0
                    max_rect_x1 = x1
                    max_rect_area = rect_area
    img_array[max_rect_y0 : max_rect_y1 + 1, max_rect_x0 : max_rect_x1 + 1] = new_color
    image = Image.fromarray(img_array)
    return image

def find_rectangle(arr_of_img, visited, y0, x0, old_color):
    he, we, col = arr_of_img.shape
    y1 = y0
    x1 = x0
    x = x0+1
    y = y0+1
    while (x<we) and (y<he) and (tuple(arr_of_img[y, x]) == old_color):
        x1 = x
        visited[y, x] = 1
        x+=1
    x -= 1
    while (x<we) and (y<he) and (tuple(arr_of_img[y, x]) == old_color):
        y1 = y
        visited[y, x] = 1
        y+=1
    for i in range(y0, y1):
        for j in range(x0, x1):
            visited[i, j] = 1
    return y1, x1
