import PIL
from PIL import Image, ImageDraw


def triangle(img, x0, y0, x1, y1, x2, y2, thickness, color, fill_color):
    draw = ImageDraw.Draw(img)
    if fill_color == None:
        draw.polygon([(x0, y0), (x1, y1), (x2, y2)], None, (color[0], color[1], color[2]), thickness)
        return img
    else:
        draw.polygon([(x0, y0), (x1, y1), (x2, y2)], (fill_color[0], fill_color[1], fill_color[2]),
                     (color[0], color[1], color[2]), thickness)
        return img


# Задача 2
def change_color(img, color):
    colors = img.getcolors(100000)
    maxcolor = 0
    color_of_max = (0, 0, 0)
    for i in colors:
        if maxcolor < i[0]:
            maxcolor = i[0]
            color_of_max = i[1]

    pixdata = img.load()
    for y in range(img.size[1]):
        for x in range(img.size[0]):
            if pixdata[x, y] == color_of_max:
                pixdata[x, y] = (color[0], color[1], color[2])
    return img


# Задача 3
def collage(img, N, M):
    x, y = img.size[0], img.size[1]
    back = Image.new("RGB", (x * M, y * N), (0, 0, 0))
    for back_y in range(0, back.size[1], y):
        for back_x in range(0, back.size[0], x):
            back.paste(img, (back_x, back_y))
    return back