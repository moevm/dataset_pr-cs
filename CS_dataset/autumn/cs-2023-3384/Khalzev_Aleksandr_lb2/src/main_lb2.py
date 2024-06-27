from PIL import Image, ImageDraw
import math as m

def pentagram(img, x0, y0, x1, y1, thickness, color):
    color = (color[0], color[1], color[2])
    dr = ImageDraw.Draw(img)
    x_center = int((x1 + x0) / 2)
    y_center = int((y1 + y0) / 2)
    rad = int((x1 - x0) / 2)

    ver = [0 for _ in range(5)]
    for i in range(5):
        phi = (m.pi/5)*(2*i+3/2)
        node_i = (int(x_center + rad * m.cos(phi)),int(y_center + rad * m.sin(phi)))
        ver[i] = node_i

    for i in range(5):
        dr.line((ver[i], ver[(i+2)%5]), fill = color, width = thickness)
    dr.ellipse((x0, y0, x1, y1), fill=None, outline = color, width = thickness)
    
    return img

def invert(img, N, vertical):
    if vertical == True:
        for x in range(img.size[0]):
            for y in range(img.size[1]):
                if (x // N) % 2 == 1:
                    img.putpixel((x, y), (255 - img.getpixel((x, y))[0], 255 - img.getpixel((x, y))[1], 255 - img.getpixel((x, y))[2]))
                else:
                    break
    else:
        for y in range(img.size[1]):
            for x in range(img.size[0]):
                if (y // N) % 2 == 1:
                    img.putpixel((x, y), (255 - img.getpixel((x, y))[0], 255 - img.getpixel((x, y))[1], 255 - img.getpixel((x, y))[2]))
                else:
                    break  
    return img

def mix(img, rules):

    parts = []
    part_size = img.size[0] // 3

    for i in range(3):
        for j in range(3):
            left = j * part_size
            upper = i * part_size
            right = left + part_size
            lower = upper + part_size
            part = img.crop((left, upper, right, lower))
            parts.append(part)

    mixed_parts = [parts[rules[i]] for i in range(9)]

    new_img = Image.new("RGB", img.size, None)

    for i in range(3):
        for j in range(3):
            left = j * part_size
            upper = i * part_size
            new_img.paste(mixed_parts[i * 3 + j], (left, upper))

    return new_img
    







