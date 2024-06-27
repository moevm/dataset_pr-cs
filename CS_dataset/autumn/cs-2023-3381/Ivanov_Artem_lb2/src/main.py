from PIL import Image, ImageDraw
import numpy as np
    
# Задача 1============================================================================
def user_func(image, x0, y0, x1, y1, fill, width):
    drawing = ImageDraw.Draw(image)
    drawing.line((x0, y0, x1, y1), fill = fill, width = width)
    return image

# Задача 2============================================================================
def check_coords(image, x0, y0, x1, y1):
    width, height = image.size
    if (x0 < x1 and y0 < y1 and x0 >= 0 and y0 >= 0 and x1 <= width and y1 <= height):
           return True
    return False

def set_black_white(image, x0, y0, x1, y1):
    if check_coords(image, x0, y0, x1, y1):
        cropped_image = image.crop((x0, y0, x1, y1))
        cropped_image = cropped_image.convert('1')
        image.paste(cropped_image, (x0, y0))
        return image
    return image

# Задача 3============================================================================
def find_largest_rect(image, color):
    width, height = image.size
    arr = np.array(image).tolist()
    for i in range(height):
        for j in range(width):
            arr[i][j] = int(arr[i][j] == list(color))
    arr = np.array(arr)

    # считаем максимальную высоту
    for i in range(1, height):
        for j in range(width):
            if arr[i][j] == 0:
                arr[i][j] = 0
            else:
                arr[i][j] += arr[i - 1][j]

    # находим максимальную площадь
    max_area = 0
    coordinates = (0, 0, 0, 0)
    for i in range(height):
        area = 0
        for k in set(arr[i]):
            for j in range(width):
                if k <= arr[i][j]:
                    area += k

                if j == width - 1 or arr[i][j + 1] < k:
                    if max_area < area:
                        max_area = area
                        # x0, y0, x1, y1
                        coordinates = (j - area // k + 1, i - k + 1, j, i)
                    area = 0

    return coordinates


def find_rect_and_recolor(image, old_color, new_color):
    coords = find_largest_rect(image, old_color)

    if coords == (0, 0, 0, 0):
        return image

    arr = np.array(image)
    arr[coords[1]:coords[3] + 1, coords[0]:coords[2] + 1, :3] = list(new_color)
    image = Image.fromarray(arr)

    return image
