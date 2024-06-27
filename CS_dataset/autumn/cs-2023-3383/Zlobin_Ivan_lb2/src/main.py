from PIL import Image, ImageDraw
import numpy as np
def user_func(image, x0, y0, x1, y1, fill, width):
    draw=ImageDraw.Draw(image)
    draw.line((x0,y0,x1,y1), fill=fill, width=width)
    return image


# Задача 2
def check_coords(image, x0, y0, x1, y1):
    if 0<=x0 and 0<=y0 and x0<x1 and x1<image.size[0] and y0<y1 and y1<image.size[1]:
        return True
    else:
        return False


def set_black_white(image, x0, y0, x1, y1):
    if check_coords(image, x0,y0,x1,y1)==False:
        return image
    conv=image.crop((x0,y0,x1,y1))
    conv=conv.convert('1')
    image.paste(conv, (x0,y0,x1,y1))
    return image


# Задача 3
def find_coordinates(array):
    ans = 0
    x0, y0, x1, y1 = 0, 0, 0, 0
    for i in range(len(array)):
        for j in range(len(array[i])):
            if array[i][j] == 0:
                for width in range(i, len(array)):
                    if array[width][j] != 0:
                        width -= 1
                        break
                for height in range(j, len(array[i])):
                    if array[i][height] != 0:
                        height -= 1
                        break
                if ans < (width - i + 1) * (height - j + 1):
                    ans = (width - i + 1) * (height - j + 1)
                    y0, x0, y1, x1 = i, j, width, height
    return x0, y0, x1, y1
def find_rect_and_recolor(image, old_color, new_color):
    old_color=list(old_color)
    array = np.array(image).tolist()
    for i in range(len(array)):
        for j in range(len(array[i])):
            if array[i][j] == old_color:
                array[i][j] = 0
            else:
                array[i][j] = 1
    coordinates=find_coordinates(array)
    draw=ImageDraw.Draw(image)
    draw.rectangle(coordinates, new_color)
    return image
