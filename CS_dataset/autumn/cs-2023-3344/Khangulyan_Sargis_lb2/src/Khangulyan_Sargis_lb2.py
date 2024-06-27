import os
os.environ["OPENBLAS_NUM_THREADS"] = "4"

from PIL import Image, ImageDraw
from math import *

def swap(img, x0, y0, x1, y1, width):
    cp_img = img.copy()
    img1 = cp_img.crop((x0, y0, x0+width, y0+width))
    img1 = img1.transpose(Image.Transpose.ROTATE_270)
    img2 = cp_img.crop((x1, y1, x1+width, y1+width))
    img2 = img2.transpose(Image.Transpose.ROTATE_270)
    cp_img.paste(img1, (x1, y1))
    cp_img.paste(img2, (x0, y0))
    cp_img = cp_img.transpose(Image.Transpose.ROTATE_270)
    return cp_img



def avg_color(img, x0, y0, x1, y1):
    av_img = img.copy()
    for x in range(x0, x1+1):
        for y in range(y0, y1+1):
            pixels_around = []
            r, g, b = 0, 0, 0
            count = 0

            begin_x = max(x-1, 0)
            begin_y = max(y-1, 0)
            end_x = min(img.width-1, x+1)
            end_y = min(img.height-1, y+1)

            for k in range(begin_x, end_x+1):
                for n in range(begin_y, end_y+1):
                    if (k, n) != (x, y):
                        pixels_around.append(img.getpixel((k, n)))
                        count += 1
            
            for i in pixels_around:
                r += i[0]
                g += i[1]
                b += i[2]
            
            av_img.putpixel((x, y), (int(r/count), int(g/count), int(b/count)))

    return av_img



def pentagram(img, x, y, r, thickness, color):
    color = tuple(color)
    drawing = ImageDraw.Draw(img)
    x1y1 = (x-r, y-r)
    x2y2 = (x+r, y+r)
    drawing.ellipse((x1y1, x2y2), width = thickness, outline = color,)
    
    versh = []
    for i in range(5):
        phi = (pi/5)*(2*i+3/2)
        node_i = (int(x+r*cos(phi)),int(y+r*sin(phi)))
        versh.append(node_i)
    
    for j in range(5):
        if j < 3:
            drawing.line((versh[0+j], versh[2+j]), fill = color, width = thickness, joint = None)
        elif j == 3:
            drawing.line((versh[3], versh[0]), fill = color, width = thickness, joint = None)
        else:
            drawing.line((versh[4], versh[1]), fill = color, width = thickness, joint = None)
    return img