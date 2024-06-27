from PIL import Image, ImageDraw
import numpy as np
# Задача 1
def triangle(img, x0, y0, x1, y1, x2, y2, thickness, color, fill_color):
    co = [(x0, y0), (x1, y1), (x2, y2)]
    drawing = ImageDraw.Draw(img)
    if fill_color is None:
        drawing.polygon(co, None, tuple(color), thickness)
        return img
    else:
        drawing.polygon(co, tuple(fill_color), tuple(color), thickness)
        return img
# Задача 2
def change_color(img, color):
    img_arr = np.array(img)
    colors = img.getcolors(maxcolors=img.size[1]*img.size[0])
    y = sorted(colors,key=lambda t: t[0])
    x = y[-1][1]
    for i in range(len(img_arr)):
        for j in range(len(img_arr[i])):
            if img_arr[i][j][0] == x[0] and img_arr[i][j][1] == x[1] and img_arr[i][j][2] == x[2]:
                img_arr[i][j] = color
    img = Image.fromarray(img_arr)
    return img
# Задача 3
def collage(img, N, M):
    x, y = img.size
    new_im = Image.new('RGB', (M * x, N * y))
    for i_M in range(M):
        for i_N in range(N):
            new_im.paste(img, (i_M * x, i_N * y))
    return new_im