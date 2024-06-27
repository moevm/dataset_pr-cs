from PIL import ImageDraw, Image
import numpy as np
from collections import Counter
from itertools import product

def triangle(img: Image, x0: int, y0: int, x1: int, y1: int, x2: int, y2:int , thickness: int, color: list, fill_color=None) -> Image:
    draw = ImageDraw.Draw(img)
    points = [(x0, y0), (x1, y1), (x2, y2)]
    draw.polygon(points, width=thickness, outline=tuple(color), fill=tuple(fill_color) if fill_color else None)
    return img

def change_color(img: Image, color: list) -> Image:
    data = np.array(img)
    common_color = Counter(map(tuple, data.reshape(-1, 3))).most_common(1)[0][0]
    data[(data == common_color).all(axis=-1)] = color
    return Image.fromarray(data, mode='RGB')

def collage(img: Image, N: int, M: int) -> Image:
    new_bg = Image.new("RGB", (img.width * M, img.height * N), (0, 0, 0))
    for n, m in product(range(N), range(M)):
        new_bg.paste(img, (img.width * m, img.height * n))
    return new_bg
