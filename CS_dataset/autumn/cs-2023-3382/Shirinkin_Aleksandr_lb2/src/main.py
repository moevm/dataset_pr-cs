from PIL import Image, ImageDraw
import math
import numpy as np


def pentagram(image, x0, y0, x1, y1, thickness, color):
    draw = ImageDraw.Draw(image)
    xc = (x1 - x0) // 2 + x0
    yc = (y1 - y0) // 2 + y0
    r = min(x1 - x0, y1 - y0) // 2
    draw.ellipse((x0, y0, x1, y1), outline=tuple(color), width=thickness)
    points = []
    for i in range(5):
        phi = (math.pi / 5) * (2 * i + 3 / 2)
        node_i = (int(xc + r * math.cos(phi)), int(yc + r * math.sin(phi)))
        points.append(node_i)
    for i in range(5):
        draw.line([points[i], points[(i + 2) % 5]], fill=tuple(color), width=thickness)
    return image


def invert(image, N, vertical):
    img_array = np.array(image)
    if vertical:
        mask = np.repeat(np.mod(np.arange(img_array.shape[1]) // N, 2) == 1, img_array.shape[0]).reshape(
            img_array.shape[1], img_array.shape[0]).T
    else:
        mask = np.repeat(np.mod(np.arange(img_array.shape[0]) // N, 2) == 1, img_array.shape[1]).reshape(
            img_array.shape[0], img_array.shape[1])
    img_array[mask] = 255 - img_array[mask]
    return Image.fromarray(img_array)


def mix(img, rules: dict):
    new_img = Image.new("RGB", (img.size[0], img.size[1]))
    size = img.size[0] // 3
    side = []
    for line in range(img.size[1] // size):
        for column in range(img.size[0] // size):
            cord = (column * size, line * size, (column + 1) * size, (line + 1) * size)
            side.append(img.crop(cord))
    for new_position, crop in rules.items():
        new_img.paste(side[crop],
                      ((new_position % 3) * size, (new_position // 3) * size))

    return new_img
