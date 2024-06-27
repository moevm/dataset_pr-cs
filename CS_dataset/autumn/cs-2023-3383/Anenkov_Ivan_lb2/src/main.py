import PIL
import numpy as np
from PIL import Image, ImageDraw


def pentagram(img, x, y, r, thickness, color):
    drawing = ImageDraw.Draw(img)
    xy = [x-r, y-r, x+r, y+r]
    drawing.ellipse(xy, None, tuple(color), thickness)
    for i in range(0,5):
        ugol = (np.pi / 5) * (2 * i + 3 / 2)
        Xstart = int(x + r * np.cos(ugol))
        Ystart = int(y + r * np.sin(ugol))
        end_of_line = (np.pi / 5) * (2 * (i+2) + 3 / 2)
        Xend = int(x + r * np.cos(end_of_line))
        Yend = int(y + r * np.sin(end_of_line))
        cords = [(Xstart, Ystart), (Xend, Yend)]
        drawing.line(tuple(cords), tuple(color), thickness)
    return img


def swap(img, x0, y0, x1, y1, width):
    a = width
    img_res = img.copy()
    piece1 = img_res.crop((x0, y0, x0 + a, y0 + a)).rotate(-90)
    piece2 = img_res.crop((x1, y1, x1 + a, y1 + a)).rotate(-90)
    img_res.paste(piece1, (x1, y1))
    img_res.paste(piece2, (x0, y0))
    img_res = img_res.rotate(-90)
    return img_res


def avg_color(img, x0, y0, x1, y1):
    img_res = img.copy()
    arr = img_res.load()
    shape = img_res.size

    for x in range(x0, x1+1):
        for y in range(y0, y1+1):

            pix_ind = ( (x-1,y-1), (x,y-1), (x+1,y-1), (x+1,y), (x+1,y+1), (x,y+1), (x-1,y+1), (x-1,y) )
            check = lambda xy: ((xy[0] >= 0) and (xy[0] < shape[0]) and (xy[1] >= 0) and (xy[1] < shape[1]))
            pix_ind = tuple(filter(check, pix_ind))
            pix = tuple(map(img.getpixel, ((i[0],i[1]) for i in pix_ind)))

            R, G, B = 0, 0, 0
            for i in range(len(pix)):
                R += pix[i][0]
                G += pix[i][1]
                B += pix[i][2]
            res_color = tuple((R // len(pix), G // len(pix), B // len(pix)))
            arr[x, y] = res_color
    return img_res