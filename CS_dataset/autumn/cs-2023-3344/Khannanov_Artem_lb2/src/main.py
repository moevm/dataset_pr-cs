from PIL import Image, ImageDraw


# Задача 1
def user_func(image, x0, y0, x1, y1, fill, width):
    drawing = ImageDraw.Draw(image)
    drawing.line((x0, y0, x1, y1), fill, width)

    return image


# Задача 2
def check_coords(image, x0, y0, x1, y1):
    x, y = image.size
    if (0 <= x0 < x1 <= x) and (0 <= y0 < y1 <= y):
        return True
    return False


def set_black_white(image, x0, y0, x1, y1):
    if check_coords(image, x0, y0, x1, y1):
        image_zone = image.crop((x0, y0, x1, y1)).convert('1')
        image.paste(image_zone, (x0, y0))

    return image


# Задача 3
def find_rect_and_recolor(image, old_color, new_color):
    color_arr = image.load()
    x, y = image.size
    rect_pos = (0, 0, 0, 0)
    max_square = 0

    for x0 in range(x):
        for y0 in range(y):
            if color_arr[x0, y0] == old_color:
                x1, y1 = x0, y0
                while x1 < x and color_arr[x1, y0] == old_color:
                    x1 += 1
                while y1 < y and color_arr[x0, y1] == old_color:
                    y1 += 1
                square = (x1 - x0) * (y1 - y0)
                if square > max_square:
                    max_square = square
                    rect_pos = (x0, y0, x1 - 1, y1 - 1)

    drawing = ImageDraw.Draw(image)
    drawing.rectangle(rect_pos, new_color)

    return image