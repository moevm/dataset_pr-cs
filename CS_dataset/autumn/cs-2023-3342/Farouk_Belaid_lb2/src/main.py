import numpy as np
from PIL import ImageDraw


def pentagram(img, x, y, r, thickness, color):
    draw = ImageDraw.Draw(img)
    xy = [x - r, y - r, x + r, y + r]
    draw.ellipse(xy=xy, fill=None, outline=tuple(color), width=thickness)
    verts = []
    for i in range(5):
        phi = (np.pi / 5) * (2 * i + 3 / 2)
        node_i = (int(x + r * np.cos(phi)), int(y + r * np.sin(phi)))
        verts.append(node_i)
    for i in range(5):
        draw.line((verts[i], verts[(i + 2) % 5]), tuple(color), thickness)
    return img


def swap(img, x0, y0, x1, y1, width):
    copy_img = img.copy()

    first_pic = img.crop((x0, y0, x0 + width, y0 + width)).rotate(-90)
    second_pic = img.crop((x1, y1, x1 + width, y1 + width)).rotate(-90)

    copy_img.paste(first_pic, (x1, y1))
    copy_img.paste(second_pic, (x0, y0))

    copy_img = copy_img.rotate(-90)

    return copy_img


def avg_color(img, x0, y0, x1, y1):
    result_img = img.copy()
    img_arr = result_img.load()
    shape_img = result_img.size

    for x in range(x0, x1 + 1):
        for y in range(y0, y1 + 1):

            pix_ind = (
                (x - 1, y - 1), (x, y - 1), (x + 1, y - 1), (x + 1, y), (x + 1, y + 1), (x, y + 1), (x - 1, y + 1),
                (x - 1, y)
            )

            check = lambda xy: ((xy[0] >= 0) and (xy[0] < shape_img[0]) and (xy[1] >= 0) and (xy[1] < shape_img[1]))

            pix_ind = tuple(filter(check, pix_ind))
            pix = tuple(map(img.getpixel, ((i[0], i[1]) for i in pix_ind)))

            R, G, B = 0, 0, 0

            for i in range(len(pix)):
                R += pix[i][0]
                G += pix[i][1]
                B += pix[i][2]
            res_color = tuple((R // len(pix), G // len(pix), B // len(pix)))
            img_arr[x, y] = res_color

    return result_img