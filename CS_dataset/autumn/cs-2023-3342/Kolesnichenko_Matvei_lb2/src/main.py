from PIL import Image, ImageDraw
import numpy

# Задача 1
def triangle(img, x0, y0, x1, y1, x2, y2, thickness, color, fill_color):
    draw = ImageDraw.Draw(img)
    coords = [(x0,y0),(x1,y1),(x2,y2)]
    if fill_color != None:
        draw.polygon(coords, tuple(fill_color), tuple(color), thickness)
    else:
        draw.polygon(coords, None, tuple(color), thickness)
    return img

# Задача 2
def change_color(img, color):
    width, height = img.size
    counters = {}
    for x in range(0,width):
        for y in range(0, height):
            curr_color = img.getpixel((x,y))
            try:
                counters[curr_color] += 1
            except KeyError:
                counters[curr_color] = 1
    max_key = max(counters, key=counters.get)
    for x in range(0,width):
        for y in range(0, height):
            curr_color = img.getpixel((x,y))
            if curr_color == max_key:
                img.putpixel((x,y), tuple(color))
    return img

# Задача 3
def collage(img, N, M):
    width, height = img.size
    new_img = Image.new("RGB", (width*M, height*N), "white")
    for x in range(M):
        for y in range(N):
            new_img.paste(img, ((width*x), (height*y)))
    return new_img
