import PIL
import numpy as np
from PIL import Image, ImageDraw, ImageOps


def pentagram(img, x0, y0, x1, y1, thickness, color):
    drawing = ImageDraw.Draw(img)
    color = tuple(color)
    drawing.ellipse((x0, y0, x1, y1), None, color, thickness)
    points = []
    r = int((x1 - x0) / 2)
    x = x0 + r
    y = y0 + r
    drawing_order = [0, 2, 4, 1, 3, 0]
    for i in drawing_order:
        phi = (np.pi / 5) * (2 * i + 3 / 2)
        points.append((int(x + r * np.cos(phi)), int(y + r * np.sin(phi))))
    points = tuple(points)
    drawing.line(points, color, thickness)
    return img


def invert(img, N, vertical):
    end_x, end_y = img.size
    if vertical:
        for x in range(N, end_x, 2 * N):
            strip = img.crop((x, 0, x + N, end_y))
            strip = ImageOps.invert(strip)
            img.paste(strip, (x, 0))
    else:
        for y in range(N, end_y, 2 * N):
            strip = img.crop((0, y, end_x, y + N))
            strip = ImageOps.invert(strip)
            img.paste(strip, (0, y))
    return img


def mix(img, rules):
    size = img.size
    block_x = size[0] // 3
    block_y = size[1] // 3
    crooped_images = []
    for i in range(3):
        for j in range(3):
            x = block_x * j
            y = block_y * i
            img2 = img.crop((x, y, x + block_x, y + block_y))
            crooped_images.append(img2)
    for i in range(9):
        crooped_img = crooped_images[rules[i]]
        x = i % 3 * block_x
        y = i // 3 * block_y
        img.paste(crooped_img, (x, y))
    return img
