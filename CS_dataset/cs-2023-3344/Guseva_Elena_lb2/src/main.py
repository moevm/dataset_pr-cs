import PIL
from PIL import Image, ImageDraw

import numpy as np

# Задача 1
def triangle(img, x0, y0, x1, y1, x2, y2, thickness, color, fill_color):
    drawing = ImageDraw.Draw(img)
    if fill_color!=None:
        drawing.polygon([(x0, y0), (x1, y1), (x2, y2)], outline=tuple(color), fill=tuple(fill_color), width=thickness)
    else:
        drawing.polygon([(x0, y0), (x1, y1), (x2, y2)], outline=tuple(color), width=thickness)
    return img
    
    
# Задача 2
def change_color(img, color):
    width, height = img.size
    new_image = img.copy()
  
    pixs_colors={}
  
    for i in range(width):
        for j in range(height):
            pixs_color = img.getpixel((i, j))
            if pixs_color in pixs_colors:
                pixs_colors[pixs_color] += 1
            else:
                pixs_colors.update({pixs_color: 1})
            
    pixs_colors = dict(sorted(pixs_colors.items(), key=lambda item: item[1]))
    color_old = list(pixs_colors.keys())[-1]
    for i in range(width):
        for j in range(height):
            pix_color = img.getpixel((i, j))
            if pix_color == color_old:
                new_image.putpixel((i, j), tuple(color))
    return new_image
    
    
    
    
    
# Задача 3
def collage(img, N, M):
    width, height = img.size
    collage_width = width * M
    collage_height = height * N
    
    collage = Image.new('RGB', (collage_width, collage_height))

    for i in range(N):
        for j in range(M):
            x = j * width
            y = i * height

            collage.paste(img, (x, y))


    return collage
