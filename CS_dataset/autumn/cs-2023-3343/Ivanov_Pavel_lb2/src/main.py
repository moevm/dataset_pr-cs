import numpy as np
from PIL import Image, ImageDraw


def triangle(img, x0, y0, x1, y1, x2, y2, thickness, color, fill_color):
    drawing = ImageDraw.Draw(img)
    drawing.polygon(((x0, y0), (x1, y1), (x2, y2)), fill=None if fill_color is None else tuple(fill_color), outline=tuple(color), width=thickness)
    return img


def change_color(img, color):
    colors = dict()
    pixels_list = np.array(img)
    strings, columns = np.shape(pixels_list)[0], np.shape(pixels_list)[1]
    for i in range(strings):
        for j in range(columns):
            if tuple(pixels_list[i][j]) not in colors.keys():
                colors[tuple(pixels_list[i][j])] = 0
            else:
                colors[tuple(pixels_list[i][j])] += 1
    most_frec = max(colors.keys(), key=lambda x: colors[x])
    for i in range(strings):
        for j in range(columns):
            if tuple(pixels_list[i][j]) == most_frec:
                pixels_list[i][j] = np.array(color)
    new = Image.fromarray(pixels_list)
    return new


def collage(img, N, M):
    width = img.size[0] * M
    height = img.size[1] * N
    new_image = Image.new("RGB", (width, height), "black")
    for i in range(N):
        for j in range(M):
            new_image.paste(img, (img.size[0]*j, img.size[1]*i))
    return new_image
