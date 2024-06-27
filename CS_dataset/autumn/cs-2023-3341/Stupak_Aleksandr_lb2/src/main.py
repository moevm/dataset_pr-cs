from PIL import ImageDraw, Image
import math


def swap(img, x0, y0, x1, y1, width):
    img2 = img.copy()
    im1 = img.crop((x0, y0, x0 + width, y0 + width))
    im2 = img.crop((x1, y1, x1 + width, y1 + width))
    im1 = im1.rotate(-90)
    im2 = im2.rotate(-90)
    img2.paste(im1, (x1, y1))
    img2.paste(im2, (x0, y0))
    img2 = img2.rotate(-90)
    return img2


def avg_color(img, x0, y0, x1, y1):
    img1 = img.copy()
    w, h = img1.size
    for x in range(x0, x1 + 1):
        for y in range(y0, y1 + 1):
            img1.putpixel((x, y), avg(img, x, y, w, h))
    return img1

    pass


def avg(img1, x, y, w, h):
    if ((x - 1 < 0) and (y - 1 < 0)):
        colors = [img1.getpixel((x, y + 1)), img1.getpixel((x + 1, y)), img1.getpixel((x + 1, y + 1))]
        answ = (int(sum(col[0] for col in colors) / 3),
                  int(sum(col[1] for col in colors) / 3),
                  int(sum(col[2] for col in colors) / 3))
    elif ((x + 1 > w) and (y - 1 < 0)):
        colors = [img1.getpixel((x - 1, y)), img1.getpixel((x - 1, y + 1)), img1.getpixel((x, y + 1))]
        answ = (int(sum(col[0] for col in colors) / 3),
                  int(sum(col[1] for col in colors) / 3),
                  int(sum(col[2] for col in colors) / 3))
    elif ((x - 1 < 0) and (y + 1 > h)):
        colors = [img1.getpixel((x, y - 1)), img1.getpixel((x + 1, y)), img1.getpixel((x + 1, y - 1))]
        answ = (int(sum(col[0] for col in colors) / 3),
                  int(sum(col[1] for col in colors) / 3),
                  int(sum(col[2] for col in colors) / 3))
    elif ((x + 1 > w) and (y + 1 > h)):
        colors = [img1.getpixel((x - 1, y)), img1.getpixel((x - 1, y - 1)), img1.getpixel((x, y - 1))]
        answ = (int(sum(col[0] for col in colors) / 3),
                  int(sum(col[1] for col in colors) / 3),
                  int(sum(col[2] for col in colors) / 3))
    elif (x - 1 < 0):
        colors = [img1.getpixel((x, y + 1)), img1.getpixel((x, y - 1)), img1.getpixel((x + 1, y)),
                  img1.getpixel((x + 1, y + 1)), img1.getpixel((x + 1, y - 1))]
        answ = (int(sum(col[0] for col in colors) / 5),
                  int(sum(col[1] for col in colors) / 5),
                  int(sum(col[2] for col in colors) / 5))
    elif (x + 1 > w):
        colors = [img1.getpixel((x, y + 1)), img1.getpixel((x, y - 1)), img1.getpixel((x - 1, y)),
                  img1.getpixel((x - 1, y + 1)), img1.getpixel((x - 1, y - 1))]
        answ = (int(sum(col[0] for col in colors) / 5),
                  int(sum(col[1] for col in colors) / 5),
                  int(sum(col[2] for col in colors) / 5))
    elif (y - 1 < 0):
        colors = [img1.getpixel((x, y + 1)), img1.getpixel((x + 1, y)), img1.getpixel((x + 1, y + 1)),
                  img1.getpixel((x - 1, y)), img1.getpixel((x - 1, y + 1))]
        answ = (int(sum(col[0] for col in colors) / 5),
                  int(sum(col[1] for col in colors) / 5),
                  int(sum(col[2] for col in colors) / 5))
    elif (y + 1 > h):
        colors = [img1.getpixel((x, y - 1)), img1.getpixel((x + 1, y)), img1.getpixel((x + 1, y - 1)),
                  img1.getpixel((x - 1, y)), img1.getpixel((x - 1, y - 1))]
        answ = (int(sum(col[0] for col in colors) / 5),
                  int(sum(col[1] for col in colors) / 5),
                  int(sum(col[2] for col in colors) / 5))
    else:
        colors = [img1.getpixel((x - 1, y - 1)), img1.getpixel((x, y - 1)), img1.getpixel((x + 1, y - 1)),
                  img1.getpixel((x - 1, y)), img1.getpixel((x + 1, y)), img1.getpixel((x - 1, y + 1)),
                  img1.getpixel((x, y + 1)), img1.getpixel((x + 1, y + 1))]
        answ = (int(sum(col[0] for col in colors) / 8),
                  int(sum(col[1] for col in colors) / 8),
                  int(sum(col[2] for col in colors) / 8))
    return answ


def pentagram(img, x, y, r, thickness, color):
    color = tuple(color)
    x1 = x - r
    y1 = y - r
    x2 = x + r
    y2 = y + r
    coordinates = ((x1, y1), (x2, y2))
    draw = ImageDraw.Draw(img)
    coor = []
    for i in range(5):
        phi = (math.pi / 5) * (2 * i + 3 / 2)
        node_i = (int(x + r * math.cos(phi)), int(y + r * math.sin(phi)))
        coor.append(node_i)
    draw.line((coor[0], coor[2]), color, thickness)
    draw.line((coor[2], coor[4]), color, thickness)
    draw.line((coor[4], coor[1]), color, thickness)
    draw.line((coor[1], coor[3]), color, thickness)
    draw.line((coor[3], coor[0]), color, thickness)
    draw.ellipse(coordinates, None, color, thickness)
    return img
