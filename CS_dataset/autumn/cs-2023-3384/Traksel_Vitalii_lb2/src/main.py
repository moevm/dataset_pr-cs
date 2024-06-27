from PIL import Image, ImageDraw
import numpy as np

def swap(img, x0, y0, x1, y1, width):
    img_copy = img.copy()
    img1 = img_copy.crop((x0, y0, x0 + width, y0 + width))
    img1 = img1.rotate(270)
    img2 = img_copy.crop((x1, y1, x1 + width, y1 + width))
    img2 = img2.rotate(270)
    img_copy.paste(img1, (x1, y1))
    img_copy.paste(img2, (x0, y0))
    img_copy = img_copy.rotate(270)
    return img_copy


def avg_color(img, x0, y0, x1, y1):
    img_copy = img.copy()
    for y in range(y0, y1 + 1):
        for x in range(x0, x1 + 1):
            count = 0
            sum_r = 0
            sum_g = 0
            sum_b = 0
            for a in (-1, 0, 1):
                for b in (-1, 0, 1):
                    if (x + a) in range(0, img.size[0]) and (y + b) in range(0, img.size[1]) and (a or b) != 0:
                        count += 1
                        i = img.getpixel((x + a, y + b))
                        sum_r += i[0]
                        sum_g += i[1]
                        sum_b += i[2]
            sum_color = (int(sum_r / count), int(sum_g / count), int(sum_b / count))
            img_copy.putpixel((x, y), sum_color)
    return img_copy


def pentagram(img, x, y, r, thickness, color):
    drawing = ImageDraw.Draw(img)
    xy = []
    for i in (0, 2, 4, 1, 3, 0):
        phi = (np.pi / 5) * (2 * i + 3 / 2)
        node_i = (int(x + r * np.cos(phi)), int(y + r * np.sin(phi)))
        xy.append(node_i)
    x1 = x - r
    x2 = x + r
    y1 = y - r
    y2 = y + r
    center = ((x1, y1), (x2, y2))
    drawing.ellipse(center, outline=tuple(color), width=thickness)
    drawing.line(xy, fill=tuple(color), width=thickness)
    return img

