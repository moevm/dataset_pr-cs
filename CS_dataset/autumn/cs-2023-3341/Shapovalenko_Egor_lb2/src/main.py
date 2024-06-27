import numpy as np
from PIL import Image, ImageDraw

def swap(img, x0 ,y0 ,x1, y1, width):
    first = img.crop((x0, y0, x0 + width, y0 + width))
    first = first.rotate(270)
    
    second = img.crop((x1, y1, x1 + width, y1 + width))
    second = second.rotate(270)
    
    result = img.copy()
    result.paste(first, (x1, y1))
    result.paste(second, (x0, y0))
    result = result.rotate(270)
    
    return result

def get_avg_color(img, x, y):
    width, height = img.size
    
    neighbors = []
    for i in range(-1, 2):
        for j in range(-1, 2):
            if(0 <= (x + i) < width) and (0 <= (y + j) < height):
                neighbors.append(img.getpixel((x + i, y + j)))
    neighbors.remove(img.getpixel((x, y)))
    
    resultColor = [0, 0, 0]
    for color in neighbors:
        for i in range(3):
            resultColor[i] += color[i]
    
    for i in range(3):
        resultColor[i] = int(resultColor[i] / len(neighbors))
    return tuple(resultColor)

def avg_color(img, x0, y0, x1, y1):
    result = img.copy()
    for x in range(x0, x1+1):
        for y in range(y0, y1+1):
            result.putpixel((x, y), get_avg_color(img, x, y))
    return result

def pentagram(img, x, y, r, thickness, color):
    color = tuple(color)

    drawing = ImageDraw.Draw(img)
    drawing.ellipse(((x - r, y - r), (x + r, y + r)), fill = None, outline = color, width = thickness)

    nodes = [(0, 0)] * 5
    for i in range(5):
        phi = (np.pi / 5) * (2 * i + 3 / 2)
        nodes[i] = (int(x + r * np.cos(phi)), int(y + r * np.sin(phi)))

    drawing.line((nodes[0], nodes[2], nodes[4], nodes[1], nodes[3], nodes[0]), fill = color, width = thickness)

    return img
