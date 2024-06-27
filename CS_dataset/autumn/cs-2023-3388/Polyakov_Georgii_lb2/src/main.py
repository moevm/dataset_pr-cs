from PIL import Image, ImageDraw

def triangle(img, x0, y0, x1, y1, x2, y2, thickness, color, fill_color):
    drawing = ImageDraw.Draw(img)
    if fill_color == None:
        drawing.polygon([(x0,y0), (x1, y1), (x2,y2)], fill = None, outline = tuple(color), width=thickness)
    else:
        drawing.polygon([(x0,y0), (x1, y1), (x2,y2)], fill = tuple(fill_color), outline = tuple(color), width=thickness)
    return img


def change_color(img, color):
    img_new = img
    x = img.size[0]
    y = img.size[1]
    count_pix_color = dict()
    data_pixels = list(img.getdata())
    for pix in data_pixels:
        if pix not in count_pix_color:
            count_pix_color[pix] = 1
        else:
            count_pix_color[pix]+=1
    max_count_color = max(count_pix_color, key = count_pix_color.get)
    drawing = ImageDraw.Draw(img_new)
    for i in range (x):
        for j in range (y):
            if img_new.getpixel((i, j)) == max_count_color:
                drawing.point((i, j), tuple(color))
    return img_new


def collage(img, N, M):
    x = img.size[0]
    y = img.size[1]
    img_new = Image.new("RGB", (x * M, y * N), "white")
    x_new = img_new.size[0]
    y_new = img_new.size[1]
    for i in range(0, x_new, x):
        for j in range (0, y_new, y):
            img_new.paste(img, (i, j))
    return img_new
