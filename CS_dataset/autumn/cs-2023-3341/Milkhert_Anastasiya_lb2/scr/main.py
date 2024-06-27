import numpy as np
from PIL import Image, ImageDraw


def swap(img, x0, y0, x1, y1, width):
    image_1 = img.crop((x0, y0, x0 + width, y0 + width))
    image_1 = image_1.rotate(270)
    image_2 = img.crop((x1, y1, x1 + width, y1 + width))
    image_2 = image_2.rotate(270)
    answer = img.copy()
    answer.paste(image_1, (x1, y1))
    answer.paste(image_2, (x0, y0))
    answer = answer.rotate(270)
    return answer


def get_pixel_color(img, x, y):
    width, height = img.size
    pixels = img.load()
    surrounding_pixels = []

    for i in range(-1, 2):
        for j in range(-1, 2):
            if ((x + i) >= 0) and ((x + i) < width):
                if ((y + j) >= 0) and ((y + j) < height):
                    surrounding_pixels.append(pixels[x + i, y + j])
    surrounding_pixels.remove(pixels[x, y])
    result_color = [0, 0, 0]

    for color in surrounding_pixels:
        for rgb in range(3):
            result_color[rgb] += color[rgb]

    for rgb in range(3):
        result_color[rgb] = int(result_color[rgb] / len(surrounding_pixels))

    return tuple(result_color)


def avg_color(img, x0, y0, x1, y1):
    img_resultt = img.copy()
    pixels = img_resultt.load()

    for x in range(x0, x1 + 1):
        for y in range(y0, y1 + 1):
            pixels[x, y] = get_pixel_color(img, x, y)

    return img_resultt


def pentagram(img, x, y, r, thickness, color):
    drawing = ImageDraw.Draw(img)
    all_lines = []
    drawing.ellipse(((x - r, y - r), (x + r, y + r)), fill=None, outline=tuple(color), width=thickness)
    for i in range(0, 5):
        node_i1 = (int(x + r * np.cos((np.pi / 5) * (2 * i + 3 / 2))), int(y + r * np.sin((np.pi / 5) * (2 * i + 3 / 2))))
        node_i2 = (int(x + r * np.cos((np.pi / 5) * (2 * (i + 2) + 3 / 2))), int(y + r * np.sin((np.pi / 5) * (2 * (i + 2) + 3 / 2))))

        all_lines.append([node_i1, node_i2])
    for el in all_lines:
        drawing.line((el[0], el[1]), tuple(color), thickness)
    return img


