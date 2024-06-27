from numpy import cos, sin, pi, ceil
from PIL import Image, ImageDraw, ImageOps

def pentagram(img, x0, y0, x1, y1, thickness, color):
    color = tuple(color)  
    drawer = ImageDraw.Draw(img)
    drawer.ellipse(((x0, y0), (x1, y1)), outline=color, width=thickness)

    r = abs(x1 - x0) // 2
    x = x1 - (abs(x1 - x0) // 2)
    y = y1 - (abs(y1 - y0) // 2)

    vertices = []
    for i in [0, 2, 4, 1, 3]:
        phi = (pi/5)*(2*i+3/2)
        node_i = (int(x+r*cos(phi)),int(y+r*sin(phi)))
        vertices.append(node_i)

    for i in range(5):
        j = (i+1)%5
        k = (i+2)%5
        drawer.line((vertices[i], vertices[j], vertices[k]), color, thickness)
        
    return img

def clamp(n, bound):
    if n < 0: return 0
    if n > bound: return bound
    return n

def invert(img, N, vertical):
    width, height = img.size

    segment_count = int(ceil((width if vertical else height) / N))

    for i in range(1, segment_count, 2):
        if vertical:
            x1, x2 = N*i, clamp(N*(i+1), width)
            y1, y2 = 0, height
        else:
            x1, x2 = 0, width
            y1, y2 = N*i, clamp(N*(i+1), height)

        img.paste(ImageOps.invert(img.crop((x1,y1,x2,y2))), (x1, y1))

    return img

def mix(img, rules):
    side, _ = [x//3 for x in img.size]

    crops = []
    for i in range(3):
        for j in range(3):
            coords = (side*j, side*i, side*(j+1), side*(i+1))
            crops.append((coords, img.crop(coords)))
    
    for orig, final in rules.items():
        _, final_crop = crops[final]
        orig_coords, _ = crops[orig]
        img.paste(final_crop, orig_coords)

    return img

    