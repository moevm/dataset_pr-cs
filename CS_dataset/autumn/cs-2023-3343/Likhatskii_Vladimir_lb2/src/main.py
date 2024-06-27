import PIL 
import math 
from PIL import Image, ImageDraw, ImageOps

def avg(*args):
    return sum(args) // len(args)

def radius_vector(center, dist, angle): 
    x, y = center
    v = (
        int(x + dist*math.cos(angle)), 
        int(y + dist*math.sin(angle))
        )

    return v 

def true_polygon(n, center, radius, rotation=0):
    points = []

    for i in range(n): 
        angle = 2*i*math.pi/n
        point = radius_vector(center, radius, angle + rotation)
        points.append(point)

    return points

def pentagram(img: Image.Image, x0, y0, x1, y1, thickness, color):
    color = tuple(color)
    radius = (x1 - x0) // 2
    center = (avg(x1, x0), avg(y1, y0))
    pentagon_ = true_polygon(5, center, radius, 3*math.pi/10)

    draw = ImageDraw.Draw(img)
    draw.ellipse((x0, y0, x1, y1), None, color, thickness)
    for i in range(5): 
        start = pentagon_[i]
        end = pentagon_[(i + 2) % len(pentagon_)]
        draw.line((start, end), color, thickness, 'curve')

    return img

def invert(img: Image.Image, N, is_vertical):
    img = img.rotate(-90 * is_vertical, Image.Resampling.NEAREST, True)
    offset = N

    while offset <= img.size[1]: 
        box = (0, offset, img.size[0], offset + N)
        area = img.crop(box)
        area = ImageOps.invert(area)
        img.paste(area, box)

        offset += 2*N 

    img = img.rotate(90 * is_vertical, Image.Resampling.NEAREST, True)

    return img 

def mix(img: Image.Image, rules: "dict[int, int]"):
    result = img.copy()
    parts = []
    w = img.size[0] // 3
    h = img.size[1] // 3

    for i in range(3): 
        for j in range(3): 
            parts.append((j * w, i * w, (j + 1) * w, (i + 1) * w,))
    
    for rule in rules.items():
        to_, from_ = rule 
        result.paste(img.crop(parts[from_]), parts[to_])

    return result