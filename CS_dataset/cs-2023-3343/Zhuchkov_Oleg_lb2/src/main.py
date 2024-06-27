from PIL import Image, ImageDraw


# Задача 1
def user_func(image, x0, y0, x1, y1, fill, width):
    ImageDraw.Draw(image).line((x0, y0, x1, y1), fill, width)
    return image


# Задача 2
def check_coords(image, x0, y0, x1, y1):
    return all((0 <= x0 <= image.width, 0 <= x1 <= image.width,
                0 <= y0 <= image.height, 0 <= y1 <= image.height))


def set_black_white(image, x0, y0, x1, y1):
    if not check_coords(image, x0, y0, x1, y1):
        return image
    grayscale_area = image.crop((x0, y0, x1, y1)).convert("1")
    image.paste(grayscale_area, (x0, y0))
    return image


# Задача 3
def find_biggest_rectangle(image, color):
    rect_coords = (0,0,0,0)
    max_area = 1
    pixels = image.load()
    for x1 in range(image.width):
        for y1 in range(image.height):
            if pixels[x1, y1] != color:
                continue
            x2, y2 = x1, y1
            while x2 < image.width and pixels[x2,y1] == color:
                x2 += 1
            x2 -= 1
            while y2 < image.height and pixels[x1,y2] == color:
                y2 += 1
            y2 -= 1
            area = (x2 - x1 + 1) * (y2 - y1 + 1)
            if area > max_area:
                rect_coords = (x1, y1, x2, y2)
                max_area = area
    return rect_coords


def find_rect_and_recolor(image, old_color, new_color):
    rect_coords = find_biggest_rectangle(image, old_color)
    ImageDraw.Draw(image).rectangle(rect_coords, new_color)
    return image