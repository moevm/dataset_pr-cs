import numpy as np
import PIL
from PIL import Image, ImageDraw

# Задача 1
def triangle(img, x0, y0, x1, y1, x2, y2, thickness, color, fill_color):
    draw = ImageDraw.Draw(img)
    ver = [(x0, y0), (x1, y1), (x2, y2)]
    if fill_color is None:
        spis = None
    else:
        spis = tuple(fill_color)
    draw.polygon(ver, outline=tuple(color), width=thickness, fill=spis)
    return img

# Задача 2
def change_color(img, color):
    r, g, b = color
    pixels = np.array(img)
    unique_colors, counts = np.unique(pixels.reshape(-1, 3), axis=0, return_counts=True)
    most_common_color = unique_colors[np.argmax(counts)]
    pixels[np.where((pixels == most_common_color).all(axis=2))] = color
    new_image = Image.fromarray(pixels)
    return new_image

# Задача 3
def collage(img, N, M):
    width, h = img.size
    new_image = Image.new(img.mode, (M * width, N * h))
    for i in range(N):
        for j in range(M):
            new_image.paste(img, (j * width, i * h))
    return new_image