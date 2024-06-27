import numpy
from PIL import Image, ImageDraw

# Задача 1
def user_func(image, x0, y0, x1, y1, fill, width):
    drawing = ImageDraw.Draw(image)
    drawing.line((x0, y0, x1, y1), fill, width)
    return image

# Задача 2
def check_coords(image, x0, y0, x1, y1):
    return ((x0 < x1) and (y0 < y1) and (x0 > 0) and (y0 > 0) and (image.size[0] >= x1) and (image.size[1] >= y1))
def set_black_white(image, x0, y0, x1, y1):
    if not(check_coords(image, x0, y0, x1, y1)):
        return image
    img = image.crop((x0, y0, x1, y1))
    img = img.convert('1')
    image.paste(img, (x0, y0))
    return image

# Задача 3
def find_rect_and_recolor(image, old_color, new_color):
    width = image.size[0]
    height = image.size[1]
    picture = numpy.zeros((height, width))
    for i in range(height):
        for j in range(width):
            if image.getpixel((j, i)) == old_color:
                picture[i][j] = 1
    picture = numpy.array(picture)
    for i in range(1, height):
        for j in range(width):
            if picture[i][j] == 1:
                picture[i][j] += picture[i - 1][j]
    coordinates = (0, 0, 0, 0)
    required_area = 0
    for i in range(height):
        cnt = 0
        now_area = 0
        for j in range(width - 1):
            if picture[i][j] != 0 and picture[i][j + 1] != 0:
                if picture[i][j] == picture[i][j + 1]:
                    cnt += 1
                    now_area = picture[i][j] * (cnt + 1)
                    required_area = max(required_area, now_area)
                    if now_area == required_area:
                        coordinates = (int(j - cnt + 1), int(i - picture[i][j] + 1), int(j + 1), int(i))
                else:
                    cnt = 0
            elif picture[i][j] == 0 or picture[i][j + 1] == 0:
                cnt = 0
    img = ImageDraw.Draw(image)
    img.rectangle(coordinates, new_color)
    return image
