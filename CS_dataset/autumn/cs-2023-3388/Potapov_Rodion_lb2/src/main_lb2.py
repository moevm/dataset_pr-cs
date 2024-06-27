import numpy as np
from PIL import Image, ImageDraw

def triangle(image, x0, y0, x1, y1, x2, y2, thickness, outline_color, fill_color):
    fill_color = tuple(fill_color) if fill_color is not None else None

    drawer = ImageDraw.Draw(image)
    drawer.polygon([(x0, y0), (x1, y1), (x2, y2)], fill_color, tuple(outline_color), thickness)
    return image

def change_color(image, new_color):
    new_color = tuple(new_color)
    pixels = list(image.getdata())

    color_count = {pixel_color: pixels.count(pixel_color) for pixel_color in set(pixels)}
    replacement_color = max(color_count, key=lambda x: color_count[x])
    new_pixels = [new_color if pixel == replacement_color else pixel for pixel in pixels]

    changed_color_image = image.copy()
    changed_color_image.putdata(new_pixels)
    return changed_color_image

def collage(image, num_rows, num_columns):
    width, height = image.size
    collage_image = Image.new("RGB", (width * num_columns, height * num_rows), 'red')

    for x in range(0, width * num_columns, width):
        for y in range(0, height * num_rows, height):
            collage_image.paste(image, (x, y))

    return collage_image