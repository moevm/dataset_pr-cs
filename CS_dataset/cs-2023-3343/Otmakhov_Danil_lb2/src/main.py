from PIL import Image, ImageDraw
from math import pi, sin, cos


def pentagram(img, x, y, r, thickness, color):
    drawing = ImageDraw.Draw(img)
    vertices = []
    for i in range(5):
        phi = (pi / 5) * (2 * i + 3 / 2)
        node_i = (int(x + r * cos(phi)), int(y + r * sin(phi)))
        vertices.append(node_i)
    for i in range(5):
        node1 = vertices[i]
        node2 = vertices[(i + 2) % 5]
        drawing.line([node1, node2], tuple(color), thickness)
    drawing.ellipse([(x - r, y - r), (x + r, y + r)], None, tuple(color), thickness)
    return img


def swap(img, x0, y0, x1, y1, width):
    new_img = img.copy()
    cropped_img1 = img.crop((x0, y0, x0 + width, y0 + width))
    cropped_img2 = img.crop((x1, y1, x1 + width, y1 + width))
    new_img.paste(cropped_img1.transpose(Image.Transpose.ROTATE_270), (x1, y1))
    new_img.paste(cropped_img2.transpose(Image.Transpose.ROTATE_270), (x0, y0))
    new_img = new_img.transpose(Image.Transpose.ROTATE_270)
    return new_img


def avg_color(img, x0, y0, x1, y1):
    new_img = img.copy()
    for x in range(x0, x1 + 1):
        for y in range(y0, y1 + 1):
            neighbors = [img.getpixel((x - 1, y)), img.getpixel((x - 1, y - 1)),
                         img.getpixel((x, y - 1)), img.getpixel((x + 1, y - 1)),
                         img.getpixel((x + 1, y)), img.getpixel((x + 1, y + 1)),
                         img.getpixel((x, y + 1)), img.getpixel((x - 1, y + 1))]
            new_color = (int(sum(neighbor[0] for neighbor in neighbors) / len(neighbors)),
                         int(sum(neighbor[1] for neighbor in neighbors) / len(neighbors)),
                         int(sum(neighbor[2] for neighbor in neighbors) / len(neighbors)))
            new_img.putpixel((x, y), new_color)
    return new_img
