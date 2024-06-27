from PIL import Image, ImageDraw
import numpy as np
def pentagram(img,x0,y0,x1,y1,thickness,color):
    drawing = ImageDraw.Draw(img)
    color=tuple(color)
    drawing.ellipse((x0,y0,x1,y1),None,color,thickness)
    node_i=[]
    x_null=abs(x0-x1)//2+x0
    y_null=abs(y0-y1)//2+y0
    r=abs(x1 - x0)//2
    for i in range(5):
        phi=((np.pi/5)*(2*i+3/2))
        node_i.append((int(x_null+r*np.cos(phi)),int(y_null+r*np.sin(phi))))
    for i in range(5):
        drawing.line((node_i[i],node_i[(i+2)%5]),color,thickness)
    return img
def invert(img, N,vertical):
    w,h=img.size
    pix=img.load()
    if vertical:
        for x in range(w):
            if ((x//N)%2)==1:
                for y in range(h):
                    pix_col=img.getpixel((x,y))
                    inv_col=tuple(255 - color for color in pix_col)
                    pix[x,y]=inv_col
    else:
        for y in range(h):
            if ((y//N)%2)==1:
                for x in range(w):
                    pix_col=img.getpixel((x,y))
                    inv_col=tuple(255 - color for color in pix_col)
                    pix[x,y]=inv_col
    return img
def mix(img, rules):
    w,h=img.size
    new_img=img
    d=w//3
    img_parts=[None]*9
    for i in range(3):
        for j in range(3):
            img_parts[i*3+j]=img.crop((j*d,i*d,(j+1)*d,(i+1)*d))
    coord=[]
    for i in range(3):
        for j in range(3):
            coord+=[tuple((j*d,i*d))]
    for key in rules:
        new_img.paste(img_parts[rules[key]],coord[key])
    return new_img