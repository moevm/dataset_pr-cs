import numpy as np
from PIL import Image, ImageDraw

# Задача 1
def user_func(image, x0, y0, x1, y1, fill, width):
    draw_line = ImageDraw.Draw(image)
    draw_line.line(((x0, y0), (x1, y1)), fill, width)
    return image

# Задача 2
def check_coords(image, x0, y0, x1, y1):
    width = image.size[0]
    height = image.size[1]
    if (x1 < x0 or y1 < y0): return False
    elif (x1 > width or y1 > height): return False
    elif (x0 < 0 or y0 < 0): return False
    return True

def set_black_white(image, x0, y0, x1, y1):
    if (not check_coords(image, x0, y0, x1, y1)):
        return image
    croped_img = image.crop((x0, y0, x1, y1))
    bw_img = croped_img.convert("1")
    image.paste(bw_img, (x0, y0, x1, y1))
    return image

# Задача 3
def find_rect_and_recolor(image, old_color, new_color):
    width, height = image.size
    max_rectangle_size = 0
    max_rectangle_position = (0, 0, 0, 0)  # (left, top, right, bottom)
    visited = np.zeros((width, height))
    # Проходим по пикселям изображения
    for x in range(width):
        for y in range(height):
            if visited[x, y] != 1:
                current_color = image.getpixel((x, y))
                if current_color == old_color:
                    left, top, right, bottom = x, y, x, y
                    width, height = image.size

                    while right < width and image.getpixel((right, y)) == old_color:
                        visited[right, y] = 1

                        while bottom < height and image.getpixel((right, bottom)) == old_color:
                            visited[right, bottom] = 1
                            bottom += 1
                        right += 1

                    rectangle_size, rectangle_position = (right - left) * (bottom - top), (left, top, right - 1, bottom - 1)
            
                    if rectangle_size > max_rectangle_size:
                        max_rectangle_size = rectangle_size
                        max_rectangle_position = rectangle_position

    # Меняем цвет самого большого прямоугольника
    draw = ImageDraw.Draw(image)
    draw.rectangle(max_rectangle_position, fill=new_color)
    return image
