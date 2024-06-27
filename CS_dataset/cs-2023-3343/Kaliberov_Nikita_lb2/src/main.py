from PIL import Image, ImageDraw, ImageOps
import numpy as np
import math

def pentagram(img, x0, y0, x1, y1, thickness, color):
    r = (x1-x0)//2
    center_x = x0+(x1-x0)//2
    center_y = y0+(y1-y0)//2
    coordinates = []
    color = tuple(color)
    for i in range(1, 6):
        coordinate_x = int(center_x+r*math.cos((math.pi/5)*(2*i+3/2)))
        coordinate_y = int(center_y+r*math.sin((math.pi/5)*(2*i+3/2)))
        coordinat = (coordinate_x, coordinate_y)
        coordinates.append(coordinat)
    drawing = ImageDraw.Draw(img)
    drawing.line(((coordinates*2)[::2] + [coordinates[0]]), color, thickness)
    drawing.ellipse((x0, y0, x1, y1), None, color, thickness)
    return img

def invert(img, N, vertical):
    vercol = img.size[0]
    horcol = img.size[1]
    if vertical:
        colums = math.ceil(vercol/N)
    else:
        colums = math.ceil(horcol/N)
    for i in range(1, colums, 2):
        if vertical:
            pol = (N*i, 0, min(N*(i+1), vercol), horcol)
        else:
            pol = (0, N*i, vercol, min(N*(i+1), horcol))
        inv_pol = ImageOps.invert(img.crop(pol))
        if vertical:
            img.paste(inv_pol, (N*i, 0))
        else:
            img.paste(inv_pol, (0, N*i))
    return img

def mix(img, rules):
    pix = np.array(img)
    width, height = img.size
    x, y = width//3, height//3
    box_l = [[] for i in range(9)]
    box = []
    for i in range(3):
        for j in range(3):
            box.append(pix[x*i:x*(i+1), y*j: y*(j+1)])
    for i in rules:
        box_l[i] = box[rules[i]]
    image = np.vstack([np.hstack((box_l[i], box_l[i+1], box_l[i+2])) for i in range(0, 7, 3)])
    img = Image.fromarray(image)
    return img
