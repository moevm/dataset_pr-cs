import numpy as np
from PIL import ImageDraw, ImageChops

def pentagram(img, x0, y0, x1, y1, thickness, color):
    color = tuple(color)
    draw = ImageDraw.Draw(img)
    draw.ellipse(((x0, y0), (x1, y1)), outline=color, width=thickness)

    r = (x1 - x0) // 2
    x = (x1 + x0) // 2
    y = (y1 + y0) // 2
    coords = []

    for i in range(5):
        phi = (np.pi / 5) * (2 * i + 3 / 2)
        node_i = (int(x + r * np.cos(phi)), int(y + r * np.sin(phi)))
        coords.append(node_i)

    for i in range(2):
        xy = (coords[i - 2], coords[i], coords[i + 2])
        draw.line(xy, fill=color, width=thickness)
    draw.line((coords[2], coords[-1]), fill=color, width=thickness)

    return img

def invert(img, N,vertical):
    width = img.width
    height = img.height

    if vertical:
        for i in range(2, width // N + (width % N != 0) + 1, 2):
            box = ((i - 1) * N, 0, i * N, height)
            part = ImageChops.invert(img.crop(box))
            img.paste(part, box)
    else:
        for i in range(2, height // N + (height % N != 0) + 1, 2):
            box = (0, (i - 1) * N, width, i * N)
            part = ImageChops.invert(img.crop(box))
            img.paste(part, box)

    return img

def mix(img, rules):
    sp = img.width // 3

    parts = [*map(lambda box: (box, img.crop(box)),
                  [((w - 1) * sp, (h - 1) * sp, w * sp, h * sp) for h in range(1, 4) for w in range(1, 4)])]

    for old, new in rules.items():
        img.paste(parts[new][1], parts[old][0])

    return img