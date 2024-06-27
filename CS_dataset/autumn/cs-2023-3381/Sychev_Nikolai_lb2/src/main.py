from PIL import Image, ImageDraw
import numpy as np


def pentagram(img, x, y, r, thickness, color):
    draw = ImageDraw.Draw(img, "RGB")
    coord = []
    x1, x2 = x - r, x + r
    y1, y2 = y - r, y + r
    draw.ellipse(((x1, y1), (x2, y2)), fill=None, width=thickness, outline=tuple(color))
    for i in range(5):
        phi = (np.pi / 5) * (2 * i + 3 / 2)
        node_i = int(x + r * np.cos(phi)), int(y + r * np.sin(phi))
        coord.append(node_i)
    for i in range(5):
        draw.line((coord[i], coord[(i + 2) % 5]), fill=tuple(color), width=thickness)
    return img


def swap(img, x0, y0, x1, y1, width):
    region0 = img.copy().crop((x0, y0, x0 + width, y0 + width)).rotate(-90)
    region1 = img.copy().crop((x1, y1, x1 + width, y1 + width)).rotate(-90)
    result = img.copy()
    result.paste(region1, (x0, y0))
    result.paste(region0, (x1, y1))
    return result.rotate(-90)


def avg_color(img, x0, y0, x1, y1):
    result = img.copy()
    width, height = img.size
    for x in range(x0, x1 + 1):
        for y in range(y0, y1 + 1):
            sum_rgb = [0, 0, 0]
            pixels_around = ((x + 1, y - 1), (x + 1, y), (x + 1, y + 1), (x, y - 1), (x, y + 1), (x - 1, y - 1), (x - 1, y), (x - 1, y + 1))
            pixels_around = tuple(filter(lambda c: (0 <= c[0] <= width - 1) and (0 <= c[1] <= height - 1), pixels_around))
            for i in pixels_around:
                pixel = img.getpixel(i)
                for j in range(3):
                    sum_rgb[j] += pixel[j]
            count = len(pixels_around)
            new_color = (int(sum_rgb[0] / count), int(sum_rgb[1] / count), int(sum_rgb[2] / count))
            result.putpixel((x, y), new_color)
    return result