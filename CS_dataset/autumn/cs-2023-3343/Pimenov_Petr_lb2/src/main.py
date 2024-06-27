from PIL import Image, ImageDraw


# Задача 1
def triangle(img, x0, y0, x1, y1, x2, y2, thickness, color, fill_color):
    drawing = ImageDraw.Draw(img)
    if fill_color is not None:
        fill_color = tuple(fill_color)
    drawing.polygon([x0, y0, x1, y1, x2, y2], fill_color, tuple(color), thickness)
    return img


# Задача 2
def change_color(img, color):
    colors = {}
    width, height = img.size
    for i in range(width):
        for j in range(height):
            pixel = img.getpixel((i, j))
            colors.update({pixel: colors.get(pixel, 0) + 1})
    target = max(colors, key=colors.get)
    changed = Image.new('RGB', img.size)
    for x in range(width):
        for y in range(height):
            pixel = img.getpixel((x, y))
            if pixel == target:
                changed.putpixel((x, y), tuple(color))
            else:
                changed.putpixel((x, y), pixel)
    return changed


# Задача 3
def collage(img, N, M):  # M - по X, N - по Y
    img_width = img.size[0]
    img_height = img.size[1]
    collage = Image.new('RGB', (img_width * M, img_height * N))
    for i in range(M):
        for j in range(N):
            collage.paste(img, (img_width * i, img_height * j))
    return collage
