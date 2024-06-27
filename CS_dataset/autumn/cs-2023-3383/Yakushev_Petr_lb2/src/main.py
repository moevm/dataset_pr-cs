import numpy as np
from PIL import Image, ImageDraw, ImageOps

def pentagram(img, x0, y0, x1, y1, thickness, color):
    r=abs(x0-x1)//2
    draw=ImageDraw.Draw(img,'RGB')
    draw.ellipse((x0,y0,x1,y1),None,tuple(color),thickness)
    linii=[]
    for i in range(5):
        phi = (np.pi/5)*(2*i+3/2)
        node_i = (int(x0+r+r*np.cos(phi)),int(y0+r+r*np.sin(phi)))
        linii.append(node_i)
    for i in range(5):
        draw.line((linii[i], linii[(i+2)%5]),tuple(color), thickness)
    return img

def invert(img, N, vertical):
    nimg=img.copy()
    if (vertical):
        for i in range(img.size[0]): 
            if ((i // N) % 2 == 1):
                cop= ImageOps.invert(nimg.crop((i,0,i+1,img.size[1])))
                poc= (i, 0) 
                nimg.paste(cop,poc)
    else:
        for i in range(img.size[1]): 
            if ((i // N) % 2 == 1):
                cop = ImageOps.invert(img.copy().crop((0, i, img.size[0], i + 1)))
                poc = (0, i) 
                nimg.paste(cop, poc)
    return nimg

def mix(img, rules):
    mixx= Image.new("RGB", (img.size[0], img.size[1]), color=0) 
    sqr = []
    nimg=img.copy()
    for i in range(3):
        for j in range(3):
            sqr.append((j * nimg.size[0] // 3, i * nimg.size[0] // 3, (j + 1) * nimg.size[0] // 3, (i + 1) * nimg.size[0] // 3))
    for i in range(9):
        cop = nimg.crop(sqr[rules[i]]) 
        poc = (sqr[i][0], sqr[i][1]) 
        mixx.paste(cop, poc)
    return mixx
