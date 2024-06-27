# Задача 1
from PIL import Image, ImageDraw
import operator

def triangle(img, x0, y0, x1, y1, x2, y2, thickness, color, fill_color):
    drawing = ImageDraw.Draw(img)
    if fill_color == None:
        drawing.polygon((x0, y0, x1, y1, x2, y2),width=thickness, outline=tuple(color))
    else:
        drawing.polygon((x0, y0, x1, y1, x2, y2), fill = tuple(fill_color), width=thickness, outline=tuple(color))
    return img

# Задача 2
def change_color(img, color):
    colors = img.getcolors(maxcolors=img.size[0]*img.size[1])
    
    sorted_colors = sorted(colors, key=operator.itemgetter(0))
    
    most_common_color = sorted_colors[-1][1]
    
    new_color = list(color)
    
    new_img = img.copy()
    pixels = new_img.load()

    for y in range(new_img.size[1]):
        for x in range(new_img.size[0]):
            if pixels[x, y] == most_common_color:
                pixels[x, y] = tuple(color)
    return new_img

# Задача 3
def collage(img, N, M):
    new_image = Image.new("RGB", (img.size[0]*M, img.size[1]*N))
    for i in range(new_image.size[0]):
        for j in range(new_image.size[1]):
            new_image.paste(img, (i*img.size[0], j*img.size[1]))
    return new_image
