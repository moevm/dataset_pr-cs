from PIL import Image, ImageDraw
import numpy as np


def pentagram(img: Image.Image, x0, y0, x1, y1, thickness, color):
    draw = ImageDraw.Draw(img)
    draw.ellipse((x0, y0, x1, y1), width=thickness, outline=tuple(color))

    tx, ty = (x1 - x0) // 2, (y1 - y0) // 2
    vx, vy = x0 + tx, y0 + ty
    nodes = []
    for i in range(5):
        nodes.append(
            (
                int(tx * np.cos(np.pi * 4 / 5 * i - np.pi / 2) + vx),
                int(ty * np.sin(np.pi * 4 / 5 * i - np.pi / 2) + vy),
            )
        )
    nodes.append(nodes[0])
    draw.line(nodes, width=thickness, fill=tuple(color))
    return img


def invert(img: Image.Image, N, vertical):
    pixels = img.load()
    width, height = img.size
    for r in range(height):
        for c in range(width):
            if vertical:
                if (c // N) % 2:
                    pixels[c, r] = tuple(map(lambda x: 255 - x, pixels[c, r]))
            else:
                if (r // N) % 2:
                    pixels[c, r] = tuple(map(lambda x: 255 - x, pixels[c, r]))
    return img


def mix(img, rules):
    width, height = img.size
    width1 = width // 3
    height1 = height // 3
    resimg = Image.new('RGB', (width, height), '#0f0')
    for y in range(3):
        for x in range(3):
            src_n = rules[y * 3 + x]
            sy, sx = src_n // 3, src_n % 3
            resimg.paste(img.crop((width1 * sx, height1 * sy, width1 * (sx + 1), height1 * (sy + 1))),
                         (width1 * x, height1 * y, width1 * (x + 1), height1 * (y + 1)))
    return resimg