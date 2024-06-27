from PIL import ImageDraw, ImageOps
from numpy import pi, cos, sin


def pentagram(img, x0, y0, x1, y1, thickness, color):
    rgb = tuple(color)
    drawing = ImageDraw.Draw(img)
    drawing.ellipse([(x0, y0), (x1, y1)], width=thickness, outline=rgb)
    center_x = (x1 + x0) // 2
    center_y = (y1 + y0) // 2 
    radius = (x1 - x0) // 2
    points = []
    for i in range(5):
        phi = pi * (2 * i + 3 / 2) / 5
        node_i = (int(center_x + radius * cos(phi)), int(center_y + radius * sin(phi)))
        points.append(node_i)
    for i in range(5):
        if i == 3:
            drawing.line([points[i], points[0]], fill=rgb, width=thickness)
        elif i == 4:
            drawing.line([points[i], points[1]], fill=rgb, width=thickness)
        else:
            drawing.line([points[i], points[i + 2]], fill=rgb, width=thickness)
    return img



def invert(img, N, vertical):
    width, height = img.size
    count = 0
    if vertical:
        for i in range(0, width, N):
            if count % 2:
                part = img.crop((i, 0, i + N, height))
                inverted = ImageOps.invert(part)
                img.paste(inverted, (i, 0))
            count += 1
    else:
        for i in range(0, height, N):
            if count % 2:
                part = img.crop((0, i, width, i + N))
                inverted = ImageOps.invert(part)
                img.paste(inverted, (0, i))
            count += 1

    return img


def mix(img, rules):
    block_x = img.width // 3
    block_y = img.height // 3
    parts = []
    points = []
    for y in range(3):
        for x in range(3):
            part = img.crop((x * block_x, y * block_y, (x + 1) * block_x, (y + 1) * block_y))
            points.append((x * block_x, y * block_y))
            parts.append(part)

    for i in range(9):
        img.paste(parts[rules[i]], points[i])

    return img
    

