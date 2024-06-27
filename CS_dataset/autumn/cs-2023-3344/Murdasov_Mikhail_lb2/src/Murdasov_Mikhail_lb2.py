import PIL
from PIL import Image, ImageDraw


def user_func(image, x0, y0, x1, y1, fill, width):
    drawing = ImageDraw.Draw(image)
    drawing.line(((x0, y0), (x1, y1)), fill, width)
    return image


def check_coords(image, x0, y0, x1, y1):
    width, height = image.size
    if x0 >= 0 and y0 >= 0 and x1 >= x0 and y1 >= y0 and x0 <= width and y0 <= height and x1 <= width and y1 <= height:
        return True
    return False


def set_black_white(image, x0, y0, x1, y1):
    if check_coords(image, x0, y0, x1, y1):
        region = image.crop((x0, y0, x1, y1))
        bw_region = region.convert('1')
        image.paste(bw_region, (x0, y0, x1, y1))
        return image
    return image


def find_rect_and_recolor(image, old_color, new_color):
    img = image.load()
    x, y = image.size
    max_S = 0
    max_rect = ()

    for i in range(x):
        for j in range(y):
            if img[i, j] == old_color:
                S = 1
                x1 = 1
                y1 = 1
                while i + x1 < x and img[i + x1, j] == old_color:
                    x1 += 1
                while j + y1 < y and img[i, j + y1] == old_color:
                    y1 += 1
                S = x1 * y1
                if S > max_S:
                    max_S = S
                    max_rect = (i, j, i + x1 - 1, j + y1 - 1)
    for i in range(max_rect[0], max_rect[2] + 1):
        for j in range(max_rect[1], max_rect[3] + 1):
            image.putpixel((i,j), new_color)

    return image
