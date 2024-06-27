from PIL import Image, ImageDraw
import numpy as np
import PIL.ImageOps

def swap(img, x0,y0,x1,y1,width):
    img_new = img.copy()
    sq1 = img.copy().crop((x0, y0, x0 + width, y0 + width)).rotate(270)
    sq2 = img.copy().crop((x1, y1, x1 + width, y1 + width)).rotate(270)
    img_new.paste(sq1, (x1, y1))
    img_new.paste(sq2, (x0, y0))
    img_new = img_new.rotate(270)
    return img_new



def avg_color(img, x0, y0, x1, y1):
    img_new = img.copy()
    s = img.size
    for x in range(x0, x1 + 1):
        for y in range(y0, y1 + 1):
            mid_color = [0, 0, 0]
            pix_around = [(x - 1, y - 1), (x, y - 1), (x + 1,y - 1), (x - 1, y), (x + 1, y), (x - 1,y + 1), (x,y + 1),(x + 1,y + 1)]
            count = 0
            for i in pix_around:
                if c_range(i, s):
                    mid_color[0] += img.getpixel(i)[0]
                    mid_color[1] += img.getpixel(i)[1]
                    mid_color[2] += img.getpixel(i)[2]
                    count += 1
            mid_color[0] = int(mid_color[0] / count)
            mid_color[1] = int(mid_color[1] / count)
            mid_color[2] = int(mid_color[2] / count)
            img_new.putpixel((x, y), tuple(mid_color))
    return img_new



def pentagram(img, x, y, r, thickness, color):
    cords = ((x - r, y - r), (x + r, y + r))
    drawing = ImageDraw.Draw(img)
    drawing.ellipse((cords),outline=tuple(color), width=thickness)
    base = list()
    for i in range(5):
        phi = (np.pi/5)*(2*i+3/2)
        node_i = (int(x+r*np.cos(phi)),int(y+r*np.sin(phi)))
        base.append(node_i)
    for i in range(3):
        drawing.line((base[i],base[i+2]), fill = tuple(color), width = thickness)
    for i in range(2):
        drawing.line((base[i],base[i+3]), fill = tuple(color), width = thickness)
    return img
    

    
def c_range(cord, size):
    x, y = cord[0], cord[1]
    return x > 0 and x < size[0] and y > 0 and y < size[1]
