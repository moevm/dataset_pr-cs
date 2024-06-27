from PIL import Image, ImageDraw
import numpy as np

def make_img_part(img, x, y, width):
    imgResult = img.crop((x, y, x+width, y+width))
    imgResult = imgResult.rotate(270)
    return imgResult

def swap(img, x0 ,y0 ,x1, y1, width):
    img1 = make_img_part(img, x0, y0, width)
    img2 = make_img_part(img, x1, y1, width)
    imgResult = img.copy()
    imgResult.paste(img1, (x1, y1))
    imgResult.paste(img2, (x0, y0))
    imgResult = imgResult.rotate(270)
    return imgResult

def get_color(img, x, y):
    width, height = img.size
    pixels = img.load()
    pixelsAround = []
    for i in range(-1, 2):
        for j in range(-1, 2):
            if(0<=(x+i)<width and 0<=(y+j)<height):
                pixelsAround.append(pixels[x+i, y+j])
    pixelsAround.remove(pixels[x,y])
    resultColor = [0,0,0]
    for color in pixelsAround:
        for rgb in range(3):
            resultColor[rgb]+=color[rgb]
    for rgb in range(3):
        resultColor[rgb]=int(resultColor[rgb]/len(pixelsAround))
    return tuple(resultColor)

def avg_color(img, x0, y0, x1, y1):
    imgResult = img.copy()
    pixels = imgResult.load()
    for x in range(x0, x1+1):
        for y in range(y0, y1+1):
            pixels[x, y] = get_color(img, x, y)
    return imgResult

def get_node(num, x, y, r):
    phi = (np.pi/5)*(2*num + 3/2)
    node = (int(x + r*np.cos(phi)), int(y + r*np.sin(phi)))
    return node

def pentagram(img, x, y, r, thickness, color):
    drawing=ImageDraw.Draw(img)
    color=tuple(color)
    drawing.ellipse(((x-r, y-r),(x+r, y+r)), None, color, thickness)
    for i in range(0, 5):
        node_1 = get_node(i, x, y, r)
        node_2 = get_node(i+2, x, y, r)
        drawing.line((node_1, node_2), color, thickness)
    return img