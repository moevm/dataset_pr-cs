import numpy as np
from PIL import Image, ImageDraw


def swap(img, x0, y0, x1, y1, width):
    img1 = img.copy()
    square1 = img1.crop((x0, y0, x0 + width, y0 + width))
    square2 = img1.crop((x1, y1, x1 + width, y1 + width))
    square1 = square1.rotate(270)
    square2 = square2.rotate(270)
    img1.paste(square1, (x1, y1))
    img1.paste(square2, (x0, y0))
    img1 = img1.rotate(270)
    return img1


def avg_color(img, x0, y0, x1, y1):
    width, height = img.size

    spisok = [(-1, -1), (-1, 0), (-1, 1), (0, -1),
              (0, 1), (1, -1), (1, 0), (1, 1)]

    def within_image_bounds(x, y):
        return (0 <= x < width) and (0 <= y < height)

    updated_image = img.copy()
    for x in range(x0, x1 + 1):
        for y in range(y0, y1 + 1):
            pixels_to_average = [img.getpixel((x + dx, y + dy)) for dx, dy in spisok if
                                 within_image_bounds(x + dx, y + dy)]
            avg_colour = tuple(int(sum(c) / len(pixels_to_average)) for c in zip(*pixels_to_average))
            updated_image.putpixel((x, y), avg_colour)

    return updated_image


def pentagram(img, x, y, r, thickness, color):
    draw = ImageDraw.Draw(img, "RGB")

    x1, y1, x2, y2 = x - r, y - r, x + r, y + r
    draw.ellipse([x1, y1, x2, y2], None, (color[0], color[1], color[2]), thickness)

    for i in range(5):
        angle1 = (np.pi / 5) * (2 * i + 3 / 2)
        nodeX1 = int(x + r * np.cos(angle1))
        nodeY1 = int(y + r * np.sin(angle1))

        angle2 = (np.pi / 5) * (2 * (i + 2) + 3 / 2)
        nodeX2 = int(x + r * np.cos(angle2))
        nodeY2 = int(y + r * np.sin(angle2))

        draw.line([(nodeX1, nodeY1), (nodeX2, nodeY2)], (color[0], color[1], color[2]), thickness)

    return img

