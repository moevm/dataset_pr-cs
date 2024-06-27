from PIL import Image, ImageDraw
# Задача 1
def triangle(img, x0, y0, x1, y1, x2, y2, thickness, color, fill_color):
    drawing = ImageDraw.Draw(img)
    if fill_color != None:
        drawing.polygon((x0, y0, x1, y1, x2, y2), tuple(fill_color), tuple(color), thickness)
    else: drawing.polygon((x0, y0, x1, y1, x2, y2), fill_color, tuple(color), thickness)
    return img
    

# Задача 2
def change_color(img, color):
    all_color_info = img.getcolors(maxcolors = img.size[0] * img.size[1])
    color_repeat = [all_color_info[i][0] for i in range(len(all_color_info))]
    max_repeat = max(color_repeat)
    ind = color_repeat.index(max_repeat)
    most_rep_color = all_color_info[ind][1]
    red_img = img.copy()
    for x in range(img.size[0]):
        for y in range(img.size[1]):
            if red_img.getpixel((x,y)) == most_rep_color:
                red_img.putpixel((x, y), tuple(color))
    return red_img

# Задача 3
def collage(img, N, M):
    collage = Image.new(img.mode, (img.size[0]*M, img.size[1]*N), "black")
    for y in range(0, img.size[1]*N, img.size[1]):
        for x in range(0, img.size[0]*M, img.size[0]):
            collage.paste(img, (x, y))
    return collage

