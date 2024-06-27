from PIL import ImageDraw
import numpy as np

def pentagram(img, x0, y0, x1, y1, thickness, color):
    radius = abs(x1 - x0) // 2
    x = x0 + (abs(x1 - x0) // 2)
    y = y0 + (abs(y1 - y0) // 2)
    coordinates = []
    for i in range(5):
        phi = (np.pi/5)*(2*i+3/2)
        coordinates.append((int(x+radius*np.cos(phi)),int(y+radius*np.sin(phi))))
    drawing = ImageDraw.Draw(img)
    drawing.ellipse(((x0, y0, x1, y1)), None, tuple(color), thickness)
    for i in range(5):
        drawing.line((coordinates[i], coordinates[(i + 2)% 5]), tuple(color), thickness)
    return img


def invert(img, N,vertical):
    width, height = img.size
    pixels = img.load()
    if vertical:
        for x in range(0, width):
            if ((x // N) % 2) == 1:
                for y in range(height):
                    px_color = img.getpixel((x,y))
                    inv_color = tuple(255 - color for color in px_color)
                    pixels[x, y] = inv_color
    else:
        for y in range(0, height):
            if ((y // N) % 2) == 1:
                for x in range(width):
                    px_color = img.getpixel((x,y))
                    inv_color = tuple(255 - color for color in px_color)
                    pixels[x, y] = inv_color

    return img
    
def mix(img, rules):
    width, height = img.size
    new_img = img.copy()
    delim = width // 3
    image_parts = [None] * 9

    for i in range(3):
        for j in range(3):
            image_parts[i * 3 + j] = img.crop((j * delim, i * delim, (j + 1) * delim, (i + 1) * delim))

    coordinates = []
    for i in range(3):
        for j in range(3):
            coordinates += [tuple((j * delim, i * delim))]

    for key in rules:
        new_img.paste(image_parts[rules[key]], coordinates[key])
    return new_img