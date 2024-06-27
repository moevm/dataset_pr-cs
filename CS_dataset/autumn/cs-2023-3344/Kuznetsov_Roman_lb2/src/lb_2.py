import os
os.environ["OPENBLAS_NUM_THREADS"] = "4"

from PIL import Image, ImageDraw
import numpy as np
import math

def swap(img, x0, y0, x1, y1, width):
    image = img.copy()

    first = image.crop((x0, y0, x0 + width, y0 + width))
    second = image.crop((x1, y1, x1 + width, y1 + width))

    first = first.transpose(Image.Transpose.ROTATE_270)
    second = second.transpose(Image.Transpose.ROTATE_270)

    image.paste(first, (x1, y1))
    image.paste(second, (x0, y0))

    return image.transpose(Image.Transpose.ROTATE_270)

def near_pixels(img, x, y):
    x_min = max(0, x-1)
    x_max = min(img.width-1, x+1)
    y_min = max(0, y-1)
    y_max = min(img.height-1, y+1)

    neighbors = []

    for i in range(x_min, x_max + 1):
        for j in range(y_min, y_max +1):
            if (i, j) != (x, y):
                neighbors.append(img.getpixel((i, j)))

    return neighbors

def color_pixels(neighbors):
    sum_r, sum_g, sum_b = 0, 0, 0
    count = len(neighbors)

    for color in neighbors:
        r, g, b = color
        sum_r += r
        sum_g += g
        sum_b += b

    all_r = int(sum_r / count)
    all_g = int(sum_g / count)
    all_b = int(sum_b / count)

    return (all_r, all_g, all_b)

def avg_color(img, x0, y0, x1, y1):
    result_img = img.copy()

    for i in range(x0, x1 + 1):
        for j in range(y0, y1 + 1):
            neighbors = near_pixels(img, i, j)
            avg_color = color_pixels(neighbors)
            result_img.putpixel((i, j), avg_color)

    return result_img

def pentagram(img, x, y, r, thickness, color):
    color = tuple(color)
    drawing = ImageDraw.Draw(img)
    drawing.ellipse(((x-r,y-r), (x+r,y+r)), width = thickness, outline = color,)
    versh = []

    for i in range(5):
        phi = (math.pi/5)*(2*i+3/2)
        node_i = (int(x+r*math.cos(phi)),int(y+r*math.sin(phi)))
        versh.append(node_i)

    drawing.line((versh[0], versh[2]), fill = tuple(color), width = thickness)
    drawing.line((versh[1], versh[3]), fill = tuple(color), width = thickness)
    drawing.line((versh[2], versh[4]), fill = tuple(color), width = thickness)
    drawing.line((versh[3], versh[0]), fill = tuple(color), width = thickness)
    drawing.line((versh[4], versh[1]), fill = tuple(color), width = thickness)
    return img
