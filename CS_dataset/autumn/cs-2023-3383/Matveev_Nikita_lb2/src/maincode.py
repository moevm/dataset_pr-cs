import numpy as np
import PIL
from PIL import Image
from PIL import ImageDraw
# Задача 1
def triangle(img, x0, y0, x1, y1, x2, y2, thickness, color, fill_color):
    color = tuple(color)
    dr = ImageDraw.Draw(img)
    if fill_color != None:
        fill_color = tuple(fill_color)
        dr.polygon(((x1, y1), (x2, y2), (x0, y0)), fill_color, color,thickness)
    else:
        dr.polygon(((x1, y1), (x2, y2), (x0, y0)), None, color, thickness)
    return img

# Задача 2
def change_color(img, color):
    color = tuple(color)
    w, h = img.size
    a = np.array(img)
    un, k = np.unique(a.reshape(-1, 3), axis = 0, return_counts=True)
    mx = np.argmax(k)
    most = un[mx]
    pixels = img.load()
    for x in range(w):
        for y in range(h):
            if pixels[x, y] == tuple(most):
                pixels[x, y] = color
    return img

# Задача 3
def collage(img, N, M):
    w, h = img.size
    img_new = Image.new('RGB', (M*w,N*h), 'white')
    for i in range(0, M*w, w):
        for j in range(0, N*h, h):
            img_new.paste(img, (i, j))
    return img_new
