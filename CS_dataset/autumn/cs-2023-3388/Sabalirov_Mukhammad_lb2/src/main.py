import numpy as np
from PIL import Image, ImageDraw


def triangle(img, x0, y0, x1, y1, x2, y2, thickness, color, fill_color):
    fill_color = tuple(fill_color) if fill_color is not None else None

    drawing = ImageDraw.Draw(img)
    drawing.polygon([(x0, y0), (x1, y1), (x2, y2)], fill_color, tuple(color), thickness)
    return img


def change_color(img, color):
    color = tuple(color)
    pixels = list(img.getdata())

    color_count = {x: pixels.count(x) for x in set(pixels)}
    replacement_color = max(color_count, key=lambda x: color_count[x])
    new_pixels = [color if pixel == replacement_color else pixel for pixel in pixels]

    changed_color_img = img.copy()
    changed_color_img.putdata(new_pixels)
    return changed_color_img


def collage(img, N, M):
    w, h = img.size
    img_collage = Image.new("RGB", (w * M, h * N), 'red')

    for x in range(0, w * M, w):
        for y in range(0, h * N, h):
            img_collage.paste(img, (x, y))
            
    return img_collage
