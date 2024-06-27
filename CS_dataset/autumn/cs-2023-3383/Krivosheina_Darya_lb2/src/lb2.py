from PIL import ImageDraw, ImageOps, Image
import numpy


def pentagram(img, x0, y0, x1, y1, thickness, color):
    color = tuple(color)
    coordinates = []
    drawing = ImageDraw.Draw(img)
    r = abs(x1 - x0) // 2
    drawing.ellipse((x0, y0, x1, y1), None, color, thickness)
    for i in range(5):
        phi = (numpy.pi / 5) * (2 * i + 3 / 2)
        node_i = (int(x0 + r + r * numpy.cos(phi)), int(y0 + r + r * numpy.sin(phi)))
        coordinates.append(node_i)
    for j in range(5):
        drawing.line((coordinates[j], coordinates[(j + 2) % 5]), color, thickness, None)
    return img


def invert(img, N, vertical):
    img_size = img.size
    width = img_size[0]
    height = img_size[1]
    flag = 0
    if vertical is True:
        if (width / N) == (width // N):
            count = width // N
            flag = 1
        else:
            count = (width // N) + 1
        for t in range(count):
            if t % 2 != 0:
                if flag == 0 and t == (count - 1):
                    img_new = img.crop((t * N, 0, width, height))
                    img_new = ImageOps.invert(img_new)
                    img.paste(img_new, (t * N, 0))
                    continue
                img_new = img.crop((t * N, 0, (t + 1) * N, height))
                img_new = ImageOps.invert(img_new)
                img.paste(img_new, (t * N, 0))
        return img
    else:
        if (height / N) == (height // N):
            count = height // N
            flag = 1
        else:
            count = (height // N) + 1
        for k in range(count):
            if k % 2 != 0:
                if flag == 0 and k == (count - 1):
                    img_new = img.crop((0, k * N, width, height))
                    img_new = ImageOps.invert(img_new)
                    img.paste(img_new, (0, k * N))
                    continue
                img_new = img.crop((0, k * N, width, (k + 1) * N))
                img_new = ImageOps.invert(img_new)
                img.paste(img_new, (0, k * N))
        return img


def mix(img, rules):
    img2 = img.copy()
    img_size = img.size
    width = img_size[0]
    length = width // 3
    images = []
    for w in range(3):
        y1 = w * length
        y2 = (w + 1) * length
        for w1 in range(3):
            x1 = w1 * length
            x2 = (w1 + 1) * length
            images.append((x1, y1, x2, y2))
    for p in range(9):
        placement = rules[p]
        img_part = img2.crop(images[placement])
        img.paste(img_part, (images[p][0], images[p][1]))
    return img
