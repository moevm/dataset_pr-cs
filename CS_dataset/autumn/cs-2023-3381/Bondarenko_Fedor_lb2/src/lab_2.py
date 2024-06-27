import numpy
from PIL import Image, ImageDraw


# Задача 1
def user_func(image, x0, y0, x1, y1, fill, width):
    drawing = ImageDraw.Draw(image)
    drawing.line((x0, y0, x1, y1), fill, width)

    return image


# Задача 2
def check_coords(image, x0, y0, x1, y1):
    if ((x0 >= 0 and y0 >= 0) and (x0 < x1) and (y0 < y1) and (x1 <= image.size[0] and y1 <= image.size[1])):
           return True
    return False


def set_black_white(image, x0, y0, x1, y1):
    if check_coords(image, x0, y0, x1, y1):
        image.paste(image.crop((x0, y0, x1, y1)).convert('1'), (x0, y0))
    return image


# Задача 3
def find_the_biggest_rectangle_to_recolor(image, old_color):
    
    field = numpy.zeros((image.size[1], image.size[0]))
    for y in range(image.size[1]):
        for x in range(image.size[0]):
            if image.getpixel((x, y)) == old_color:
                field[y][x] = 1

    vertical = numpy.array(field)

    for y in range(1, len(vertical)):
        for x in range(len(vertical[0])):
            if field[y][x] == 1:
                vertical[y][x] += vertical[y - 1][x]

    vertical_area = []
    coordinates = tuple()
    for y in range(len(vertical)):
        area = 0
        count = 1
        for x in range(len(vertical[0]) - 1):
            if vertical[y][x] != 0 and vertical[y][x + 1] != 0:
                if vertical[y][x] == vertical[y][x + 1]:
                    count += 1
                    area = count * vertical[y][x]
                    vertical_area.append(area)
                    if area == max(vertical_area):
                        coordinates = (int(x + 2 - count), int(y - vertical[y][x] + 1), int(x + 1), int(y))
                elif vertical[y][x] != vertical[y][x + 1]:
                    count = 1
            elif vertical[y][x] == 0 or vertical[y][x + 1] == 0:
                count = 1

    return coordinates


def find_rect_and_recolor(image, old_color, new_color):

    coordinates = find_the_biggest_rectangle_to_recolor(image, old_color)

    draw = ImageDraw.Draw(image)
    draw.rectangle(coordinates, new_color)

    return image

