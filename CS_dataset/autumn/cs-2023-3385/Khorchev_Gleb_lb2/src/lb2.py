import math
from PIL import Image, ImageDraw
import numpy as np

def swap(img, x0,y0,x1,y1,width):
    img_res = img.copy()
    coords_sq1 = (x0, y0, x0+width, y0+width)
    coords_sq2 = (x1, y1, x1+width, y1+width)
    square1 = img_res.crop(coords_sq1).transpose(method=Image.Transpose.ROTATE_270)
    square2 = img_res.crop(coords_sq2).transpose(method=Image.Transpose.ROTATE_270)
    img_res.paste(square1, coords_sq2)
    img_res.paste(square2, coords_sq1)
    img_res = img_res.transpose(method=Image.Transpose.ROTATE_270)
    return img_res


def avg_color(img, x0,y0,x1,y1):
    img_res = img.copy()
    pixels = img_res.load()
    for x in range(x0, x1+1):
        for y in range(y0, y1+1):
            count = 0
            colours = np.array([0, 0, 0])
            for x_temp in range(x-1, x+2):
                if x_temp < img.size[0]  and y-1 < img.size[1] and y-1>0 and x_temp>0:
                    r = img.getpixel((x_temp, y - 1))[0]
                    g = img.getpixel((x_temp, y - 1))[1]
                    b = img.getpixel((x_temp, y - 1))[2]
                    colours += np.array([r, g, b])
                    count += 1
            for x_temp in range(x-1, x+3, 2):
                if x_temp < img.size[0] and y < img.size[1] and x-1>0:
                    r = img.getpixel((x_temp, y))[0]
                    g = img.getpixel((x_temp, y))[1]
                    b = img.getpixel((x_temp, y))[2]
                    colours += np.array([r, g, b])
                    count += 1
            for x_temp in range(x-1, x+2):
                if x_temp < img.size[0] and y+1 < img.size[1] and x_temp>0 and y+1 < img.size[1]:
                    r = img.getpixel((x_temp, y+1))[0]
                    g = img.getpixel((x_temp, y+1))[1]
                    b = img.getpixel((x_temp, y+1))[2]
                    colours += np.array([r, g, b])
                    count += 1
            pixels[x, y] = (int(colours[0]//count),int(colours[1]//count),int(colours[2]//count))
    return img_res


def pentagram(img, x, y, r, thickness, color):
    coordinates_circle = [x-r, y-r, x+r, y+r]
    circle = ImageDraw.Draw(img)
    circle.ellipse(xy=coordinates_circle, fill=None, outline=tuple(color), width=thickness)
    drawing = ImageDraw.Draw(img)
    for i in range(5):
        phi_start = (math.pi / 5) * (2 * i + 3 / 2)
        node_i_start = (int(x + r * math.cos(phi_start)), int(y + r * math.sin(phi_start)))
        phi_end = (math.pi / 5) * (2 * (i+2) + 3 / 2)
        node_i_end = (int(x + r * math.cos(phi_end)), int(y + r * math.sin(phi_end)))
        drawing.line(xy=(node_i_start, node_i_end), fill=tuple(color), width=thickness)
    return img
