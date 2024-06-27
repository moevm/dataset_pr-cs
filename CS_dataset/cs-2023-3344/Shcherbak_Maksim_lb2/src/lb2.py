from PIL import Image, ImageDraw
# Задача 1
def triangle(img, x0, y0, x1, y1, x2, y2, thickness, color, fill_color):
    draw = ImageDraw.Draw(img)
    cord = ((x0, y0), (x1, y1), (x2, y2))
    if fill_color is not None:
        draw.polygon(cord, fill=tuple(fill_color), outline=tuple(color), width=thickness)
    else:
        draw.polygon(cord, outline=tuple(color), width=thickness)
    return img

# Задача 2
def change_color(img, color):
    img_copy = img.copy()
    x_size, y_size = img.size
    cveta = {}

    for x in range(x_size):
        for y in range(y_size):
            pixcolor = img.getpixel((x, y))
            if pixcolor not in cveta:
                cveta[pixcolor] = 0
            cveta[pixcolor] += 1

    mas = max(cveta.values())
    color_name = ''

    for i in cveta:
        if cveta[i] == mas:
            color_name = i

    for x in range(x_size):
        for y in range(y_size):
            if img.getpixel((x, y)) == color_name:
                img_copy.putpixel((x, y), tuple(color))

    return img_copy

# Задача 3
def collage(img, N, M):
    width, height = img.size
    new_img = Image.new("RGB", (width * M, height * N))

    for i in range(M):
        for j in range(N):
            new_img.paste(img, (width * i, height * j))

    return new_img

