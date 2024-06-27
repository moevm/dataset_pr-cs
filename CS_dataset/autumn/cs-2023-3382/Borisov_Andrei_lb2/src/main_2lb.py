from PIL import Image, ImageDraw
import numpy as np
import PIL.ImageOps

def pentagram(img,x0,y0,x1,y1,thickness,color):
    drawing = ImageDraw.Draw(img)
    color=tuple(color)
    drawing.ellipse((x0,y0,x1,y1),None,color,thickness)
    base = []
    dx=abs(x0-x1)//2+x0
    dy=abs(y0-y1)//2+y0
    r=abs(x1 - x0)//2
    for i in range(5):
        phi = (np.pi/5)*(2*i+3/2)
        node_i = (int(dx+r*np.cos(phi)),int(dy+r*np.sin(phi)))
        base.append(node_i)
    for i in range(3):
        drawing.line((base[i],base[i+2]), color, thickness)
    for i in range(2):
        drawing.line((base[i],base[i+3]), color, thickness)
    return img

def invert(img, N,vertical):
    lenn = img.size
    if vertical == 1:
        for i in range(1, ((lenn[0]//N)+1), 2):
            invert_img = img.crop((N*i, 0, N*i+N, lenn[1]))
            invert_img = PIL.ImageOps.invert(invert_img)
            img.paste(invert_img, (N*i, 0))
    if vertical == 0:
        for i in range(1, ((lenn[1]//N)+1), 2):
            invert_img = img.crop((0, N*i, lenn[0], N*i+N))
            invert_img = PIL.ImageOps.invert(invert_img)
            img.paste(invert_img, (0,N*i))
    return img

def mix(img, rules):
    size = img.size
    new_img=img
    size_one=size[0]//3
    parts=[None]*9
    for i in range(3):
        for j in range(3):
            parts[i*3+j]=img.crop((j*size_one,i*size_one,(j+1)*size_one,(i+1)*size_one))
    coord=[]
    for i in range(3):
        for j in range(3):
            coord+=[tuple((j*size_one,i*size_one))]
    for key in rules:
        new_img.paste(parts[rules[key]],coord[key])
    return new_img