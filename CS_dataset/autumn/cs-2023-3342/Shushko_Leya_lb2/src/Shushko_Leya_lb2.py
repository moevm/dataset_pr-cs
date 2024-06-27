from PIL import Image,ImageDraw, ImageOps
from numpy import pi, cos, sin
def pentagram(img, x0, y0, x1, y1, thickness, color):
    drawing = ImageDraw.Draw(img)
    drawing.ellipse(((x0, y0), (x1, y1)), fill = None, outline = tuple(color), width = thickness)
    r = abs(x1 - x0) // 2
    center_x = abs(x1 + x0) // 2
    center_y = abs(y1 + y0) // 2 
    points=[]
    for i in range (5):
        phi = (pi / 5) * (2 * i + 3 / 2)
        node_i = (int(center_x + r * cos(phi)), int(center_y + r * sin(phi)))
        points.append(node_i)
    for i in range (5):
        if i == 3:
            drawing.line((points[3], points[0]), fill = tuple(color), width = thickness, joint = None)
        elif i == 4:
            drawing.line((points[4], points[1]), fill = tuple(color), width = thickness, joint = None)
        else:
            drawing.line((points[i], points[i+2]), fill = tuple(color), width = thickness, joint = None)
    return img
def invert(img, N, vertical):
    width, height = img.size
    index = 0
    if vertical:
        for i in range(0, width, N):
            if index % 2 != 0:
                strip = img.crop((i, 0, i + N, height))
                strip = ImageOps.invert(strip)
                img.paste(strip, (i, 0))
            index += 1    
    else:
         for i in range(0, height, N):
            if index % 2 != 0:
                strip = img.crop((0, i, width, i + N))
                strip = ImageOps.invert(strip)
                img.paste(strip, (0, i))
            index += 1    
    return img
def mix(img, rules):
    square_width = img.width // 3
    parts = []
    points = []
    for i in range(3):
        for j in range(3):
            part = img.crop((j * square_width, i * square_width, (j + 1) * square_width, (i + 1) * square_width))
            parts.append(part)
            points.append((j * square_width, i * square_width))
    for x in range(9):
        img.paste(parts[rules[x]], points[x])
    return img
