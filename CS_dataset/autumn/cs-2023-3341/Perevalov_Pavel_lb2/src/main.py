import PIL
from PIL import Image, ImageDraw, ImageOps
from math import cos, sin, pi

def calculate_center(x0, x1, y0, y1):
    x_c = x1 - (abs(x1 - x0) // 2)
    y_c = y1 - (abs(y1 - y0) // 2)
    return x_c, y_c

def pentagram(img, x0, y0, x1, y1, thickness, color):
    drawing = ImageDraw.Draw(img)

    r = abs(x1 - x0) // 2
    x_c, y_c = calculate_center(x0, x1, y0, y1)
    posts = []
    for i in range(5):
        phi = (pi / 5) * (2 * i + 3 / 2)
        post_i = (int(x_c + r * cos(phi)), int(y_c + r * sin(phi)))
        posts.append(post_i)

    drawing.ellipse((x0, y0, x1, y1), outline=tuple(color), width=thickness)

    for i in range(5):
        drawing.line([posts[i], posts[(i + 2) % 5]], fill=tuple(color), width=thickness)

    return img

def invert(img, N, vertical):
    width, height = img.size
    w = width//N + 1
    h = height//N + 1
    if (vertical):
        for i in range(1, w, 2):
            inv_color = img.crop((i*N, 0, (i+1)*N, height))
            inv_color = ImageOps.invert(inv_color)
            img.paste(inv_color, (i*N, 0))
    else:
         for f in range(1, h, 2):
             inv_color = img.crop((0, f*N, width, (f+1)*N))
             inv_color = ImageOps.invert(inv_color)
             img.paste(inv_color, (0, f*N))
    return img


def mix(img, rules):
    width, height = img.size
    w = width // 3
    h = height // 3
    bob = []
    for f in range(3):
        for i in range(3):
            a = ((i * h, f * w, (i + 1) * h, (f + 1) * w))
            piece = img.crop(a)
            bob.append([piece, (i * h, f * w)])
    for i in rules:
        img.paste(bob[rules[i]][0], bob[i][1])
    return img
