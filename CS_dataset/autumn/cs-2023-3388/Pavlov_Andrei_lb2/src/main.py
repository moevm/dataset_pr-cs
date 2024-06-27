import os
os.environ['OPENBLAS_NUM_THREADS'] = '1'

import PIL
import numpy as np
from PIL import Image, ImageDraw


def swap(img, x0, y0, x1, y1, width):
    img_res = img.copy()
    piece1 = img_res.crop((x0, y0, x0 + width, y0 + width)).rotate(-90)
    piece2 = img_res.crop((x1, y1, x1 + width, y1 + width)).rotate(-90)
    img_res.paste(piece1, (x1, y1))
    img_res.paste(piece2, (x0, y0))
    img_res = img_res.rotate(-90)
    return img_res

def end_of_img(xy, shape):
    return (xy[0] >= 0) and (xy[0] < shape[0]) and (xy[1] >= 0) and (xy[1] < shape[1])

def avg_color(img, x0, y0, x1, y1):
    img_res = img.copy()
    data = img_res.load()
    img_shape = img_res.size
    
    for x in range(x0, x1+1):
        for y in range(y0, y1+1):
            pixels = [(x-1, y-1), (x, y-1), (x+1, y-1), (x+1, y), (x+1, y+1), (x, y+1), (x-1, y+1), (x-1, y)]
            pixels = [pixel for pixel in pixels if end_of_img(pixel, img_shape)]
            avg = np.array(list(map(img.getpixel, pixels)))
            result = avg.mean(axis=0)
            data[x, y] = (int(result[0]), int(result[1]), int(result[2]))
    return img_res

def pentagram(img, x, y, r, thickness, color):
    drawing = ImageDraw.Draw(img)
    xy = [x-r, y-r, x+r, y+r]
    drawing.ellipse(xy, None, tuple(color), thickness)
    for i in range(0, 5):
        alpha = (np.pi / 5) * (2 * i + 3 / 2)
        Xstart = int(x + r * np.cos(alpha))
        Ystart = int(y + r * np.sin(alpha))
        end_of_line = (np.pi / 5) * (2 * (i+2) + 3 / 2)
        Xend = int(x + r * np.cos(end_of_line))
        Yend = int(y + r * np.sin(end_of_line))
        cords = ((Xstart, Ystart), (Xend, Yend))
        drawing.line(cords, tuple(color), thickness)
    return img

