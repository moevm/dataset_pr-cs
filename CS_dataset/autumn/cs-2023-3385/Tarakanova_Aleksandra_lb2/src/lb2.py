from PIL import Image, ImageDraw
import numpy as np

# Задача 1
def user_func(image, x0, y0, x1, y1, fill, width):
    color=tuple(fill)
    drawing = ImageDraw.Draw(image)
    drawing.line(((x0, y0), (x1, y1)), color, width)
    return image


# Задача 2
def check_coords(image, x0, y0, x1, y1):
    x, y = image.size[0], image.size[1]

    if not (0 <= x0 < x and 0 <= y0 < y):
        return False
    if not (0 < x1 < x and 0 < y1 < y):
        return False

    if not (x0 < x1 and y0 < y1):
        return False

    return True


def set_black_white(image, x0, y0, x1, y1):
    if not check_coords(image, x0, y0, x1, y1):
        return image
    cr_image = image.crop((x0, y0, x1, y1))
    cr_image = cr_image.convert("1")
    image.paste(cr_image, (x0, y0))
    return image


# Задача 3
def find(image, color):
    arr = np.array(image)
    mask = np.all(arr == color, axis=-1)
    arr = mask.astype(int)
    for i in range(1, len(arr)):
        for j in range(len(arr[i])):
            arr[i][j] *= arr[i - 1][j]+1 
    max_s = 0
    coordinates = (0, 0, 0, 0)
    for i in range(len(arr)):
        s = 0
        for k in set(arr[i]):
            for j in range(len(arr[i])):
                if k <= arr[i][j]:
                    s += k
                if j == len(arr[i]) - 1 or arr[i][j + 1] < k:
                    if max_s < s:
                        max_s = s
                        # x0, y0, x1, y1
                        coordinates = (j - s // k + 1, i - k + 1, j, i)
                    s = 0
    return coordinates




def find_rect_and_recolor(image, old_color, new_color):
    obl = find(image, old_color)
    if obl == (0, 0, 0, 0):
        return image
    arr = np.array(image)
    arr[obl[1]:obl[3] + 1, obl[0]:obl[2] + 1, :3] = list(new_color)
    image = Image.fromarray(arr)
    return image

