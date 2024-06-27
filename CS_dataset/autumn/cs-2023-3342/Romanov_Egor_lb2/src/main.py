from numpy import *
from PIL import ImageDraw, ImageChops


def pentagram(img, x0, y0, x1, y1, thickness, color):
    radius = int((x1-x0) / 2)
    centerX = int((x0+x1)/2)
    centerY = int((y0+y1)/2)
    coords=[]
    for i in range(0,10,2):
        phi = (pi/5)*(2*i+3/2)
        node_i = (int(centerX+radius*cos(phi)),int(centerY+radius*sin(phi)))
        coords.append(node_i)
        
    drawing = ImageDraw.Draw(img)
    drawing.ellipse(((x0,y0),(x1,y1)), None, tuple(color), thickness)
    
    for i in range(10*len(coords)):
        drawing.line((coords[i%5], coords[(i+1)%5]), tuple(color), thickness)
    return img
    
def invert(img, N,vertical):
    width = img.size[0]
    height =img.size[1]
    if vertical:
        for i in range(1,int(ceil(width / N)),2):
            block = (i*N,0,(i+1)*N,height);
            part = ImageChops.invert(img.crop(block))
            img.paste(part, block)

    else:
        for i in range(1,int(ceil(height / N)),2):
            block = (0,i*N,width,(i+1)*N);
            part = ImageChops.invert(img.crop(block))
            img.paste(part, block)

    return img

def mix(img,rules):
    parts = []
    coords=[]
    w = img.width
    h = img.height
    for y in range(3):
        for x in range(3):
            path = img.crop((x*(w//3), y*(h//3), (x+1)*(w//3), (y+1)*(h//3)))
            coords.append((x*(w//3), y*(h//3)))
            parts.append(path)

    for i in range(9):
        img.paste(parts[rules[i]], coords[i])
        
    return img
