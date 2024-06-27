import PIL
from PIL import Image, ImageDraw, ImageOps
import numpy as np

def pentagram(img, x0, y0, x1, y1, thickness, color):
    drawing = ImageDraw.Draw(img)
    
    radius = abs(x1 - x0) // 2
    center_x = x1 - (abs(x1 - x0) // 2)
    center_y = y1 - (abs(y1 - y0) // 2)
    
    nodes = []
    for i in range(5):
        phi = (np.pi)*(2*i+3/2)/5
        node_i = ( int(center_x + radius*np.cos(phi)), int(center_y + radius*np.sin(phi)) )
        nodes.append(node_i)
    
    nodes = [nodes[0], nodes[2], nodes[4], nodes[1], nodes[3], nodes[0]]
    
    drawing.ellipse((x0, y0, x1, y1), outline=tuple(color), width=thickness)
    drawing.line(nodes, fill=tuple(color), width=thickness)
    
    return img


def invert(img, N, vertical):
    width, height = img.size
    if (vertical):
        for j in range(1, width//N+1, 2):
            inverted_part = img.crop( (j*N, 0, (j+1)*N, height) )
            inverted_part = ImageOps.invert(inverted_part)
            img.paste(inverted_part, (j*N, 0) )
    else:
        for i in range(1, height//N+1, 2):
            inverted_part = img.crop( (0, i*N, width, (i+1)*N) )
            inverted_part = ImageOps.invert(inverted_part)
            img.paste(inverted_part, (0, i*N) )
    return img


def mix(img, rules):
    width, height = img.size
    parts = []
    for j in range(3):
        for i in range(3):
            part = img.crop( ( i*(height//3), j*(width//3), (i+1)*(height//3), (j+1)*(width//3) ) )
            parts.append( [part, (i*(height//3), j*(width//3))] )
    for i in rules:
        img.paste(parts[rules[i]][0], parts[i][1])
    return img
