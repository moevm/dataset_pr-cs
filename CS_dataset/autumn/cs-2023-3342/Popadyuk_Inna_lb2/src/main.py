import numpy as np
from PIL import Image, ImageDraw
import math 

def swap(img, x0,y0,x1,y1,width):
    result = img.copy()
    zone1 = (x0, y0, x0+width, y0+width)
    zone2 = (x1, y1, x1+width, y1+width)
    new_zone1 = result.crop(zone1).rotate(angle=-90)
    new_zone2 = result.crop(zone2).rotate(angle=-90)
    result.paste(new_zone1, (x1, y1))
    result.paste(new_zone2, (x0, y0))
    result = result.rotate(angle=-90)
    return result


def avg_color(img, x0,y0,x1,y1):
    result = img.copy()
    width = img.size[0]
    height = img.size[1]
    for x in range(x0, x1+1):
        for y in range(y0, y1+1):
            red=[]
            green=[]
            blue=[]
            if x > 0:
                colors = img.getpixel((x-1, y))
                red.append(colors[0])
                green.append(colors[1])
                blue.append(colors[2])
                if y < (height - 1):
                    colors = img.getpixel((x - 1, y + 1))
                    red.append(colors[0])
                    green.append(colors[1])
                    blue.append(colors[2])
                if y > 0:
                    colors = img.getpixel((x - 1, y - 1))
                    red.append(colors[0])
                    green.append(colors[1])
                    blue.append(colors[2])
            if y > 0:
                colors = img.getpixel((x, y-1))
                red.append(colors[0])
                green.append(colors[1])
                blue.append(colors[2])
            if x < (width - 1):
                colors = img.getpixel((x+1, y))
                red.append(colors[0])
                green.append(colors[1])
                blue.append(colors[2])
                if y < (height - 1):
                    colors = img.getpixel((x + 1, y + 1))
                    red.append(colors[0])
                    green.append(colors[1])
                    blue.append(colors[2])
                if y > 0:
                    colors = img.getpixel((x + 1, y - 1))
                    red.append(colors[0])
                    green.append(colors[1])
                    blue.append(colors[2])
            if y < (height - 1):
                colors = img.getpixel((x, y + 1))
                red.append(colors[0])
                green.append(colors[1])
                blue.append(colors[2])
            new_red = int(sum(red)/len(red))
            new_blue = int(sum(blue)/len(blue))
            new_green = int(sum(green)/len(green))
            rgb = (new_red, new_green, new_blue)
            result.putpixel((x, y), rgb)
    return result


def pentagram(img, x, y, r, thickness, color):
    drawing = ImageDraw.Draw(img)
    drawing.ellipse((x-r, y-r, x+r, y+r), fill=None, outline=tuple(color), width=thickness)
    vertexes = []
    for i in range(5):
        phi = (math.pi/5)*(2*i+3/2)
        vertex = (int(x+r*math.cos(phi)),int(y+r*math.sin(phi)))
        vertexes.append(vertex)
    for i in range(5):
        drawing.line(xy=(vertexes[i], vertexes[(i+2)%5]), fill=tuple(color), width=thickness, joint=None)
    return img