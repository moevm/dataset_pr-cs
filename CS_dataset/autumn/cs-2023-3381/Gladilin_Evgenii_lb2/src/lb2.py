import PIL
from PIL import Image, ImageDraw
from math import pi, cos, sin

def swap(img, x0, y0, x1, y1, width):
    img_result = img.copy()
    img1 = img.crop((x0, y0, x0 + width, y0 + width))
    img2 = img.crop((x1, y1, x1 + width, y1 + width))
    img1 = img1.rotate(270)
    img2 = img2.rotate(270)
    img_result.paste(img1, (x1, y1))
    img_result.paste(img2, (x0, y0))
    img_result = img_result.rotate(270)
    return img_result


def f(img, x, y, size_x, size_y):
    a = set()
    l = 0
    pixdata = img.load()
    for i in range(-1, 2):
        for j in range(-1, 2):
            if (i != 0 or j != 0) and (size_x > x+i >= 0 and size_y > y+j >= 0):
                l+=1
                a.add((x+i,y+j))                
    r = g = b = l = 0
    for i in a:
        l += 1
        r += pixdata[i][0]
        g += pixdata[i][1]
        b += pixdata[i][2]
    colour = (int(r / l), int(g / l), int(b / l))
    return colour


def avg_color(img, x0, y0, x1, y1):
    result = img.copy()
    width = result.size[0]
    height = result.size[1]
    for x in range(x0,x1+1):
        for y in range(y0,y1+1):
            result.putpixel((x,y),f(img,x,y,width,height))
    return result


def pentagram(img, x, y, r, thickness, color):
    draw = ImageDraw.Draw(img,'RGB')
    colors = tuple(color)
    coords = []
    for i in range(5):
        phi = (pi/5)*(2*i+3/2)
        node_i = (int(x+r*cos(phi)),int(y+r*sin(phi)))
        coords.append(node_i)
    shape = (x-r,y-r,x+r,y+r)
    draw.ellipse(shape,outline=colors, width = thickness)
    c = [[0,2],[2,4],[4,1],[1,3],[3,0]]
    for i in c:
        draw.line([coords[i[0]],coords[i[1]]],fill=colors,width=thickness)
    return img

