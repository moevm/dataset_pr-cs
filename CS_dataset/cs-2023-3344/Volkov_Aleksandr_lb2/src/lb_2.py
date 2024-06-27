from PIL import Image, ImageDraw
import numpy as np


def swap(img, x0, y0, x1, y1, width):
    img_copy = img.copy()
    first = img_copy.crop((x0, y0, x0 + width, y0 + width)).transpose(Image.Transpose.ROTATE_270)
    second = img_copy.crop((x1, y1, x1 + width, y1 + width)).transpose(Image.Transpose.ROTATE_270)
    img_copy.paste(first, (x1, y1))
    img_copy.paste(second, (x0, y0))
    img_copy = img_copy.transpose(Image.Transpose.ROTATE_270)
    return img_copy


def avg_color(img, x0, y0, x1, y1):
    img_copy = img.copy()
    size = img.size
    for x in range(x0, x1 + 1):
        for y in range(y0, y1 + 1):
            neighbor_pixels = (
                (x, y + 1),
                (x, y - 1),
                (x + 1, y),
                (x - 1, y),
                (x + 1, y + 1),
                (x + 1, y - 1),
                (x - 1, y - 1),
                (x - 1, y + 1),
            )
            neighbor_pixels = tuple(
                filter(lambda n: (0 <= n[0] <= size[0] - 1) and (0 <= n[1] <= size[1] - 1),neighbor_pixels))
            len_neighbor_pixels = len(neighbor_pixels)

            rgb = [0, 0, 0]
            for i in neighbor_pixels:
                pixel_color = img.getpixel(i)
                rgb[0] += pixel_color[0]
                rgb[1] += pixel_color[1]
                rgb[2] += pixel_color[2]
            new_color = (
                int(rgb[0] / len_neighbor_pixels),
                int(rgb[1] / len_neighbor_pixels),
                int(rgb[2] / len_neighbor_pixels),
            )
            img_copy.putpixel((x, y), new_color)
    return img_copy


def pentagram(img, x, y, r, thickness, color):
    drawing = ImageDraw.Draw(img)
    color = tuple(color)
    coordinates = ((x - r, y - r), (x + r, y + r))
    drawing.ellipse(coordinates, outline=color, width=thickness)
    nodes = []
    for i in range(5):
        phi = (np.pi / 5) * (2 * i + 3 / 2)
        node_i = (int(x + r * np.cos(phi)), int(y + r * np.sin(phi)))
        nodes.append(node_i)
    for i in range(5):
        drawing.line((nodes[i], nodes[(i + 2) % 5]), fill=color, width=thickness)
    return img
