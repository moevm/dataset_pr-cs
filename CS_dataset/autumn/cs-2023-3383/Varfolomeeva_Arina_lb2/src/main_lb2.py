import PIL
from PIL import Image, ImageDraw
# Задача 1
def triangle(img, x0, y0, x1, y1, x2, y2, thickness, color, fill_color):
    drawing = ImageDraw.Draw(img)
    if fill_color:
        drawing.polygon([(x0, y0), (x1, y1), (x2, y2)], fill = tuple(fill_color), outline = tuple(color), width = thickness)
    else:
        drawing.polygon([(x0, y0), (x1, y1), (x2, y2)], outline = tuple(color), width = thickness)
    return img

# Задача 2
def change_color(img, color):
    colors = make_dict_colors(img)
    freq_color = find_freq_color(colors)
    img_new  = img.copy()
    for x in range(img.size[0]):
        for y in range(img.size[1]):
            if img.getpixel((x, y)) == freq_color:
                img_new.putpixel((x, y), tuple(color))
    return img_new
    
def make_dict_colors(img):
    colors = dict()
    for x in range(img.size[0]):
        for y in range(img.size[1]):
            if img.getpixel((x, y)) in colors:
                colors[img.getpixel((x, y))] += 1
            else:
                colors[img.getpixel((x, y))] = 1
    return colors

def find_freq_color(colors):
    mx_color = 0
    for key, value in colors.items():
        if value > mx_color:
            freq_color = key
            mx_color = value
    return freq_color
    
# Задача 3
def collage(img, N, M):
    img_new = Image.new("RGB", (img.width * M, img.height * N), (0, 0, 0))
    for i in range(M):
        for j in range(N):
            img_new.paste(img, (i * img.width, j * img.height))
    return img_new
