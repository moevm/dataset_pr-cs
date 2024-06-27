from numpy import pi, cos, sin
import PIL
from PIL import Image, ImageDraw, ImageOps


def pentagram(img, x0, y0, x1, y1, thickness, color):
    drawing = ImageDraw.Draw(img)
    drawing.ellipse((x0, y0, x1, y1), None, tuple(color), thickness)
    r = abs(x1 - x0) // 2
    x = x0 + abs(x1 - x0) // 2
    y = y0 + abs(x1 - x0) // 2
    ends = []
    for i in range(5):
        phi = (pi / 5) * (2 * i + 3 / 2)
        node_i = (int(x + r * cos(phi)), int(y + r * sin(phi)))
        ends.append(node_i)
    for j in range(5):
        drawing.line((ends[j],ends[(j+2)%5]), tuple(color), thickness)
    return img
    
def invert(img, N,vertical):
    inverted = ImageOps.invert(img)
    height, width = img.size
    if vertical:
        for i in range(1, (width//N) + 1, 2):
            begin = i*N
            end = (i+1)*N
            end = min(end,width)
            img.paste(inverted.crop((begin, 0, end, height)), (begin,0))
    else:
        for j in range(1, (height//N) + 1, 2):
            begin = j*N
            end = (j+1)*N
            end = min(end,height)
            img.paste(inverted.crop((0, begin, width, end)), (0,begin))
    return img

def mix(img, rules):
    res = Image.new('RGB',tuple(img.size), color = 0)
    height, width = img.size
    coordinates=[]
    for y in range(3):
        y0 = y*height//3
        y1 = (y+1)*height//3
        for x in range(3):
            x0 = x * width // 3
            x1 = (x + 1) * width // 3
            coordinates.append((x0,y0,x1,y1))
    for i in range(9):
        to_put = rules.get(i)
        res.paste(img.crop(coordinates[to_put]), coordinates[i])
    return res
