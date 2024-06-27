import os
os.environ["OPENBLAS_NUM_THREADS"]="4"
from PIL import Image, ImageDraw
import math
def swap(img, x0,y0,x1,y1,width):
    im=img.copy()
    img1=im.crop((x0, y0, x0+width, y0+width)).rotate(270)
    img2=im.crop((x1, y1, x1+width, y1+width)).rotate(270)
    im.paste(img2,(x0, y0))
    im.paste(img1,(x1, y1))
    im=im.rotate(270)
    return im
def avg_color(img, x0,y0,x1,y1):
    im=img.copy()
    siz=im.size
    for y in range(y0, y1+1):
        for x in range(x0, x1+1):
            near=( (x-1,y-1), (x,y-1), (x+1,y-1), (x+1,y), (x+1,y+1), (x,y+1), (x-1,y+1), (x-1,y) )
            near1 = tuple(filter(lambda c: (0 <= c[0] <= siz[0] - 1) and (0 <= c[1] <= siz[1] - 1), near))
            r, g, b=0, 0, 0
            count=0
            for i in near:
                color=img.getpixel(i)
                r+=color[0]
                g+=color[1]
                b+=color[2]
                count+=1
            im.putpixel((x, y), (int(r/count),int(g/count),int(b/count)))
    return im
    

def pentagram(img, x, y, r, thickness, color):
    a=color[0]
    b=color[1]
    c=color[2]
    
    draw = ImageDraw.Draw(img, "RGB" )
    draw.ellipse((x-r, y-r, x+r, y+r),outline=(a, b, c),width=thickness)
    points=[]
    for i in range(0 ,5):
        phi = (math.pi/5)*(2*i+3/2)
        node_i=( [int(x+r*math.cos(phi)),int(y+r*math.sin(phi))])
        points.append(node_i)
    for i in range(0, 5):
        draw.line((points[i][0], points[i][1], points[(i+2)%5][0], points[(i+2)%5][1]), fill=(a, b, c), width=thickness)
    return img
