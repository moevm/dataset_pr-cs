import numpy as np
from PIL import Image, ImageDraw
# Задача 1
def triangle(img, x0, y0, x1, y1, x2, y2, thickness, color, fill_color=None):
    draw = ImageDraw.Draw(img)
    points = [(x0, y0), (x1, y1), (x2, y2)]
    draw.polygon(points,outline=tuple(color), width=thickness,fill=tuple(fill_color) if fill_color else None)

    return img

# Задача 2
def change_color(img, color):
    img_array = np.array(img)
    unique_colors, counts = np.unique(img_array.reshape(-1, 3), return_counts=True, axis=0)
    most_frequent_color = unique_colors[np.argmax(counts)]
    img_array[np.all(img_array == most_frequent_color, axis=-1)] = color
    new_img = Image.fromarray(img_array)

    return new_img

# Задача 3
def collage(img, N, M):
    width, height = img.size
    collage_img = Image.new('RGB', (M * width, N * height))

    for y in range(N):
        for x in range(M):
            collage_img.paste(img, (x * width, y * height))

    return collage_img