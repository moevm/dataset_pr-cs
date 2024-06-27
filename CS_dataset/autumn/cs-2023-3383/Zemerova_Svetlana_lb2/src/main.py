import PIL
from PIL import Image, ImageDraw
import numpy as np

def pentagram(img, x, y, r, thickness, color):
    color=tuple(color)
    drawing=ImageDraw.Draw(img,"RGB")
    drawing.ellipse(((x-r,y-r),(x+r,y+r)),fill=None, outline=color,width=thickness)
    coordinates=[]
    for i in range(5):
        phi = (np.pi/5)*(2*i+3/2)
        node_i = (int(x+r*np.cos(phi)),int(y+r*np.sin(phi)))
        coordinates.append(node_i)
    for i in range(5):
        drawing.line((coordinates[i],coordinates[(i+2)%5]), fill=color, width=thickness)
    return img

def swap(img, x0,y0,x1,y1,width):
    newimg=img.copy()
    img1=img.crop((x0,y0,x0+width,y0+width)).rotate(-90)
    img2=img.crop((x1,y1,x1+width,y1+width)).rotate(-90)
    newimg.paste(img1,(x1,y1))
    newimg.paste(img2,(x0,y0))
    newimg=newimg.rotate(-90)
    return newimg

def avg_color(img, x0,y0,x1,y1):
    newimg=img.copy()
    sz=img.size
    for y in range(y0,y1+1):
        for x in range(x0,x1+1):
            pixels=[]
            r,g,b,count=0,0,0,0
            for y2 in range(y-1,y+2):
                for x2 in range(x-1,x+2):
                    if (0<=x2<sz[0]) and (0<=y2<sz[1]) and (not((x2==x) and (y2==y))):
                        pixels.append(img.getpixel((x2,y2)))
                        count+=1
            for i in range(count):
                r+=pixels[i][0]
                g+=pixels[i][1]
                b+=pixels[i][2]
            newcolor=(int(r/count),int(g/count),int(b/count))
            newimg.putpixel((x,y),newcolor)
    return newimg
