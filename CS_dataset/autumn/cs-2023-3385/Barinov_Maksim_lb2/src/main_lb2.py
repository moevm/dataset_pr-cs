import PIL
from math import pi, cos, sin
from PIL import Image, ImageDraw, ImageOps

def pentagram(img, x0, y0, x1, y1, thickness, color):
    v = []
    n_v = []
    r = abs(x1 - x0) // 2
    x = x0 + r
    y = y0 + r
    for i in range(5):
        phi = (pi/5)*(2*i +3/2)
        n_v.append((int(x+r*cos(phi)), int(y + r*sin(phi))))
    draw = ImageDraw.Draw(img)
    draw.ellipse(((x0,y0), (x1,y1)), fill=None, outline=tuple(color), width=thickness)
    for i in range(5):
        draw.line((n_v[i], n_v[(i + 2) % 5]), tuple(color),thickness)
    return img

def invert(img, N, vertical):
    if vertical:
        for i in range(img.size[0]):
            if (i // N) % 2 == 1:
                img_1 = ImageOps.invert(img.copy().crop((i, 0, i + 1, img.size[1])))
                c = (i, 0)
                img.paste(img_1, c)
    else:
        for i in range(img.size[1]):
            if((i // N % 2== 1)):
                img_1 = ImageOps.invert(img.copy().crop((0, i, img.size[0], i + 1)))
                c = (0, i)
                img.paste(img_1, c)
    return img

def mix(img, rules):
    mimg = Image.new("RGB", (img.size[0], img.size[1]), color=0)
    s = []
    for i in range(3):
        for j in range(3):
            s.append((j*img.size[0] // 3, i * img.size[0] // 3, (j + 1) * img.size[0] // 3, (i + 1) * img.size[0] // 3))
    for i in range(9):
        img_1 = img.copy().crop(s[rules[i]])
        img_2 = (s[i][0], s[i][1])
        mimg.paste(img_1, img_2);
    return mimg


