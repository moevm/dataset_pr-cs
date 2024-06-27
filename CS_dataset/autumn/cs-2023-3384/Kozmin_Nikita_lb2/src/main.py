from PIL import Image, ImageDraw, ImageOps
from numpy import pi, cos, sin


def pentagram(img, x0, y0, x1, y1, thickness, color):
    color = tuple(color)
    drawing = ImageDraw.Draw(img)
    drawing.ellipse(((x0, y0), (x1, y1)), None, color, thickness)
    r, i = abs(x1 - x0) // 2, 0
    x, y = (x1+x0) // 2, (y1+y0) // 2
    
    coords = []
    for i in range(0, 5):
        phi = (pi/5)*(2*i+3/2)
        node_i = (int(x+r*cos(phi)), int(y+r*sin(phi)))
        coords.append(node_i)
        
    cur_node_i = coords[0]
    for i in range(2, 11, 2):
        next_node_i = coords[i % 5]
        drawing.line(((cur_node_i), (next_node_i)), color, thickness)
        cur_node_i = next_node_i
    
    return img


def invert(img, N, vertical):
    x_size, y_size = img.size
    if vertical:
        for i in range(1, (x_size // N) + 1, 2):
            crp = img.crop((N*i, 0, min(x_size, N*(i+1)), y_size))
            crp = ImageOps.invert(crp)
            img.paste(crp, (N*i, 0))
    else:
        for i in range(1, (y_size // N) + 1, 2):
            crp = img.crop((0, N*i, x_size, min(y_size, N*(i+1))))
            crp = ImageOps.invert(crp)
            img.paste(crp, (0, N*i))
    return img


def mix(img, rules):
    x_size, y_size = img.size
    columns, lines = 3, 3
    x_size //= columns
    y_size //= lines
    new_img = Image.new("RGB", img.size)
    for place, value in rules.items():
        crp = img.crop((value % columns * x_size,
                        value // columns * y_size,
                        value % columns * x_size + x_size,
                        value // columns * y_size + y_size))
        new_img.paste(crp, (place % columns * x_size,
                        place // columns * y_size))
    img.paste(new_img)
    return img

def invert(img, N, vertical):
    x_size, y_size = img.size
    if vertical:
        for i in range(1, (x_size // N) + 1, 2):
            crp = img.crop((N*i, 0, min(x_size, N*(i+1)), y_size))
            crp = ImageOps.invert(crp)
            img.paste(crp, (N*i, 0))
    else:
        for i in range(1, (y_size // N) + 1, 2):
            crp = img.crop((0, N*i, x_size, min(y_size, N*(i+1))))
            crp = ImageOps.invert(crp)
            img.paste(crp, (0, N*i))
    return img


def mix(img, rules):
    x_size, y_size = img.size
    columns, lines = 3, 3
    x_size //= columns
    y_size //= lines
    new_img = Image.new("RGB", img.size)
    for place, value in rules.items():
        crp = img.crop((value % columns * x_size,
                        value // columns * y_size,
                        value % columns * x_size + x_size,
                        value // columns * y_size + y_size))
        new_img.paste(crp, (place % columns * x_size,
                        place // columns * y_size))
    img.paste(new_img)
    return img
