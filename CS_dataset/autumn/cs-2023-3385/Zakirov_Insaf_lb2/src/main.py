import PIL
from PIL import Image, ImageDraw
import numpy as np

# Задача 1
def triangle(img, x0, y0, x1, y1, x2, y2, thickness, color, fill_color):
    new_color = (color[0], color[1], color[2])

    draw = ImageDraw.Draw(img)
    
    if fill_color :
        new_fill_color = (fill_color[0], fill_color[1], fill_color[2])
        draw.polygon((x0, y0, x1, y1, x2, y2), new_fill_color, new_color, thickness)
    else :
        draw.polygon((x0, y0, x1, y1, x2, y2), outline = new_color, width = thickness)
    
    return img

# Задача 2
def change_color(img, color):
    pix = img.load()
    width = img.size[0]
    height = img.size[1]
    colors = {}
    img_new = img.copy()

    for x in range(width):
        for y in range(height):
            color_old = pix[x, y]

            colors[color_old] = colors.get(color_old, 0) + 1

    m_color = max(colors, key=colors.get)
    
    for x in range(width):
        for y in range(height):
            if pix[x, y] == m_color:
                img_new.putpixel((x,y),tuple(color))

    return img_new

# Задача 3
def collage(img, N, M):
    w = img.size[0]
    h = img.size[1]
    w_new = w * M
    h_new = h * N

    img_new = Image.new("RGB", (w_new, h_new), (0, 0, 0))

    for x in range(M):
        for y in range(N):
            x_new = x * w
            y_new = y * h
            img_new.paste(img, (x_new, y_new))

    return img_new