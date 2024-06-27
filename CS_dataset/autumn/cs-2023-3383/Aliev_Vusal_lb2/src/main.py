from PIL import Image, ImageDraw, ImageOps
import numpy as np

def pentagram(img, x0, y0, x1, y1, thickness, color):
    draw = ImageDraw.Draw(img)
    draw.ellipse((x0,y0,x1,y1), None, tuple(color), thickness)

    r = abs(x0-x1) // 2
    x = r + x0
    y = r + y0
    coordinates = []

    for i in range(5):
        phi = (np.pi/5) * (2*i+3/2)
        node_i = (int(x+r * np.cos(phi)), int(y+r * np.sin(phi)))
        coordinates.append(node_i)
    
    for j in range(5):
        draw.line((coordinates[j],coordinates[(j+2) % 5]), tuple(color), thickness, None)
    
    return img

def invert(img, N,vertical):
    width = img.size[0]
    height = img.size[1]

    if vertical:
        ostatok = width % N 
        count_strip = width//N

        for i in range(count_strip):
            if i % 2 == 1:
                img_crop = img.crop((i * N, 0, (i+1) * N, height))
                img_crop = ImageOps.invert(img_crop)
                img.paste(img_crop, (i * N, 0))

        if count_strip % 2 == 1 and ostatok > 0:
            img_crop = img.crop((count_strip * N, 0, width, height))
            img_crop = ImageOps.invert(img_crop)
            img.paste(img_crop, (count_strip * N, 0))

    else:
        ostatok = height % N 
        count_strip = height//N

        for i in range(count_strip):
            if i % 2 == 1:
                img_crop = img.crop((0, i * N, width, (i+1) * N))
                img_crop = ImageOps.invert(img_crop)
                img.paste(img_crop, (0, i * N))

        if count_strip % 2 == 1 and ostatok > 0:
            img_crop = img.crop((0, count_strip * N, width, height))
            img_crop = ImageOps.invert(img_crop)
            img.paste(img_crop, (0, count_strip * N))

    return img

def mix(img, rules):
    img_x, img_y = img.size[0] // 3, img.size[1] // 3
    new_img = Image.new("RGB", img.size , "white")
    coordinates = []
    for y in range(3):
        for x in range(3):
            coordinates.append((x * img_x, y * img_y, (x+1) * img_x, (y+1) * img_y))
    
    for key, item in rules.items():
        key_coor = (coordinates[key][0], coordinates[key][1])
        item_coor = coordinates[item]
        img_crop = img.crop(item_coor)
        new_img.paste(img_crop, key_coor)
    
    return new_img