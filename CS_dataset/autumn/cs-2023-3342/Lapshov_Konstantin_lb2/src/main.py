from PIL import ImageDraw
import numpy as np


def pentagram(img, x, y, r, thickness, color):
    draw = ImageDraw.Draw(img)
    xy = [x - r, y - r, x + r, y + r]
    draw.ellipse(xy=xy, fill=None, outline=tuple(color), width=thickness)
    vertices = []
    for i in range(5):
        phi = (np.pi / 5) * (2 * i + 3 / 2)
        node_i = (int(x + r * np.cos(phi)), int(y + r * np.sin(phi)))
        vertices.append(node_i)
    for i in range(5):
        draw.line((vertices[i], vertices[(i + 2) % 5]), tuple(color), thickness)
    return img


def swap(img, x0, y0, x1, y1, width):
    img_copy = img.copy()

    piece_one = img.crop((x0, y0, x0 + width, y0 + width)).rotate(-90)
    piece_two = img.crop((x1, y1, x1 + width, y1 + width)).rotate(-90)

    img_copy.paste(piece_one, (x1, y1))
    img_copy.paste(piece_two, (x0, y0))

    img_copy = img_copy.rotate(-90)

    return img_copy


def avg_color(img, x0, y0, x1, y1):
    img_result = img.copy()
    img_arr = img_result.load()
    img_shape = img_result.size

    for x in range(x0, x1 + 1):
        for y in range(y0, y1 + 1):

            pix_ind = (
                (x - 1, y - 1), (x, y - 1), (x + 1, y - 1), (x + 1, y), (x + 1, y + 1), (x, y + 1), (x - 1, y + 1),
                (x - 1, y)
            )

            check = lambda xy: ((xy[0] >= 0) and (xy[0] < img_shape[0]) and (xy[1] >= 0) and (xy[1] < img_shape[1]))

            pix_ind = tuple(filter(check, pix_ind))
            pix = tuple(map(img.getpixel, ((i[0], i[1]) for i in pix_ind)))

            R, G, B = 0, 0, 0

            for i in range(len(pix)):
                R += pix[i][0]
                G += pix[i][1]
                B += pix[i][2]
            result_color = tuple((R // len(pix), G // len(pix), B // len(pix)))
            img_arr[x, y] = result_color

    return img_result