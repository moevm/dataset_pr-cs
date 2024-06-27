from PIL import Image, ImageDraw, ImageOps
from numpy import pi, sin, cos


def pentagram(img, x0, y0, x1, y1, thickness, color):
    r = abs(x1 - x0) // 2
    x = x0 + r
    y = y0 + r
    node_i = []
    for i in range(0, 5):
        phi = ((pi / 5) * (2 * i + 3 / 2))
        node_i.append((int(x + r * cos(phi)), int(y + r * sin(phi))))
    drawing = ImageDraw.Draw(img, 'RGB')
    drawing.ellipse(((x0, y0), (x1, y1)), fill=None, outline=tuple(color), width=thickness)
    for i in range(0, 5):
        j = 2 + i
        drawing.line((node_i[j % 5], node_i[(j + 2) % 5]), fill=tuple(color), width=thickness, joint=None)
    return img


def invert(img, N, vertical):
    if vertical:
        for i in range(img.size[0]):
            if (i // N) % 2 == 1:
                img1 = ImageOps.invert(img.copy().crop((i, 0, i + 1, img.size[1])))
                img1_coords = (i, 0)
                img.paste(img1, img1_coords)
    else:
        for i in range(img.size[1]):
            if (i // N) % 2 == 1:
                img1 = ImageOps.invert(img.copy().crop((0, i, img.size[0], i + 1)))
                img1_coords = (0, i)
                img.paste(img1, img1_coords)
    return img


def mix(img, rules):
    result_img = Image.new('RGB', img.size, 'blue')
    coord_tuples, coord_tuples1 = [], []
    size_step = img.size[1] // 3
    for i in range(3):
        for j in range(3):
            coord_tuples.append(
                (j * size_step, i * size_step, (j + 1) * size_step, (i + 1) * size_step))
    for i in range(9):
        img1 = img.copy().crop(coord_tuples[rules[i]])
        img1_coords = (coord_tuples[i][0], coord_tuples[i][1])
        result_img.paste(img1, img1_coords)
    return result_img