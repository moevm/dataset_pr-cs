from PIL import Image, ImageDraw


# Задача 1
def triangle(img, x0, y0, x1, y1, x2, y2, thickness, color, fill_color):
    if fill_color:
        fill_color = tuple(fill_color)
    drawing = ImageDraw.Draw(img)
    drawing.polygon((x0, y0, x1, y1, x2, y2), fill_color, tuple(color), thickness)
    return img

# Задача 2
def change_color(img, color):
    color = tuple(color)
    d = {}
    for i in range(img.size[0]):
        for j in range(img.size[1]):
            curr = tuple(img.getpixel((i, j)))
            d[curr] = d.get(curr, 0) + 1
    max_elem = (0, 0, 0)
    maxx = 0
    for k, v in d.items():
        if v > maxx:
            maxx = v
            max_elem = k
    new_img = Image.new('RGB', (img.size[0], img.size[1]), (0, 0, 0))
    for i in range(img.size[0]):
        for j in range(img.size[1]):
            if img.getpixel((i, j)) == max_elem:
                new_img.putpixel((i, j), color)
            else:
                new_img.putpixel((i, j), img.getpixel((i, j)))
    return new_img

# Задача 3
def collage(img, N, M):
    new_img = Image.new('RGB', (img.size[0] * M, img.size[1] * N), (0, 0, 0))
    for i in range(M):
        for j in range(N):
            new_img.paste(img, (img.size[0] * i, img.size[1] * j))
    return new_img