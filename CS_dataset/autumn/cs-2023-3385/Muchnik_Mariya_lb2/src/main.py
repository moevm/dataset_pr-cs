import math
from PIL import Image, ImageDraw

def swap(img, x0, y0, x1, y1, width):
    edit_img = img.copy()
    img1 = edit_img.crop((x0, y0, x0+width, y0+width)).rotate(-90)
    img2 = edit_img.crop((x1, y1, x1+width, y1+width)).rotate(-90)
    edit_img.paste(img1, (x1, y1))
    edit_img.paste(img2, (x0, y0))
    edit_img = edit_img.rotate(-90)
    return edit_img

def avg_color(img, x0, y0, x1, y1):
    edit_img = img.copy()
    for x in range(x0, x1+1):
        for y in range(y0, y1+1):
            sum = [0, 0, 0]
            count = 0
            for z in (-1, 0, 1):
                for d in (-1, 0, 1):
                    if not(z == 0 and d == 0) and (0 <= x+z <= edit_img.size[0]-1) and (0 <= y+d <= edit_img.size[1]-1):
                        rgb = img.getpixel((x+z, y+d))
                        sum[0] += rgb[0]
                        sum[1] += rgb[1]
                        sum[2] += rgb[2]
                        count += 1
            edit_img.putpixel((x, y), (int(sum[0]/count), int(sum[1]/count), int(sum[2]/count)))
    return edit_img


def pentagram(img, x, y, r, thickness, color):
    draw = ImageDraw.Draw(img)
    draw.ellipse(((x-r, y-r), (x+r, y+r)), fill=None, outline=tuple(color), width=thickness)
    phi = (math.pi/5)*(3/2)

    for i in (2, 4, 1, 3, 5):
        node_i = (int(x + r*math.cos(phi)), int(y + r*math.sin(phi)))
        phi = (math.pi/5)*(2*i + 3/2)
        draw.line((node_i, (int(x + r*math.cos(phi)), int(y + r*math.sin(phi)))), fill=tuple(color), width=thickness)
    return img
