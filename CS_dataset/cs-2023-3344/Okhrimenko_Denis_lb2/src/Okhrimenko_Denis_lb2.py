from PIL import Image
from PIL import ImageDraw
import numpy as np


def triangle(img, x0, y0, x1, y1, x2, y2, thickness, color, fill_color):
    drawing = ImageDraw.Draw(img)
    coordinates = [x0, y0, x1, y1, x2, y2]
    if fill_color == None:
        drawing.polygon(
            coordinates,
            outline=tuple(color),
            width=thickness,
        )
    else:
        drawing.polygon(
            coordinates,
            fill=tuple(fill_color),
            outline=tuple(color),
            width=thickness,
        )
    return img


def change_color(img, color):
    color = tuple(color)
    d = {}
    pixels = np.array(img)
    for i in pixels:
        for j in i:
            pixel = tuple(j)
            if pixel not in d:
                d[pixel] = 1
            else:
                d[pixel] += 1
    find = max(d.values())
    for key in d:
        if d[key] == find:
            most_relevant_color = key
    for i in range(len(pixels)):
        for j in range(len(pixels[i])):
            if tuple(pixels[i][j]) == most_relevant_color:
                pixels[i][j] = color
    img = Image.fromarray(pixels)
    return img


# Задача 3
def collage(img, N, M):
    image = img
    img = img.resize(size=(img.size[0] * M, img.size[1] * N))
    for i in range(N):
        for j in range(M):
            img.paste(image, (image.size[0] * j, image.size[1] * i))
    return img
