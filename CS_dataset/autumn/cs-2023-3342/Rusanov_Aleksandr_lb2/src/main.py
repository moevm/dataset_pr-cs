import PIL
from PIL import Image, ImageDraw
from numpy import pi, sin, cos


def swap(img, x0, y0, x1, y1, width):
    img_res = img.copy()
    part_1 = img_res.crop((x0, y0, x0 + width, y0 + width)).rotate(-90)
    part_2 = img_res.crop((x1, y1, x1 + width, y1 + width)).rotate(-90)
    img_res.paste(part_1, (x1, y1))
    img_res.paste(part_2, (x0, y0))
    img_res = img_res.rotate(-90)
    return img_res


def avg_color(img, x0, y0, x1, y1):
    result_img = img.copy()

    width, height = img.size

    for y in range(y0, y1 + 1):
        for x in range(x0, x1 + 1):

            r_values = []
            g_values = []
            b_values = []

            if x > 0:
                r, g, b = img.getpixel((x - 1, y))
                r_values.append(r)
                g_values.append(g)
                b_values.append(b)
                if y > 0:
                    r, g, b = img.getpixel((x - 1, y - 1))
                    r_values.append(r)
                    g_values.append(g)
                    b_values.append(b)
                if y < height - 1:
                    r, g, b = img.getpixel((x - 1, y + 1))
                    r_values.append(r)
                    g_values.append(g)
                    b_values.append(b)

            if x < width - 1:
                r, g, b = img.getpixel((x + 1, y))
                r_values.append(r)
                g_values.append(g)
                b_values.append(b)
                if y > 0:
                    r, g, b = img.getpixel((x + 1, y - 1))
                    r_values.append(r)
                    g_values.append(g)
                    b_values.append(b)
                if y < height - 1:
                    r, g, b = img.getpixel((x + 1, y + 1))
                    r_values.append(r)
                    g_values.append(g)
                    b_values.append(b)

            if y > 0:
                r, g, b = img.getpixel((x, y - 1))
                r_values.append(r)
                g_values.append(g)
                b_values.append(b)

            if y < height - 1:
                r, g, b = img.getpixel((x, y + 1))
                r_values.append(r)
                g_values.append(g)
                b_values.append(b)

            avg_r = int(sum(r_values) / len(r_values))
            avg_g = int(sum(g_values) / len(g_values))
            avg_b = int(sum(b_values) / len(b_values))

            result_img.putpixel((x, y), (avg_r, avg_g, avg_b))

    return result_img


def pentagram(img, x, y, r, thickness, color):
    drawing = ImageDraw.Draw(img)
    xy = [x - r, y - r, x + r, y + r]
    drawing.ellipse(xy, None, tuple(color), thickness)
    for i in range(5):
        phi = (pi / 5) * (2 * i + 3 / 2)
        x_0 = int(x + r * cos(phi))
        y_0 = int(y + r * sin(phi))
        end_of_line = (pi / 5) * (2 * (i + 2) + 3 / 2)
        x_1 = int(x + r * cos(end_of_line))
        y_1 = int(y + r * sin(end_of_line))
        coordinates = [(x_0, y_0), (x_1, y_1)]
        drawing.line(tuple(coordinates), tuple(color), thickness)
    return img
