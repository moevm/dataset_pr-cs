from PIL import ImageDraw, Image, ImageOps
import numpy as np

def pentagram(img, x0, y0, x1, y1, thickness, color):
    draw = ImageDraw.Draw(img, 'RGB')
    r = (x1-x0)//2
    center_x = x0+r
    center_y = y0+r
    points = []
    draw.ellipse((x0, y0, x1, y1), None, tuple(color), thickness)
    for i in range(5):
        phi = (np.pi/5)*(2*i+3/2)
        x = int(center_x + r*np.cos(phi))
        y = int(center_y + r*np.sin(phi))
        points.append((x,y))
    for i in range(5):
        draw.line((points[i], points[(i+2)%5]), tuple(color), thickness)
    return img

def invert(img, N, vertical):
    width, height = img.size
    if vertical:
        for i in range(0, width, N):
            if (i//N)%2==1:
                box = (i, 0, i+N, height)
                img.paste(ImageOps.invert(img.crop(box)), box)
    else:
        for i in range(0, height, N):
            if (i//N)%2==1:
                box = (0, i, width, i+N)
                img.paste(ImageOps.invert(img.crop(box)), box)
    return img

def mix(img, rules):
    parts = []
    width, height = img.size
    parts_width = width//3
    parts_height = height//3
    for i in range(3):
        for j in range(3):
            part = img.crop((j*parts_width, i*parts_height, (j+1)*parts_width, (i+1)*parts_height))
            parts.append(part)
    for key, value in rules.items():
        img.paste(parts[value], ((key%3)*parts_width, (key//3)*parts_height))
    return img
