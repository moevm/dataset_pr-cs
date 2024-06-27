from PIL import Image, ImageDraw, ImageOps
import numpy as np


def absoluteAverage (x1, x2):
    return abs(x1 - x2) // 2


def pentagram(img, x0, y0, x1, y1, thickness, color):
    color = tuple(color)

    drawing = ImageDraw.Draw(img)
    drawing.ellipse((x0, y0, x1, y1), outline=color, width=thickness)

    centre = {'x': x1 - absoluteAverage(x0, x1), 'y': y1 - absoluteAverage(y0, y1)}
    radius = absoluteAverage(x0, x1)

    nodes = [(0, 0)] * 5

    for i in range(5):
        phi = (np.pi / 5) * (2 * i + 3 / 2)
        node_i = (int(centre['x'] + radius * np.cos(phi)), int(centre['y'] + radius * np.sin(phi)))
        nodes[i] = node_i

    drawing.line((nodes[0], nodes[3], nodes[1], nodes[4], nodes[2], nodes[0]), color, thickness, None)
    return img


def invert(img, N, vertical):
    w = img.size[0]
    h = img.size[1]
    M = (w // N) + 1

    if vertical:
        if w % N == 0:
            for i in range(M):
                if i % 2 == 1:
                    strip = img.crop((N * i, 0, N * (i + 1), h))
                    invertedStrip = ImageOps.invert(strip)
                    img.paste(invertedStrip, (N * i, 0))
        else:
            for i in range(M):
                if i % 2 == 1 and i < (M - 1):
                    strip = img.crop((N * i, 0, N * (i + 1), h))
                    invertedStrip = ImageOps.invert(strip)
                    img.paste(invertedStrip, (N * i, 0))
                if i == M - 1 and i % 2 == 1:
                    strip = img.crop((N * (M - 1), 0, w, h))
                    invertedStrip = ImageOps.invert(strip)
                    img.paste(invertedStrip, (N * (M - 1), 0))

    else:
        if w % N == 0:
            for i in range(M):
                if i % 2 == 1:
                    strip = img.crop((0, N * i, w, N * (i + 1)))
                    invertedStrip = ImageOps.invert(strip)
                    img.paste(invertedStrip, (0, N * i))
        else:
            for i in range(M):
                if i % 2 == 1 and i < (M - 1):
                    strip = img.crop((0, N * i, w, N * (i + 1)))
                    invertedStrip = ImageOps.invert(strip)
                    img.paste(invertedStrip, (0, N * i))
                if i == M - 1 and i % 2 == 1:
                    strip = img.crop((0, N * (M - 1), w, h))
                    invertedStrip = ImageOps.invert(strip)
                    img.paste(invertedStrip, (0, N * (M - 1)))

    return img


def mix(img, rules):
    pieces = []
    w = img.size[0]
    h = img.size[1]

    for i in range(3):
        for j in range(3):
            piece = img.crop((j * (h // 3), i * (w // 3), (j + 1) * (h // 3), (i + 1) * (w // 3)))
            pieces += [(piece, (j * (h // 3), i * (w // 3)))]

    for i in rules:
        img.paste(pieces[rules[i]][0], pieces[i][1])

    return img
