from numpy import pi, sin, cos, ceil
from PIL import Image, ImageDraw, ImageOps

def pentagram(img, x0, y0, x1, y1, thickness, color):
    drawing = ImageDraw.Draw(img)
    colour = tuple(color)
    drawing.ellipse(((x0, y0), (x1, y1)), width=thickness, outline=colour)
    r = (x1 - x0) // 2
    x = (x1 + x0) // 2
    y = (y1 + y0) // 2
    dots = []
    for i in range(5):
        phi = (pi / 5) * (2 * i + 3 / 2)
        node_i = (int(x+r*cos(phi)),int(y+r*sin(phi)))
        dots.append(node_i)
    for i in range(2):
        crd = (dots[i-2], dots[i], dots[i+2])
        drawing.line(crd, fill=colour, width=thickness)
    drawing.line((dots[2], dots[-1]), fill=colour, width=thickness)
        
    return img

def invert(img, N, vertical):
    width, height = img.size
    if vertical:
        count = int(ceil(width / N))
        for i in range(1, count, 2):
            x1 = N*i
            x2 = N*(i+1)
            if x2 > width:
                x2 = width
            y1 = 0
            y2 = height
            img.paste(ImageOps.invert(img.crop((x1,y1,x2,y2))), (x1, y1))
    else:
        count = int(ceil(height / N))
        for i in range (count):
            if i%2!=0:
                x1=0
                x2 = width
                y1 = N*i
                y2 = N*(i+1)
                if y2 > height: 
                    y2 = height
                img.paste(ImageOps.invert(img.crop((x1,y1,x2,y2))), (x1, y1))
    return img




def mix(img, rules):
    nw = img.width//3
    squares=[]
    boxes = []
    for i in range(1, 4):
        for j in range(1, 4):
            square = img.crop(((j - 1) * nw, (i - 1) * nw, j * nw,i * nw))
            squares.append(square)
            boxes.append(((j - 1) * nw, (i - 1) * nw, j * nw,i * nw))
    for orig, final in rules.items():
        img.paste(squares[final], boxes[orig])
    return img