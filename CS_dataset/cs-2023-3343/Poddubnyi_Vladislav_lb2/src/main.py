from PIL import Image, ImageDraw, ImageOps
from numpy import pi,cos,sin
import math
def pentagram(img, x0, y0, x1, y1, thickness, color):
    color = tuple(color)
    drawing = ImageDraw.Draw(img)
    drawing.ellipse(((x0,y0),(x1,y1)),None,color,thickness)
    r = round((x1-x0)/2)
    nodes = {}
    x = round(x0 + r)
    y = round(y0 + r)
    for i in range(5):
        phi = (pi / 5) * (2 * i + 3 / 2)
        node = (int(x + r * cos(phi)), int(y + r * sin(phi)))
        nodes[i]=[node,i+1]
        if i==4:
            nodes[i]=[node,0]
    for i in range(5):
        nextNode = nodes[nodes[i][1]]
        nextNextNode = nodes[nextNode[1]]
        drawing.line((nodes[i][0],nextNextNode[0]),color,thickness)
    return img

def invert(img, N,vertical):
    size = img.size
    numOfLines = int(math.ceil(size[0]/N))
    for i in range(numOfLines):
        if vertical:
            cropped = img.crop((N*i,0,N*(i+1),size[1]))
        else:
            cropped = img.crop((0,N*i,size[1],N*(i+1)))
        if i%2!=0:
            cropped = ImageOps.invert(cropped)

        if vertical:
            img.paste(cropped,(N*i,0))
        else:
            img.paste(cropped,(0,N*i))
    return img

def mix(img, rules):
    size = img.size
    cropedSize = (size[0]//3,size[1]//3)
    cropedImgs = []
    for i in range(3):
        for j in range(3):
            left = (j*cropedSize[0],i*cropedSize[1])
            right = ((j+1)*cropedSize[0],(i+1)*cropedSize[1])
            cropedImg = img.crop((left[0],left[1],right[0],right[1]))
            cropedImgs.append(cropedImg)
    count=0
    for i in range(3):
        for j in range(3):
            cropedImg = cropedImgs[rules[count]]
            count+=1
            img.paste(cropedImg,(j*cropedSize[0],i*cropedSize[1]))
    return img
