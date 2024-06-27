import numpy as np
from PIL import Image, ImageDraw


def triangle(img, x0, y0, x1, y1, x2, y2, thickness, color, fill_color):
    drawing = ImageDraw.Draw(img)
    if fill_color:
        drawing.polygon([(x0, y0), (x1, y1), (x2, y2)], fill=tuple(fill_color),
                        width=thickness, outline=tuple(color))
    else:
        drawing.polygon([(x0, y0), (x1, y1), (x2, y2)],
                        width=thickness, outline=tuple(color))
    return img


def change_color(img, color):
    x, y = img.size
    pixels_array = np.array([img.getpixel((i, j)) for i in range(x) for j in range(y)])
    pixels_array, counts = np.unique(pixels_array, axis=0, return_counts=True)
    freq_color = tuple(pixels_array[np.where(counts ==
                                             np.max(counts))][0].tolist())
    img_new = img.copy()
    pixels = img_new.load()
    for i in range(x):
        for j in range(y):
            if pixels[i, j] == freq_color:
                pixels[i, j] = tuple(color)
    return img_new


def collage(img, N, M):
    x, y = img.size
    img_new = Image.new("RGB", (x * M, y * N))
    for i in range(N):
        for j in range(M):
            img_new.paste(img, (x * j, y * i))
    return img_new
