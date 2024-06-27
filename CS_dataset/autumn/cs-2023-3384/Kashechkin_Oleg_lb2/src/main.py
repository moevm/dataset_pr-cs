import numpy as np
from PIL import Image, ImageDraw

def triangle(img, x0, y0, x1, y1, x2, y2, thickness, color, fill_color):
    draw = ImageDraw.Draw(img)
    points = [(x0, y0), (x1, y1), (x2, y2)]
    if fill_color != None:
        draw.polygon(points, outline=tuple(color), width=thickness, fill=tuple(fill_color))
    else:
        draw.polygon(points, outline=tuple(color), width=thickness)
    return img
    
def change_color(img, color):
    img_arr = np.array(img)
    w,h = img.size
    colors = img.getcolors(maxcolors=w*h)
    sorted_colors = sorted(colors,key=lambda t: t[0])
    old_color = sorted_colors[-1][1]
    for i in range(len(img_arr)):
        for j in range(len(img_arr[i])):
            if img_arr[i][j][0] == old_color[0] and img_arr[i][j][1] == old_color[1] and img_arr[i][j][2] == old_color[2]:
                img_arr[i][j] = color

    img = Image.fromarray(img_arr)
    return img

def collage(img, N, M):
    width, height = img.size
    collage_width = width * M
    collage_height = height * N
    collage_img = Image.new("RGB", (collage_width, collage_height))
    
    for i in range(N):
        for j in range(M):
            collage_img.paste(img, (j * width, i * height))
    
    return collage_img