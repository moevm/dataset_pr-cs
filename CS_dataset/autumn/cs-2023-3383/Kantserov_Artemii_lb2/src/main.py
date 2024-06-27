from PIL import Image, ImageDraw
import numpy

# Задача 1
def triangle(img, x0, y0, x1, y1, x2, y2, thickness, color, fill_color):
    color = tuple(color)
    if fill_color != None:
        fill_color = tuple(fill_color)
    draw = ImageDraw.Draw(img)
    draw.polygon([(x0, y0), (x1, y1), (x2, y2)], fill= fill_color, width= thickness, outline= color)
    return img

# Задача 2
def change_color(img, color):
    img1 = img
    colors = dict()
    x, y = img.size
    for i in range(x):
        for j in range(y):
            col = img1.getpixel((i,j))
            if col in colors:
                colors[col] += 1
            else:
                colors[col] = 1
    k = [colors.keys()]
    v = [colors.values()]
    most = max(colors, key= lambda x: colors[x])
    for i in range(x):
        for j in range(y):
            if img1.getpixel((i,j)) == most:
                img1.putpixel((i, j), tuple(color))
    return img1


# Задача 3
def collage(img, N, M):
    w, h = img.size
    W = w*M
    H = h*N
    img1 = Image.new('RGB', (W, H), 'red')
    for i in range(0, W, w):
        for j in range(0, H, h):
            img1.paste(img, (i, j))
    return img1