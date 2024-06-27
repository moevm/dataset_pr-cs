from PIL import Image, ImageDraw
import numpy as np

def pentagram(img, x0, y0, x1, y1, thickness, color):
    color = tuple(color)
    radius = abs(x1 - x0) // 2
    center_x = x1 - (abs(x1 - x0) // 2)
    center_y = y1 - (abs(y1 - y0) // 2)
    drawing = ImageDraw.Draw(img)
    coordinates = ((x0, y0), (x1, y1))
    drawing.ellipse(coordinates, outline=color, width=thickness, fill=None)
    c = []
    for i in range(0, 6):
        phi = (np.pi/5)*(2*i+3/2)
        node_i = (int(center_x + radius*np.cos(phi)), int(center_y + radius*np.sin(phi)))
        c.append(node_i)
    c = [c[3], c[0], c[2], c[4], c[1], c[3]]
    drawing.line(c, color, thickness)
    return img


def invert(img, N, vertical):
    w, l = img.size
    pixels = img.load()
    if not vertical:
        for step in range(N, l, 2 * N):
            for x in range(w):
                for y in range(step, step + N):
                    if x < w and y < l:
                        r, g, b = pixels[x, y]
                        pixels[x, y] = 255 - r, 255 - g, 255 - b
    else:
        for step in range(N, w, 2 * N):
            for x in range(step, step + N):
                for y in range(l):
                    if x < w and y < l:
                        r, g, b = pixels[x, y]
                        pixels[x, y] = 255 - r, 255 - g, 255 - b
    return img

def mix(img, rules):
    w, l = img.size
    result = Image.new('RGB', (w, l), 'black')
    N = w // 3
    for i in rules:
        k = rules[i]
        x = (k % 3) * N
        y = k // 3 * N
        x1 = (k % 3) * N + N
        y1 = k // 3 * N + N
        img1 = img.crop((x, y, x1, y1))
        x2 = (i % 3) * N
        y2 = i // 3 * N
        result.paste(img1, (x2, y2))
    return result
