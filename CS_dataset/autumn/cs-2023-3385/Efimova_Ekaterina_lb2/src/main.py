import numpy as np
from PIL import Image, ImageDraw, ImageOps


def pentagram(img, x0, y0, x1, y1, thickness, color):
    r = abs(x1 - x0) // 2
    x = int(x0 + r)
    y = int(y0 + r)
    points = []
    draw = ImageDraw.Draw(img, 'RGB')
    for i in range(5):
        phi = (np.pi / 5) * (2 * i + 3 / 2)
        node_i = (int(x + r * np.cos(phi)), int(y + r * np.sin(phi)))
        points.append(node_i)
    draw.ellipse((x0, y0, x1, y1), width=thickness, outline=tuple(color))
    draw.line((points[0], points[3], points[1], points[4], points[2], points[0]), width=thickness, fill=tuple(color))
    return img


def invert(img, N,vertical):
    img_invert = ImageOps.invert(img)
    if vertical:
        for i in range(1, img.size[0] // N + 1, 2):
            start = i * N
            finish = (i + 1) * N if (i + 1) * N <= img.size[0] else img.size[0]
            part = img_invert.crop((start, 0, finish, img.size[1]))
            img.paste(part, (start, 0, finish, img.size[1]))
    else:
        for i in range(1, img.size[1] // N + 1, 2):
            start = i * N
            finish = (i + 1) * N if (i + 1) * N <= img.size[1] else img.size[1]
            part = img_invert.crop((0, start, img.size[0], finish))
            img.paste(part, (0, start, img.size[1], finish))
    return img
    

def mix(img, rules):
    part_len = img.size[0] // 3
    new_img = Image.new("RGB", (img.size[0], img.size[1]), "black")
    for n in range(9):
        m = rules[n]
        part = img.crop((m % 3 * part_len, m // 3 * part_len,
                         (m % 3 + 1) * part_len, (m // 3 + 1) * part_len))
        new_img.paste(part, (n % 3 * part_len, n // 3 * part_len,
                             (n % 3 + 1) * part_len, (n // 3 + 1) * part_len))
    return new_img
