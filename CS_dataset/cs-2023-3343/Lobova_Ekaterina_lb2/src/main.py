from PIL import Image, ImageDraw
import numpy as np
from math import pi, cos, sin

def pentagram(img, x, y, r, thickness, color):
    color=tuple(color)
    coordinates=((x-r,y-r),(x+r,y+r))
    drawing = ImageDraw.Draw(img)
    drawing.ellipse(coordinates, None, color, thickness)
    peeks=[]
    for i in range(5):
        phi = (pi / 5) * (2 * i + 3 / 2)
        peek = (int(x + r * cos(phi)), int(y + r * sin(phi)))
        peeks.append(peek)
    peeks = [peeks[0], peeks[2], peeks[4], peeks[1], peeks[3], peeks[0]]
    drawing.line(peeks, fill=tuple(color), width=thickness)
    return img
    
def swap(img, x0,y0,x1,y1, width):
    new_image = img.copy()
    img1=img.crop((x0,y0,x0+width,y0+width)).transpose(Image.Transpose.ROTATE_270)
    img2=img.crop((x1,y1,x1+width,y1+width)).transpose(Image.Transpose.ROTATE_270)
    new_image.paste(img1,(x1,y1))
    new_image.paste(img2, (x0, y0))
    new_image = new_image.transpose(Image.Transpose.ROTATE_270)
    return new_image

def avg_color(image, x0, y0, x1, y1):
    new_image = image.copy()
    for x in range(x0, x1 + 1):
        for y in range(y0, y1 + 1):
            r_sum, g_sum, b_sum = 0, 0, 0
            count = 0
            for i in range(x-1, x+2):
                for j in range(y-1, y+2):
                    if i < 0 or j < 0 or i >= image.width or j >= image.height or (x == i and y == j):
                        continue  
                    pixel_r, pixel_g, pixel_b = image.getpixel((i, j))
                    r_sum += pixel_r
                    g_sum += pixel_g
                    b_sum += pixel_b
                    count += 1
            new_color = (int(r_sum / count), int(g_sum / count), int(b_sum / count))
            new_image.putpixel((x, y), new_color)
    return new_image

