from PIL import Image, ImageDraw, ImageChops
from math import pi, sin, cos


def pentagram(img, x0, y0, x1, y1, thickness, color):
    r = (x1 - x0) // 2
    img_draw = ImageDraw.Draw(img)
    color = tuple(color)
    circle_x = (x0 + x1) // 2
    circle_y = (y0 + y1) // 2
    img_draw.ellipse(((x0, y0), (x1, y1)), outline=color, width=thickness)
    pent_coords = []
    for i in range(5):
        phi = (pi / 5) * (2 * i + 3 / 2)
        node_i = (int(circle_x + r * cos(phi)), int(circle_y + r * sin(phi)))
        pent_coords.append(node_i)
    for i in range(2):
        img_draw.line([pent_coords[i - 2], pent_coords[i], pent_coords[i + 2]], fill=color, width=thickness)
    img_draw.line([pent_coords[2], pent_coords[4]], fill=color, width=thickness)
    return img


def invert(img, N, vertical):
    width, height = img.size
    if vertical == True:
        num_of_strip = width // N
        for i in range(1, num_of_strip + 1, 2):
            box = (N * i, 0, N * (i + 1), height)
            invert_img = ImageChops.invert(img.crop(box))
            img.paste(invert_img, box)
    else:
        num_of_strip = height // N
        for i in range(1, num_of_strip + 1, 2):
            box = (0, N * i, width, N * (i + 1))
            invert_img = ImageChops.invert(img.crop(box))
            img.paste(invert_img, box)
    return img


def mix(img, rules):
    width, height = img.size
    rect_width = width // 3
    rect_height = height // 3
    row_count = 1;
    paste_coords = {}
    img_paste_list = []
    for i in range(9):
        box = (rect_width * (i % 3), rect_width * (row_count - 1), rect_width * ((i % 3) + 1), rect_height * row_count)
        if i != 0 and (i + 1) % 3 == 0:
            row_count += 1
        paste_coords[i] = box
        img_paste_list.append(img.crop(box))
    for i in range(9):
        opt = rules[i]
        img.paste(img_paste_list[opt], paste_coords[i])
    return img
