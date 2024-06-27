from PIL import Image, ImageDraw


# Задача 1
def triangle(img, x0, y0, x1, y1, x2, y2, thickness, color, fill_color):
    drawing = ImageDraw.Draw(img)
    coordinates = [(x0, y0), (x1, y1), (x2, y2)]

    if fill_color:
        drawing.polygon(coordinates, outline = tuple(color), fill = tuple(fill_color), width = thickness)
    else:
        drawing.polygon(coordinates, outline = tuple(color), fill = None, width = thickness)
    return img


# Задача 2
def change_color(img, color):
    image = img.copy()
    width, height = image.size
    colors_img = {}

    for x in range(width):
        for y in range(height):
            current_color = image.getpixel((x, y))
            if current_color in colors_img:
                colors_img[current_color] += 1
            else:
                colors_img[current_color] = 1

    max_count = max(colors_img.values())
    common_color = (0, 0, 0)

    for x in colors_img.keys():
        if colors_img[x] == max_count:
            common_color = x

    for x in range(width):
        for y in range(height):
            pixel_color = image.getpixel((x, y))
            if pixel_color == common_color:
                image.putpixel((x, y), tuple(color))

    return image


# Задача 3
def collage(img, N, M):
    width, height = img.size
    image = Image.new("RGB", (width * M, height * N), 'white')

    for x in range (M):
        for y in range (N):
            image.paste(img, (x * width, y * height))
    return image