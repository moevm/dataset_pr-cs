from PIL import Image, ImageDraw
import numpy as np

def user_func(image, x0, y0, x1, y1, fill, width):
    drawing = ImageDraw.Draw(image)
    coordinates = (x0, y0, x1, y1)
    drawing.line(coordinates, fill, width)
    return image

def check_coords(image, x0, y0, x1, y1):
    width, height = image.size
    return (width >= x1) and (x1 > x0) and (x0 >= 0) and (height >= y1) and (y1 > y0) and (y0 >= 0)

def set_black_white(image, x0, y0, x1, y1):
    if check_coords(image, x0, y0, x1, y1):
        save_image = image.crop((x0,y0, x1, y1))
        save_image = save_image.convert('1')
        image.paste(save_image, (x0, y0))
    return image

def find_rect_and_recolor(image, old_color, new_color):
    array = np.array(image).tolist() 
    for i in range(len(array)):
        for j in range(len(array[i])):
            array[i][j] = int(array[i][j] == list(old_color)) 
    array = np.array(array) 
    
    for i in range(1, len(array)):
        for j in range(len(array[i])):
            if array[i][j] == 0:
                array[i][j] = 0
            else:
                array[i][j] += array[i - 1][j]
    
    max_rectangle = 0
    coordinates = (0, 0, 0, 0)
    for i in range(len(array)):
        rectangle = 0
        for k in set(array[i]):
            for j in range(len(array[i])):
                if k <= array[i][j]:
                    rectangle += k

                if j == len(array[i]) - 1 or array[i][j + 1] < k:
                    if max_rectangle < rectangle:
                        max_rectangle = rectangle
                        coordinates = (j - rectangle // k + 1, i - k + 1, j, i)
                    rectangle = 0
    
    if coordinates == (0, 0, 0, 0):
        return image

    array = np.array(image)
    array[coordinates[1]:coordinates[3] + 1, coordinates[0]:coordinates[2] + 1, :3] = list(new_color)
    image = Image.fromarray(array)
    return image