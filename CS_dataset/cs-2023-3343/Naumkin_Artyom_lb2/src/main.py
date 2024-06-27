from PIL import Image
from collections import Counter
import numpy as np


def triangle(img, x0, y0, x1, y1, x2, y2, thickness, color, fill_color=None):
    draw = ImageDraw.Draw(img)
    draw.polygon(((x0, y0), (x1, y1), (x2, y2)), width=thickness, outline=tuple(color), fill=tuple(fill_color) if fill_color else None)

    return img


def change_color(img, color):
    img_array = np.array(img)
    colors_count = Counter(tuple(pixel) for i in img_array for pixel in i)
    most_common_color = colors_count.most_common(1)[0][0]
    img_array[(img_array == most_common_color).all(axis=2)] = color
    new_img = Image.fromarray(img_array)

    return new_img


def collage(img, N, M):
    width, height = img.size
    collage_img = Image.new("RGB", (M * width, N * height))
    
    for i in range(N):
        for j in range(M):
            collage_img.paste(img, (j * width, i * height))

    return collage_img


