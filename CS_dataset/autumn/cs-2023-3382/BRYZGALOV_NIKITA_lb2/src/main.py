import PIL
import numpy as np
from PIL import Image, ImageDraw

# Задача 1
def user_func(image, x0, y0, x1, y1, fill, width):
    drawing = ImageDraw.Draw(image)
    coordinates = ((x0, y0), (x1, y1))
    drawing.line(coordinates, fill, width)
    return image

# Задача 2
def check_coords(image, x0, y0, x1, y1):
    width, height = image.size
    return (0 <= x0 <= x1 <= width) and (0 <= y0 <= y1 <= height)

def set_black_white(image, x0, y0, x1, y1):
    if not check_coords(image, x0, y0, x1, y1): return image
    else:
        region = (x0, y0, x1, y1)
        cropped_image = image.crop(region)
        black_white_image = cropped_image.convert('1')
        image.paste(black_white_image, region)
        return image

# Задача 3
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
                y1, x1 = find_max_rectangle(img_array, visited, y, x, old_color)
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

def find_max_rectangle(img_array, visited, y0, x0, old_color):
    height, width, _ = img_array.shape
    y1 = y0
    x1 = x0
    check_pixels = [[y0, x0]]
    while check_pixels:
        y, x = check_pixels.pop()
        if (visited[y, x] != 1) and tuple(img_array[y, x]) == old_color:
            y1 = max(y1, y)
            x1 = max(x1, x)
            visited[y, x] = 1
            if y < height-1: check_pixels += [[y+1, x]]
            if x < width-1: check_pixels += [[y, x+1]]
    return y1, x1
