from PIL import Image, ImageDraw
import numpy as np


def user_func(image, x0, y0, x1, y1, fill, width):
    color = tuple(fill)
    drawing = ImageDraw.Draw(image)
    drawing.line(((x0, y0), (x1, y1)), color, width)
    return image


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


def find_rect_and_recolor(image, old_color, new_color):
    img = np.array(image)

    old_pixels = np.where(
        (img[:, :, 0] == old_color[0]) & (img[:, :, 1] == old_color[1]) & (img[:, :, 2] == old_color[2]))

    if len(old_pixels[0]) == 0:
        return image

    rect_x = []
    rect_y = []
    rect_w = []
    rect_h = []

    for i in range(len(old_pixels[0])):
        x = old_pixels[1][i]
        y = old_pixels[0][i]

        if (x == 0 or img[y, x - 1][0] != old_color[0] or img[y, x - 1][1] != old_color[1] or img[y, x - 1][2] !=
            old_color[2]) and (
                y == 0 or img[y - 1, x][0] != old_color[0] or img[y - 1, x][1] != old_color[1] or img[y - 1, x][2] !=
                old_color[2]):
            w = 1
            h = 1

            while x + w < img.shape[1] and img[y, x + w][0] == old_color[0] and img[y, x + w][1] == old_color[1] and \
                    img[y, x + w][2] == old_color[2]:
                w += 1

            while y + h < img.shape[0] and img[y + h, x][0] == old_color[0] and img[y + h, x][1] == old_color[1] and \
                    img[y + h, x][2] == old_color[2]:
                h += 1

            rect_x.append(x)
            rect_y.append(y)
            rect_w.append(w)
            rect_h.append(h)

    max_area = 0
    max_area_index = 0
    for i in range(len(rect_x)):
        area = rect_w[i] * rect_h[i]
        if area > max_area:
            max_area = area
            max_area_index = i

    x = rect_x[max_area_index]
    y = rect_y[max_area_index]
    w = rect_w[max_area_index]
    h = rect_h[max_area_index]
    img[y:y + h, x:x + w] = new_color

    return Image.fromarray(img)