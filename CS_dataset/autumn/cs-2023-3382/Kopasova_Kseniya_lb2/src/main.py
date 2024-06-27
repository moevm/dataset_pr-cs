import PIL
from PIL import Image, ImageDraw
import numpy as np


def swap(img, x0,y0,x1,y1,width):
    w=width
    nimg=img.copy()
    i1=img.copy().crop((x0, y0, x0+w, y0+w)).rotate(-90)
    nimg.paste(i1, (x1, y1))
    i2=img.copy().crop((x1, y1, x1+w, y1+w)).rotate(-90)
    nimg.paste(i2, (x0, y0))
    nimg=nimg.rotate(-90)
    return nimg

def avg_color(img, x0, y0, x1, y1):
    new_img=img.copy()
    sz=img.size
    for x in range(x0, x1 + 1):
        for y in range(y0, y1 + 1):
            sum_rgb = [0, 0, 0]
            pix_ar = [(x-1,y-1), (x,y+1), (x,y-1), (x+1,y), (x+1,y-1), (x+1,y+1), (x-1,y+1), (x-1,y)]
            len_pa=len(pix_ar)
            for i in range(len_pa):
                if not filtr(pix_ar[len_pa-i-1],sz):
                    pix_ar.pop(len_pa-i-1)
            for j in pix_ar:
                pix=img.getpixel(j)
                for k in range(3):
                    sum_rgb[k] += pix[k]
            len_pa = len(pix_ar)
            new_color = (int(sum_rgb[0] / len_pa), int(sum_rgb[1] / len_pa), int(sum_rgb[2] / len_pa))
            new_img.putpixel((x, y), new_color)
    return new_img

def filtr(a,sz):
    return (a[0] >= 0) and (a[0] < sz[0]) and (a[1] >=0) and (a[1] < sz[1])

def pentagram(img, x, y, r, thickness, color):
    draw=ImageDraw.Draw(img, "RGB")
    draw.ellipse(((x-r, y-r), (x+r, y+r)), fill=None, width=thickness, outline=tuple(color))
    
    ver=[]
    for i in range(5):
        phi = (np.pi/5)*(2*i+3/2)
        node_i = (int(x+r*np.cos(phi)),int(y+r*np.sin(phi)))
        ver.append((node_i))
    
    for i in range(5):
        draw.line((ver[i],ver[(i + 2) % 5]),fill = tuple(color),width = thickness)
    
    return img