import PIL
from PIL import Image, ImageDraw
import numpy as np

def triangle(img, x0, y0, x1, y1, x2, y2, thickness, color, fill_color):
    drawing = ImageDraw.Draw(img)
    color = tuple(color)
    if fill_color is not None:
        fill_color = tuple(fill_color)
    drawing.polygon((x0, y0, x1, y1, x2, y2), fill_color, color, thickness)

    return img


def change_color(img: Image, color):
    arr = np.asarray(img).copy()
    colors = {}
    color = tuple(color)
    for i in range(len(arr)):
        for j in range(len(arr[0])):
            px_color = tuple(arr[i][j])
            if px_color in colors:
                colors[px_color] += 1
            else:
                colors[px_color] = 1
    orig_color = max(colors, key=colors.get)
    for i in range(len(arr)):
        for j in range(len(arr[0])):
            px_color = tuple(arr[i][j])
            if px_color == orig_color:
                arr[i][j] = np.array(color)
    return Image.fromarray(arr)



def collage(img, N, M):
    width, height = img.size

    a = M * width
    b = N * height

    img_new = Image.new("RGB", (a, b), 'white')

    for x in range(0, a, width):
        for y in range(0, b, height):
            img_new.paste(img, (x, y))

    return img_new



