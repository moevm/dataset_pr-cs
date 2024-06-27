import PIL
from PIL import Image, ImageDraw

def triangle(img, x0, y0, x1, y1, x2, y2, thickness, color, fill_color):
    pic = ImageDraw.Draw(img)
    if fill_color == None:
        pic.polygon([(x0,y0), (x1, y1), (x2,y2)], None, (color[0], color[1], color[2]), thickness)
        return img
    else:
        pic.polygon([(x0,y0), (x1, y1), (x2,y2)], (fill_color[0], fill_color[1], fill_color[2]), (color[0], color[1], color[2]), thickness)
        return img
    
    
    
# Задача 2
def change_color(img, color):
    colors = img.getcolors(10000)
    max_num = 0
    color_avg = (0,0,0)
    for i in colors:
        if max_num < i[0]:
            max_num = i[0]
            color_avg = i[1]
    
    img_pix = img.load()
    for x in range(img.size[0]):
        for y in range(img.size[1]):
            if img_pix[x, y] == color_avg:
                img_pix[x, y] = (color[0], color[1], color[2])
    return img

# Задача 3
def collage(img, N, M):
    x = img.size[0]
    y = img.size[1]
    img_paste = Image.new("RGB", (x * M, y * N), (0, 0, 0))
    for y_paste in range(0, img_paste.size[1], y):
        for x_paste in range(0, img_paste.size[0], x):
            img_paste.paste(img, (x_paste, y_paste))
    return img_paste
