import PIL
from PIL import Image, ImageDraw
import numpy as np


def swap(img, x0,y0,x1,y1,width):
    ans = img.copy()
    tmp1 = img.copy().crop((x0, y0, x0 + width, y0 + width)).rotate(-90)
    tmp2 = img.copy().crop((x1, y1, x1 + width, y1 + width)).rotate(-90)
    ans.paste(tmp1,(x1, y1))
    ans.paste(tmp2,(x0, y0))
    return ans.rotate(-90)

def check_in(a, s):
    x, y = a[0], a[1]
    return x > 0 and x < s[0] and y > 0 and y < s[1]


def avg_color(img, x0,y0,x1,y1):
    ans = img.copy()
    s = img.size
    for x in range(x0, x1 + 1):
        for y in range(y0, y1  + 1):
            avg = [0, 0, 0]
            pix = [(x-1,y-1),(x,y-1), (x+1,y-1),
                      (x-1,y),(x+1,y),
                      (x-1,y+1), (x,y+1),(x+1,y+1)]
            cnt = 0
            for i in pix:
                if check_in(i, s):
                    avg[0] += img.getpixel(i)[0]
                    avg[1] += img.getpixel(i)[1]
                    avg[2] += img.getpixel(i)[2]
                    cnt+=1
            avg[0] = int(avg[0] / cnt)
            avg[1] = int(avg[1] / cnt)
            avg[2] = int(avg[2] / cnt)
            ans.putpixel((x,y), tuple(avg))               
    return ans


def pentagram(img, x, y, r, thickness, color):
    d=ImageDraw.Draw(img, "RGB")
    d.ellipse(((x-r, y-r), (x+r, y+r)), fill=None, width=thickness, outline=tuple(color))

    p = []
    for i in range(5):
        phi = (np.pi/5)*(2*i+3/2)
        node_i = int(x + r * np.cos(phi)),int(y + r * np.sin(phi))
        p.append(node_i)
    for i in range(5):
        d.line((p[i], p[(i+2) % 5]), tuple(color),thickness, None)
    
    return img

