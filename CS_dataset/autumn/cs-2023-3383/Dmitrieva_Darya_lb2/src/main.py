import math
from PIL import Image, ImageDraw
import numpy as np

def swap(img, x0, y0, x1, y1, width):
    new_img = img.copy()
    region1 = img.crop((x0, y0, x0 + width, y0 + width))
    region1_rotated = region1.rotate(-90)
    new_img.paste(region1_rotated, (x1, y1))
    region2 = img.crop((x1, y1, x1 + width, y1 + width))
    region2_rotated = region2.rotate(-90)
    new_img.paste(region2_rotated, (x0, y0))
    new_img_rotated = new_img.rotate(-90)
    return new_img_rotated
    pass


def avg_color(img, x0, y0, x1, y1):
    new_img = img.copy()
    for y in range(y0, y1 + 1):
        for x in range(x0, x1 + 1):
            pixels = [img.getpixel((x2, y2)) for y2 in range(y - 1, y + 2) for x2 in range(x - 1, x + 2) if (0 <= x2 < img.size[0]) and (0 <= y2 < img.size[1]) and not ((x2 == x) and (y2 == y))]
            k = len(pixels)
            if k > 0:
                r, g, b = map(sum, zip(*pixels))
                color = (int(r / k), int(g / k), int(b / k))
                new_img.putpixel((x, y), color)
    return new_img

def pentagram(img, x, y, r, thickness, color):
    drawing = ImageDraw.Draw(img)
    nodes = []
    for i in range(5):
        phi = (math.pi / 5) * (2 * i + 3 / 2)
        node_i = (int(x + r * math.cos(phi)) , int(y + r * math.sin(phi)))
        nodes.append(node_i)
    drawing.ellipse((x - r, y - r, x + r, y + r), fill=None, outline=tuple(color), width=thickness)
    for i in range(5):
        drawing.line([nodes[i], nodes[(i + 2) % 5]], fill=tuple(color), width=thickness)
    return img
    pass