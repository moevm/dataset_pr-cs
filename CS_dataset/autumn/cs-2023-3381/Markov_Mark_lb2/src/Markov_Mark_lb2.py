from PIL import Image, ImageDraw
from math import cos, sin, pi


def swap(img, x0, y0, x1, y1, width):
    img_final = img.copy()
    first = img.crop((x0, y0, x0 + width, y0 + width))
    first = first.rotate(-90)
    second = img.crop((x1, y1, y1 + width, y1 + width))
    second = second.rotate(-90)
    img_final.paste(second, (x0, y0))
    img_final.paste(first, (x1, y1))
    img_final = img_final.rotate(-90)
    return img_final


def avg_color(img, x0, y0, x1, y1):
    img_final = img.copy()
    width, height = img.size
    for x in range(x0, x1 + 1):
        for y in range(y0, y1 + 1):
            near_pixels = set()
            for near_x in range(-1, 2):
                for near_y in range(-1, 2):
                    if (near_x != 0 or near_y != 0) and (width > x + near_x >= 0) and (height > y + near_y >= 0):
                        near_pixels.add((x + near_x, y + near_y))
            pixels = img.load()
            counter = len(near_pixels)
            r, g, b = 0, 0, 0
            for i in near_pixels:
                r += pixels[i][0]
                g += pixels[i][1]
                b += pixels[i][2]
            color = (int(r / counter), int(g / counter), int(b / counter))
            img_final.putpixel((x, y), color)
    return img_final


def pentagram(img, x, y, r, thickness, color):
    drawing = ImageDraw.Draw(img)
    drawing.ellipse((x - r, y - r, x + r, y + r), None, tuple(color), thickness)
    vertex = []
    for i in range(5):
        phi = (pi / 5) * (2 * i + 3 / 2)
        node_i = (int(x + r * cos(phi)), int(y + r * sin(phi)))
        vertex.append(node_i)
    drawing.line(((vertex[0], vertex[2], vertex[4], vertex[1], vertex[3], vertex[0])), tuple(color), thickness)
    return img
