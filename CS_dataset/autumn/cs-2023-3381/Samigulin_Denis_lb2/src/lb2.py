import numpy as np
from PIL import Image, ImageDraw


def pentagram(img: Image.Image, x0, y0, x1, y1, thickness, color):
    draw = ImageDraw.Draw(img)
    draw.ellipse((x0, y0, x1, y1), width=thickness, outline=tuple(color))

    rx, ry = (x1 - x0) // 2, (y1 - y0) // 2
    cx, cy = x0 + rx, y0 + ry
    n = []
    for i in range(5):
        n.append(
            (
                int(rx * np.cos(np.pi * 4 / 5 * i - np.pi / 2) + cx),
                int(ry * np.sin(np.pi * 4 / 5 * i - np.pi / 2) + cy),
            )
        )
    n.append(n[0])
    draw.line(n, width=thickness, fill=tuple(color))
    return img

def invert(img: Image.Image, N, vertical):
    pixels = img.load()
    w, h = img.size
    for r in range(h):
        for c in range(w):
            if vertical:
                if (c // N) % 2:
                    pixels[c, r] = tuple(map(lambda x: 255 - x, pixels[c, r]))
            else:
                if (r // N) % 2:
                    pixels[c, r] = tuple(map(lambda x: 255 - x, pixels[c, r]))
    return img


def mix(img, rules):
    w, h = img.size
    w1 = w // 3
    h1 = h // 3
    resimg = Image.new('RGB', (w, h), '#0f0')
    for y in range(3):
        for x in range(3):
            src_n = rules[y * 3 + x]
            sy, sx = src_n // 3, src_n % 3
            resimg.paste(img.crop((w1 * sx, h1 * sy, w1 * (sx + 1), h1 * (sy + 1))),
                         (w1 * x, h1 * y, w1 * (x + 1), h1 * (y + 1)))
    return resimg