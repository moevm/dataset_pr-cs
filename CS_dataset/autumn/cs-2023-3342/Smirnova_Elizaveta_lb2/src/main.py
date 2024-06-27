from PIL import Image, ImageDraw
import numpy as np

# Задача 1
def user_func(image, x0, y0, x1, y1, fill, width):
    drawing = ImageDraw.Draw(image)
    drawing.line(((x0,y0),(x1,y1)), fill, width, joint=None)
    return image

# Задача 2
def check_coords(image, x0, y0, x1, y1):
    
    if (x0>0 and x1>0 and y0>0 and y1>1 and x1>x0 and y1>y0 and image.size[0]>=x1 and image.size[1]>=y1):
        return True
    else:
        return False
    
def set_black_white(image, x0, y0, x1, y1):
    if (check_coords(image, x0, y0, x1, y1) is True):
        img = image.crop((x0, y0, x1, y1))
        img = img.convert("1")
        image.paste(img, (x0, y0))
    return image

# Задача 3
def find_rect_and_recolor(image, old_color, new_color):
    
    arr = np.array(image).tolist()
    for i in range(len(arr)):
        for j in range(len(arr[i])):
            arr[i][j] = int(arr[i][j] == list(old_color))
    arr = np.array(arr)
    
    
    for i in range(1, len(arr)):
        for j in range(len(arr[i])):
            if arr[i][j] == 0:
                arr[i][j] = 0
            else:
                arr[i][j] += arr[i - 1][j]
    
    max_area = 0
    coordinates = (0, 0, 0, 0)
    for i in range(len(arr)):
        area = 0
        for k in set(arr[i]):
            for j in range(len(arr[i])):
                if k <= arr[i][j]:
                    area += k

                if j == len(arr[i]) - 1 or arr[i][j + 1] < k:
                    if max_area < area:
                        max_area = area
                        coordinates = (j - area // k + 1, i - k + 1, j, i)
                    area = 0
    
    
    if coordinates == (0, 0, 0, 0):
        return image

    arr = np.array(image)
    arr[coordinates[1]:coordinates[3] + 1, coordinates[0]:coordinates[2] + 1, :3] = list(new_color)
    image = Image.fromarray(arr)
    return image
    
