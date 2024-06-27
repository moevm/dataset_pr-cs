from PIL import Image, ImageDraw, ImageChops
import math


def pentagram(img, x0, y0, x1, y1, thickness, color):
    coordinates = []
    color=tuple(color)
    radius=abs(x1-x0)//2
    center_x = (x1+x0)//2
    center_y = (y1+y0)//2
    for i in range(0, 5):
        phi=(math.pi/5) * (2*i + 3/2)
        node_i=(int(center_x+radius*math.cos(phi)), int(center_y + radius*math.sin(phi)))
        coordinates.append(node_i)

    img_pentagram = ImageDraw.Draw(img)
    img_pentagram.ellipse(((x0, y0), (x1, y1)), None, color, thickness)
    for i in range(0, 5):
        coordinates_line = (coordinates[i], coordinates[(i+2)%5])
        img_pentagram.line(coordinates_line, color, thickness)
    return img


def invert(img, N, vertical):
    if vertical==True:
        img=img.transpose(Image.Transpose.ROTATE_270)
        width=img.height
        height=img.width
    else:
        width=img.width
        height=img.height
    for i in range(2, height//N + (height%N!=0) + 1, 2):
        box = ((0, (i-1)*N, width, i*N))
        part = ImageChops.invert(img.crop(box))
        img.paste(part, box)
    if vertical==True:
        img=img.transpose(Image.Transpose.ROTATE_90)
    return img


def mix(img, rules):
    ans=Image.new("RGB", (img.width, img.width), 'white')
    side=img.width//3
    parts=[]
    for h in range(0, 3):
        for w in range(0, 3):
            parts.append(tuple((w*side, h*side, (w+1)*side, (h+1)*side)))
    for i in range(0, 9):
        box=img.crop(parts[rules[i]])
        ans.paste(box, (parts[i][0], parts[i][1]))
    return ans
