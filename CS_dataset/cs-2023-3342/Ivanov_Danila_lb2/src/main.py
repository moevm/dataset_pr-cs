import PIL, numpy
from PIL import Image, ImageDraw, ImageOps
from numpy import pi, cos, sin, ceil


def pentagram(img, x0, y0, x1, y1, thickness, color):
    drawing = ImageDraw.Draw(img)
    drawing.ellipse([(x0, y0), (x1, y1)], width=thickness, outline=tuple(color))
    r = (x1 - x0) // 2
    cen_x = ((x1 - x0) // 2) + x0
    cen_y = ((y1 - y0) // 2) + y0
    coords = []
    for i in range(5):
        phi = (pi) * (2 * i + 3 / 2) /5
        node_i = (int(cen_x + r * cos(phi)), int(cen_y + r * sin(phi)))
        coords.append(node_i)
    drawing.line([coords[0], coords[2]], fill=tuple(color), width=thickness)
    drawing.line([coords[0], coords[3]], fill=tuple(color), width=thickness)
    drawing.line([coords[1], coords[3]], fill=tuple(color), width=thickness)
    drawing.line([coords[1], coords[4]], fill=tuple(color), width=thickness)
    drawing.line([coords[2], coords[4]], fill=tuple(color), width=thickness)
    return img


def invert(img, N, vertical):
    w, h = img.size
    k = 0
    if vertical:
        for x in range(0, w, N):
            if k % 2 == 1:
                part = img.crop((x, 0, x + N, h))
                inv_part = ImageOps.invert(part)
                img.paste(inv_part, (x, 0))
            k += 1
    else:
        for y in range(0, h, N):
            if k % 2 == 1:
                part = img.crop((0, y, w, y + N))
                inv_part = ImageOps.invert(part)
                img.paste(inv_part, (0, y))
            k += 1

    return img


def mix(img, rules):
    dic = {0: (0, 0), 1: (0, 1), 2: (0, 2), 3: (1, 0), 4: (1, 1), 5: (1, 2), 6: (2, 0), 7: (2, 1), 8: (2, 2)}
    parts = [[0 for _ in range(3)] for _ in range(3)]
    result = [[0 for _ in range(3)] for _ in range(3)]
    w, h = img.size
    size_x = w // 3
    size_y = h // 3
    for i in range(3):
        for j in range(3):
            img_0 = img.crop((0 + j * size_y, 0 + i * size_x, 0 + (j + 1) * size_y, 0 + (i + 1) * size_x))
            parts[i][j] = img_0
            result[i][j] = img_0
    for i in rules:
        x0, y0 = dic[i]
        x1, y1 = dic[rules[i]]
        result[x0][y0] = parts[x1][y1]
    for i in range(3):
        for j in range(3):
            img.paste(result[i][j], (0 + j * size_y, 0 + i * size_x))
    return img