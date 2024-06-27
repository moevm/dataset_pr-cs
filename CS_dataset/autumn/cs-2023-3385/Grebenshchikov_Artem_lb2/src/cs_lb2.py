from PIL import Image, ImageDraw
import numpy as np


def pentagram(img, x, y, r, thickness, color):
    coordinates = [x - r, y - r, x + r, y + r]
    drawing = ImageDraw.Draw(img)
    drawing.ellipse(coordinates, None, tuple(color), thickness)
    for i in range(5):
        ugl = (np.pi / 5) * (2 * i + 3 / 2)
        Xstart = int(x + r * np.cos(ugl))
        Ystart = int(y + r * np.sin(ugl))
        endline = (np.pi / 5) * (2 * (i + 2) + 3 / 2)
        Xend = int(x + r * np.cos(endline))
        Yend = int(y + r * np.sin(endline))
        coords = [(Xstart, Ystart), (Xend, Yend)]
        drawing.line(tuple(coords), tuple(color), thickness)
    return img


def swap(img, x0, y0, x1, y1, width):
    img_res = img.copy()
    piece1 = img_res.crop((x0, y0, x0 + width, y0 + width)).rotate(-90)
    piece2 = img_res.crop((x1, y1, x1 + width, y1 + width)).rotate(-90)
    img_res.paste(piece1, (x1, y1))
    img_res.paste(piece2, (x0, y0))
    img_res = img_res.rotate(-90)
    return img_res


def avg_color(img, x0, y0, x1, y1):
    img_res = img.copy()
    arr = img_res.load()
    shape = img_res.size

    for x in range(x0, x1 + 1):
        for y in range(y0, y1 + 1):
            pix_ind = ((x - 1, y - 1), (x, y - 1), (x + 1, y - 1), (x + 1, y), (x + 1, y + 1), (x, y + 1), (x - 1, y + 1), (x - 1, y))
            check = lambda xy: ((xy[0] >= 0) and (xy[0] < shape[0]) and (xy[1] >= 0) and (xy[1] < shape[1]))
            pix_ind = tuple(filter(check, pix_ind))
            pix = list(map(img.getpixel, ((i[0], i[1]) for i in pix_ind)))
            newcolor = np.sum(np.array(pix), axis = 0)
            arr[x, y] = tuple(newcolor // len(pix))
    return img_res
