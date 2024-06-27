from PIL import Image, ImageDraw
import itertools
import math

def pentagram(img, x0, y0, x1, y1, thickness, color):
    color = (color[0], color[1], color[2])
    draw = ImageDraw.Draw(img)

    draw.arc((x0, y0, x1, y1), fill=color, width=thickness, start=0, end=360)

    x = int((x1 + x0) / 2)
    y = int((y1 + y0) / 2)
    r = int((x1 - x0) / 2)
    
    verts = []
    for i in range(5):
        phi = math.pi / 5 * (2 * i + 3 / 2)
        vert = (int((x + r * math.cos(phi))), int((y + r * math.sin(phi))))
        verts.append(vert)

    for i in range(5):
        v0 = verts[i]
        v1 = verts[(i + 2) % 5]
        draw.line((v0[0], v0[1], v1[0], v1[1]), fill=color, width=thickness)
    
    return img

def invert(img, N, vertical):
    if vertical:
        for x in range(img.size[0]):
            if (x // N) % 2 == 1:
                for y in range(img.size[1]):
                    px = img.getpixel((x, y))
                    img.putpixel((x, y), (255 - px[0], 255 - px[1], 255 - px[2]))
    else:
        for y in range(img.size[1]):
            if (y // N) % 2 == 1:
                for x in range(img.size[0]):
                    px = img.getpixel((x, y))
                    img.putpixel((x, y), (255 - px[0], 255 - px[1], 255 - px[2]))
    return img

def mix(img, rules):
    img_new = Image.new('RGB', img.size)
    size_x, size_y = img.size 
    
    parts_sz = { 
        x + y*3: (
            (size_x * x) // 3,       (size_y * y) // 3,
            (size_x * (x + 1)) // 3, (size_y * (y + 1)) // 3
        ) 
        for x, y in itertools.product(range(3), range(3))
    }

    for i in range(9):
       img_new.paste(img.crop(parts_sz[rules[i]]), parts_sz[i])

    return img_new 