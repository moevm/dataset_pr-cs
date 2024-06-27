import PIL
from PIL import Image, ImageDraw, ImageOps
import numpy as np


def center(x1, x2):
    return x1 + abs(x2 - x1) // 2
    

def pentagram(img, x0, y0, x1, y1, thickness, color):
    img_drawing = ImageDraw.Draw(img)

    radius = abs(x0 - x1) // 2
    x_center = center(x0, x1)
    y_center = center(y0, y1)

    vertices = []
    for i in range(5):
        angle = (np.pi / 5) * (2 * i + 3 / 2)
        x_vertex = int(x_center + radius * np.cos(angle))
        y_vertex = int(y_center + radius * np.sin(angle))
        vertices.append((x_vertex, y_vertex))

    vertices = [vertices[i] for i in [0, 2, 4, 1, 3, 0]]
    img_drawing.ellipse((x0, y0, x1, y1), outline=tuple(color), width=thickness)
    img_drawing.line(vertices, fill=tuple(color), width=thickness)
    return img


def invert(img, N, vertical):
    width, height = img.size

    if vertical:
        for pixel in range(1, width // N + 1, 2):
            line_coords = (pixel * N, 0, (pixel + 1) * N, height)
            inverted_line = img.crop(line_coords)
            inverted_line = ImageOps.invert(inverted_line)
            img.paste(inverted_line, line_coords[:2])
    else:
        for pixel in range(1, height // N + 1, 2):
            line_coords = (0, pixel * N, width, (pixel + 1) * N)
            inverted_line = img.crop(line_coords)
            inverted_line = ImageOps.invert(inverted_line)
            img.paste(inverted_line, line_coords[:2])

    return img


def mix(img, rules):
    width, height = img.size

    pieces = []
    for ver in range(3):
        for hor in range(3):
            piece_width, piece_height = width // 3, height // 3
            crop_coords = (hor * piece_height, ver * piece_width, (hor + 1) * piece_height, (ver + 1) * piece_width)
            crop = img.crop(crop_coords)
            pieces.append([crop, (hor * piece_height, ver * piece_width)])

    for i in rules.keys():
        img.paste(pieces[rules[i]][0], pieces[i][1])

    return img
