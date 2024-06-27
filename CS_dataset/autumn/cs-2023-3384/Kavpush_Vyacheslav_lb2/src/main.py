import numpy as np
import PIL
from PIL import Image, ImageDraw

def pentagram(img, x, y, r, thickness, color):
    drawing = ImageDraw.Draw(img)
    xy = [x-r, y-r, x+r, y+r]
    filling = tuple(color)
    drawing.ellipse(xy, None, filling, thickness)
    for i in range(0, 5):
        phi = (np.pi/5)*(2*i+3/2)
        start = (int(x+r*np.cos(phi)), int(y+r*np.sin(phi)))
        phi = (np.pi/5)*(2*(i+2)+3/2)
        finish = (int(x+r*np.cos(phi)), int(y+r*np.sin(phi)))
        nodes = (start, finish)
        drawing.line(nodes, filling, thickness)
    return img
    
def swap(img, x0,y0,x1,y1,width):
    otv = img.copy()
    minimg1 = otv.crop((x0, y0, x0 + width, y0 + width)).rotate(-90)
    minimg2 = otv.crop((x1, y1, x1 + width, y1 + width)).rotate(-90)
    otv.paste(minimg1, (x1, y1))
    otv.paste(minimg2, (x0, y0))
    otv = otv.rotate(-90)
    return otv

def avg_color(img, x0,y0,x1,y1):
    otv = img.copy()
    arr = otv.load()
    size = otv.size
    
    def borders(ij, size0 = size):
        if (ij[0] < size0[0]) and (ij[0] >= 0) and (ij[1] < size0[1]) and (ij[1] >= 0):
            return True
        else:
            return False
    
    for i in range(x0, x1+1):
        for j in range(y0, y1+1):
            index = ((i-1, j-1), (i, j-1), (i+1, j-1), (i-1, j), (i+1, j), (i-1,j+1), (i, j+1), (i+1, j+1))
            index = tuple(filter(borders, index))
            pixel = tuple(map(img.getpixel, ((l[0], l[1]) for l in index)))
            r, g, b = 0, 0, 0
            for l in range(len(pixel)):
                r += pixel[l][0]
                g += pixel[l][1]
                b += pixel[l][2]
            filling = tuple((r//len(pixel), g//len(pixel), b//len(pixel)))
            arr[i, j] = filling
    return otv