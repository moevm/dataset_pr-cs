import PIL
from PIL import Image, ImageDraw
import math


def swap(img, x0, y0, x1, y1, width):
    img_out = img.copy()
    crop_first = img_out.crop((x0, y0, x0 + width, y0 + width)).rotate(270)
    crop_second = img_out.crop((x1, y1, x1 + width, y1 + width)).rotate(270)
    img_out.paste(crop_first, (x1, y1))
    img_out.paste(crop_second, (x0, y0))
    img_out = img_out.rotate(270)
    return img_out


def avg_color(img, x0, y0, x1, y1):
    img_out = img.copy()
    for x in range(x0, x1+1):
        for y in range(y0, y1+1):
            summ_red, summ_green, summ_blue = 0, 0, 0
            count = 0
            for i in range(-1, 2):
                for j in range(-1, 2):
                    if (i != 0 or j != 0) and (0 <= x + i < img.size[0] and 0 <= y + j < img.size[1]):
                        count += 1
                        summ_red += img.getpixel((x + i, y + j))[0]
                        summ_green += img.getpixel((x + i, y + j))[1]
                        summ_blue += img.getpixel((x + i, y + j))[2]
            img_out.putpixel((x, y), (int(summ_red / count), int(summ_green / count), int(summ_blue / count)))
    return img_out


def pentagram(img, x, y, r, thickness, color):
    node_i = []
    drawing = ImageDraw.Draw(img)
    drawing.ellipse(((x - r, y - r), (x + r, y + r)), None, tuple(color), thickness)
    for i in range(5):
        phi = (math.pi / 5) * (2 * i + 3 / 2)
        node_i += [(int(x + r * math.cos(phi)), int(y + r * math.sin(phi)))]
    drawing.line((*node_i[0], *node_i[2]), tuple(color), thickness)
    drawing.line((*node_i[2], *node_i[4]), tuple(color), thickness)
    drawing.line((*node_i[4], *node_i[1]), tuple(color), thickness)
    drawing.line((*node_i[1], *node_i[3]), tuple(color), thickness)
    drawing.line((*node_i[3], *node_i[0]), tuple(color), thickness)
    return img
