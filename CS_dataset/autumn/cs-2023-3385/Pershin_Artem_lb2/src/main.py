import numpy as np
from PIL import Image, ImageDraw, ImageOps


def pentagram(img, x0, y0, x1, y1, thickness, color):
    r = abs(x0 - x1) // 2
    x = x0 + r
    y = y0 + r
    draw = ImageDraw.Draw(img, 'RGB')
    draw.ellipse((x0, y0, x1, y1), None, tuple(color), thickness)
    points = []
    for i in range(5):
        phi = (np.pi / 5) * (2 * i + 3 / 2)
        node_i = (int(x + r * np.cos(phi)), int(y + r * np.sin(phi)))
        points.append(node_i)
    for i in range(5):
        draw.line((points[i], points[(i + 2) % 5]), tuple(color), thickness)

    return img


def invert(img, N, vertical):
    if (vertical):
        for i in range(img.size[0]):
            if ((i // N) % 2 == 1):
                img_1 = ImageOps.invert(img.copy().crop((i, 0, i + 1, img.size[1])))
                img_2 = (i, 0)
                img.paste(img_1, img_2)
    else:
        for i in range(img.size[1]):
            if ((i // N) % 2 == 1):
                img_1 = ImageOps.invert(img.copy().crop((0, i, img.size[0], i + 1)))
                img_2 = (0, i)
                img.paste(img_1, img_2)

    return img


def mix(img, rules):
    mix_img = Image.new("RGB", (img.size[0], img.size[1]), color=0)
    squares = []
    for i in range(3):
        for j in range(3):
            squares.append(
                (j * img.size[0] // 3, i * img.size[0] // 3, (j + 1) * img.size[0] // 3, (i + 1) * img.size[0] // 3))
    for i in range(9):
        img_1 = img.copy().crop(squares[rules[i]])
        img_2 = (squares[i][0], squares[i][1])
        mix_img.paste(img_1, img_2)
    return mix_img