from PIL import Image, ImageDraw
import numpy as np
# Задача 1
def user_func(image, x0, y0, x1, y1, fill, width):
    draw = ImageDraw.Draw(image)
    draw.line(((x0, y0), (x1, y1)), fill, width)
    return image

# Задача 2
def check_coords(image, x0, y0, x1, y1):
    size_x = image.size[0]
    size_y = image.size[1]
    if(x0 > 0 and y0 > 0 and x1 > 0 and y1 > 0) and (x1 > x0 and y1 > y0) and (x1 < size_x and y1 < size_y):
        return True
    else:
        return False
def set_black_white(image, x0, y0, x1, y1):
    if check_coords(image, x0, y0, x1, y1):
        converted_image = image.crop((x0, y0, x1, y1))
        converted_image = converted_image.convert("1")
        image.paste(converted_image, (x0, y0))
    return image

# Задача 3
def find_rect_and_recolor(image, old_color, new_color):
    color = list(old_color)
    array = np.array(image).tolist()
    for i in range(len(array)):
        for j in range(len(array[i])):
            array[i][j] = int(array[i][j] == color)
    array = np.array(array)
    for i in range(1, len(array)):
        for j in range(len(array[i])):
            if array[i][j] == 1:
                array[i][j] += array[i-1][j]
    max_size = 0
    coords = (0, 0, 0, 0)
    for i in range(len(array)):
        curr_size = 0
        last_j = 0
        for j in range(len(array[i])-1):
            curr_size += array[i][j]
            if curr_size > max_size:
                max_size = curr_size
                coords = (j - (max_size // array[i][j]) + 1, i - array[i][j] + 1, j, i)
            if array[i][j] != array[i][j+1]:
                curr_size = 0
            last_j = j
        if array[i][last_j] == array[i][last_j+1]:
            curr_size += array[i][last_j+1]
            if curr_size > max_size:
                max_size = curr_size
                coords = (last_j - (max_size // array[i][last_j+1]) + 1, i - array[i][last_j+1] + 1, last_j+1, i)
    array = np.array(image).tolist()
    for i in range(coords[1], coords[3]+1):
        for j in range(coords[0], coords[2]+1):
            array[i][j] = new_color
    image = Image.fromarray(np.uint8(array))
    return image
