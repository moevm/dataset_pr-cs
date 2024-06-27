from PIL import Image, ImageDraw, ImageOps
from numpy import pi, cos, sin


def pentagram(img, x0, y0, x1, y1, thickness, color):
    r = abs(x0 - x1) // 2
    x_cent = x0 + r
    y_cent = y0 + r
    coordinates = []
    for i in range(6):
        phi = (pi / 5) * (4 * (i % 5) + 3 / 2)
        node_i = (int(x_cent + r * cos(phi)), int(y_cent + r * sin(phi)))
        coordinates.append(node_i)
    drawing = ImageDraw.Draw(img, 'RGB')
    drawing.ellipse((x0, y0, x1, y1), outline=tuple(color), width=thickness)
    drawing.line(coordinates, fill=tuple(color), width=thickness)
    return img


def invert(img, N, vertical):
    lines = []
    if vertical:
        img = img.rotate(-90, expand=True)
    w, h = img.size

    for i in range(h // N):
        img_part = img.crop((0, N * i, w, N * (i + 1)))
        lines.append(img_part)
    if abs(h / N - h // N) > 10 ** -5:
        lines.append(img.crop((0, N * (h // N), w, h)))

    for i in range(1, len(lines), 2):
        img.paste(ImageOps.invert(lines[i]), (0, N * i))

    if vertical:
        img = img.rotate(90, expand=True)
    return img


def mix(img, rules):
    w, h = img.size
    parts = [[0] * 3 for _ in range(3)]
    for i in range(3):
        for j in range(3):
            c0 = (int(j * w / 3), int(i * h / 3))
            cend = (int((j + 1) * w / 3), int((i + 1) * h / 3))
            img_part = img.crop((*c0, *cend))
            parts[i][j] = img_part
    new_parts = [[0] * 3 for _ in range(3)]
    for new, old in rules.items():
        new_parts[new // 3][new % 3] = parts[old // 3][old % 3]

    for i in range(3):
        for j in range(3):
            img.paste(new_parts[i][j], (int(j * w / 3), int(i * h / 3)))
    return img
