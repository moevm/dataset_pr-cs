import PIL
import math

from PIL import Image, ImageDraw


# Задача 1
def user_func(image, x0, y0, x1, y1, fill, width):
    drawing = ImageDraw.Draw(image)
    drawing.line((x0,y0,x1,y1),fill,width)
    return image

# Задача 2
def check_coords(image, x0, y0, x1, y1):
    width,height = image.size
    return (x0 >= 0) and (x1 >= 0) and (y0 >= 0) and (y1 >= 0) and (x1 > x0) and (y1 > y0) and (x1 < width) and (y1 < height)
    
def set_black_white(image, x0, y0, x1, y1):
    if not check_coords(image,x0,y0,x1,y1):
        return image
    area = (x0,y0,x1,y1)
    cropped_area = image.crop(area)
    black_white_cropped_area = cropped_area.convert("1")
    image.paste(black_white_cropped_area,area)
    return image

# Задача 3
def find_rect_and_recolor(image, old_color, new_color):
    copy_image = image.copy()
    pixels = copy_image.load()
    res_pixels = image.load()
    width,height = image.size

    max_rectangle_coords = (0,0,0,0)
    max_rectangle_area = 0
    for x in range(width):
        for y in range(height):
            if pixels[x,y] == old_color:
                rectangle_coords = flood_fill(x,y,width,height,pixels,old_color)
                coord_area = (rectangle_coords[2] - rectangle_coords[0]) * (rectangle_coords[3] - rectangle_coords[1]) # площадь прямоугольника
                if coord_area > max_rectangle_area:
                    max_rectangle_coords = rectangle_coords
                    max_rectangle_area = coord_area
    for x in range(max_rectangle_coords[0],max_rectangle_coords[2]):
        for y in range(max_rectangle_coords[1],max_rectangle_coords[3]):
                res_pixels[x,y] = new_color
    return image


def flood_fill(x, y, width, height, pixels, old_color):
    stack = [(x,y)]
    min_coord = [width,height] # минимальные координаты по x и y
    max_coord = [0,0] # максимальные координаты по x и y
    while stack:
        current_x,current_y = stack.pop()
        if 0 <= current_x < width and 0 <= current_y < height:
            if pixels[current_x,current_y] == old_color:
                pixels[current_x,current_y] = (0,0,0,0) # изменяет цвет, чтобы не было повторной обработки пикселя
                min_coord[0] = min(min_coord[0],current_x)
                min_coord[1] = min(min_coord[1],current_y)
                max_coord[0] = max(max_coord[0],current_x)
                max_coord[1] = max(max_coord[1],current_y)
                stack.append((current_x,current_y + 1)) #добавляются координаты "соседних" пикселей и после уже они проходят по циклу
                stack.append((current_x,current_y - 1))
                stack.append((current_x + 1,current_y))
                stack.append((current_x - 1,current_y))
    return (min_coord[0],min_coord[1],max_coord[0] + 1, max_coord[1] + 1)
