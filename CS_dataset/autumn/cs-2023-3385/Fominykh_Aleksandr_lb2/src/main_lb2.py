from PIL import Image, ImageDraw

# Задача 1
def triangle(img, x0, y0, x1, y1, x2, y2, thickness, color, fill_color):
    if fill_color is not None:
        fill_color = tuple(fill_color)
    drawing = ImageDraw.Draw(img)
    drawing.polygon((x0, y0, x1, y1, x2, y2), fill=fill_color, outline=tuple(color), width=thickness)
    return img

# Задача 2
def change_color(img, color):
    pixel_colors = {}
    width, height = img.size
    pixels = img.load()
    for i in range(width):
        for j in range(height):
            pixel_color = str(pixels[i, j])
            if pixel_color not in pixel_colors:
                pixel_colors[pixel_color] = 1
            else:
                pixel_colors[pixel_color] += 1
    the_most_common_color_val_key = max(pixel_colors, key=pixel_colors.get)
    for i in range(width):
        for j in range(height):
            if str(pixels[i, j]) == the_most_common_color_val_key:
                pixels[i, j] = tuple(color)
    return img

# Задача 3
def collage(img, N, M):
    img_width, img_height = img.size
    new_img_width, new_img_height = img_width * M, img_height * N
    new_img = Image.new("RGB", (new_img_width, new_img_height), (0, 0, 0))
    coordinates = []
    for i in range(M):
        for j in range(N):
            coordinates.append((i * img_width, j * img_height))
    for k in range(M * N):
        new_img.paste(img, coordinates[k])
    return new_img

