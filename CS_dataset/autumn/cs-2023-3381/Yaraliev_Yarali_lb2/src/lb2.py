from PIL import Image, ImageDraw
from math import pi, cos, sin


def swap(img, x0,y0,x1,y1,width):
    result = img.copy()
    img1 = img.copy().crop((x0, y0, x0 + width, y0 + width)).rotate(-90)
    img2 = img.copy().crop((x1, y1, x1 + width, y1 + width)).rotate(-90)
    result.paste(img2, (x0, y0))
    result.paste(img1, (x1, y1))
    return result.rotate(-90)

def avg_color(img, x0,y0,x1,y1):
    new_img = img.copy()
    width, height = img.size
    for x in range(x0, x1 + 1):
        for y in range(y0, y1 + 1):
            r,g,b = 0,0,0
            pixels_around = ((x + 1, y - 1), (x + 1, y), (x + 1, y + 1), (x, y - 1), (x, y + 1), (x - 1, y - 1), (x - 1, y), (x - 1, y + 1))
            pixels_around = tuple(filter(lambda c: (0 <= c[0] <= width - 1) and (0 <= c[1] <= height - 1), pixels_around))
            count = len(pixels_around)
            for i in pixels_around:
                pixel = img.getpixel(i)
                r += pixel[0]
                g += pixel[1]
                b += pixel[2]
            new_color = (int(r / count), int(g / count), int(b / count))
            new_img.putpixel((x, y), new_color)
    return new_img

def pentagram(img, x, y, r, thickness, color):
    draw = ImageDraw.Draw(img,'RGB')
    colors = tuple(color)
    c = []
    for i in range(5):
        phi = (pi/5)*(2*i+3/2)
        node_i = (int(x+r*cos(phi)),int(y+r*sin(phi)))
        c.append(node_i)
    shape = (x-r,y-r,x+r,y+r)
    draw.ellipse(shape,outline=colors, width = thickness)
    k = [[0,2],[2,4],[4,1],[1,3],[3,0]]
    for i in k:
        draw.line([c[i[0]],c[i[1]]],fill=colors,width=thickness)
    return img
