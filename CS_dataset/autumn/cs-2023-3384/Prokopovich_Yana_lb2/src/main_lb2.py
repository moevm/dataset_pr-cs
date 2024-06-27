import math
from PIL import Image, ImageDraw


def pentagram(img, center_x, center_y, radius, thickness, colors):
    drawing = ImageDraw.Draw(img)
    coordinates = (center_x - radius, center_y - radius, center_x + radius, center_y + radius)
    drawing.ellipse(coordinates, outline=tuple(colors), width=thickness)
    nodes = []
    for i in range(5):
        phi = (math.pi / 5) * (2 * i + 3/2)
        node_i_x = int(center_x + radius * math.cos(phi))
        node_i_y = int(center_y + radius * math.sin(phi))
        nodes.append([node_i_x, node_i_y])
    for j in range(5):
        drawing.line((*nodes[j], *nodes[(j+2) % 5]), fill=tuple(colors), width=thickness)
    return img


def swap(img, x0, y0, x2, y2, width):
    img_new = img.copy()
    x1, y1 = x0 + width, y0 + width
    x3, y3 = x2 + width, y2 + width
    img1 = img_new.crop((x0, y0, x1, y1))
    img2 = img_new.crop((x2, y2, x3, y3))
    img1 = img1.rotate(270)
    img2 = img2.rotate(270)
    img_new.paste(img1, (x2, y2))
    img_new.paste(img2, (x0, y0))
    img_new = img_new.rotate(270)
    return img_new


def avg_color(img, x0, y0, x1, y1):
    img_new = img.copy()
    img_size_x, img_size_y = img_new.size
    for i in range(x0, x1+1):
        for j in range(y0, y1+1):
            r, g, b = 0, 0, 0
            amount = 0
            for x in range(max(0, i-1), min(img_size_x-1, i+2)):
                for y in range(max(0, j-1), min(img_size_y-1, j+2)):
                    if (x, y) != (i, j):
                        r_p, g_p, b_p = img.getpixel((x, y))
                        r += r_p
                        g += g_p
                        b += b_p
                        amount += 1
            new_color = (int(r/amount), int(g/amount), int(b/amount))
            img_new.putpixel((i, j), new_color)
    return img_new