import numpy as np       
from PIL import Image, ImageDraw


def swap(img, x0, y0, x1, y1, width):
    result_img = img.copy()
    result_img.paste(img.crop((x0, y0, x0+width, y0+width)).rotate(270), (x1, y1))
    result_img.paste(img.crop((x1, y1, x1 + width, y1 + width)).rotate(270), (x0, y0))
    return result_img.rotate(270)

def avg_color(img, x0, y0, x1, y1):
    result_img = img.copy()
    pixels = img.load()
    pixels_new = result_img.load()
    width, height = img.size

    x0_isborder = x0 == 0
    x1_isborder = x1 == height-1
    y0_isborder = y0 == 0
    y1_isborder = y1 == width-1

    if x0_isborder and x1_isborder:

        if y0_isborder:
            pixels_new[x0, y0] = tuple((np.array(pixels[x0 + 1, y0]) + np.array(pixels[x0, y0 + 1]) + np.array(pixels[x0 + 1, y0 + 1])) // 3)
            pixels_new[x1, y0] = tuple((np.array(pixels[x1-1, y0]) + np.array(pixels[x1, y0 + 1]) + np.array(pixels[x1-1, y0 + 1])) // 3)
        if y1_isborder:
            pixels_new[x0, y1] = tuple((np.array(pixels[x0+1, y1]) + np.array(pixels[x0, y1-1]) + np.array(pixels[x0+1, y1-1])) // 3)
            pixels_new[x1, y1] = tuple((np.array(pixels[x1-1, y1]) + np.array(pixels[x1, y1-1]) + np.array(pixels[x1-1, y1-1])) // 3)

        y0 += int(y0_isborder)
        y1 -= int(y1_isborder)
        for y in range(y0, y1+1):
            result1 = np.array(pixels[x0, y + 1]) + np.array(pixels[x0, y - 1])
            result2 = np.array(pixels[x1, y + 1]) + np.array(pixels[x1, y - 1])
            for i in range(3):
                result1 += np.array(pixels[x0 + 1, y + 1 - i])
                result2 += np.array(pixels[x1 - 1, y + 1 - i])
            result1 //= 5
            result2 //= 5
            pixels_new[x0, y] = tuple(result1)
            pixels_new[x1, y] = tuple(result2)
        y0 -= int(y0_isborder)
        y1 += int(y1_isborder)

    elif x0_isborder:

        if y0_isborder:
            pixels_new[x0, y0] = tuple((np.array(pixels[x0 + 1, y0]) + np.array(pixels[x0, y0 + 1]) + np.array(pixels[x0 + 1, y0 + 1])) // 3)
            pixels_new[x1, y0] = tuple((np.array(pixels[x1 - 1, y0]) + np.array(pixels[x1, y0 + 1]) + np.array(pixels[x1 - 1, y0 + 1])) // 3)
        if y1_isborder:
            pixels_new[x0, y1] = tuple((np.array(pixels[x0 + 1, y1]) + np.array(pixels[x0, y1 - 1]) + np.array(pixels[x0 + 1, y1 - 1])) // 3)
            pixels_new[x1, y1] = tuple((np.array(pixels[x1 - 1, y1]) + np.array(pixels[x1, y1 - 1]) + np.array(pixels[x1 - 1, y1 - 1])) // 3)

        y0 += int(y0_isborder)
        y1 -= int(y1_isborder)
        for y in range(y0, y1+1):
            result = np.array(pixels[x0, y + 1]) + np.array(pixels[x0, y - 1])
            for i in range(3):
                result += np.array(pixels[x0 + 1, y + 1 - i])
            result //= 5
            pixels_new[x0, y] = tuple(result)
        y0 -= int(y0_isborder)
        y1 += int(y1_isborder)

    elif x1_isborder:

        if y0_isborder:
            pixels_new[x0, y0] = tuple((np.array(pixels[x0 + 1, y0]) + np.array(pixels[x0, y0 + 1]) + np.array(pixels[x0 + 1, y0 + 1])) // 3)
            pixels_new[x1, y0] = tuple((np.array(pixels[x1 - 1, y0]) + np.array(pixels[x1, y0 + 1]) + np.array(pixels[x1 - 1, y0 + 1])) // 3)
        if y1_isborder:
            pixels_new[x0, y1] = tuple((np.array(pixels[x0 + 1, y1]) + np.array(pixels[x0, y1 - 1]) + np.array(pixels[x0 + 1, y1 - 1])) // 3)
            pixels_new[x1, y1] = tuple((np.array(pixels[x1 - 1, y1]) + np.array(pixels[x1, y1 - 1]) + np.array(pixels[x1 - 1, y1 - 1])) // 3)

        y0 += int(y0_isborder)
        y1 -= int(y1_isborder)
        for y in range(y0, y1+1):
            result = np.array(pixels[x1, y + 1]) + np.array(pixels[x1, y - 1])
            for i in range(3):
                result += np.array(pixels[x1 - 1, y + 1 - i])
            result //= 5
            pixels_new[x1, y] = tuple(result)
        y0 -= int(y0_isborder)
        y1 += int(y1_isborder)

    if y0_isborder and y1_isborder:

        x0 += int(x0_isborder)
        x1 -= int(x1_isborder)
        for x in range(x0, x1+1):
            result1 = np.array(pixels[x+1, y0]) + np.array(pixels[x-1, y0])
            result2 = np.array(pixels[x+1, y1]) + np.array(pixels[x-1, y1])
            for i in range(3):
                result1 += np.array(pixels[x+1-i, y0+1])
                result2 += np.array(pixels[x+1-i, y1-1])
            result1 //= 5
            result2 //= 5
            pixels_new[x, y0] = tuple(result1)
            pixels_new[x, y1] = tuple(result2)
        x0 -= int(x0_isborder)
        x1 += int(x1_isborder)

    elif y0_isborder:

        x0 += int(x0_isborder)
        x1 -= int(x1_isborder)
        for x in range(x0, x1+1):
            result = np.array(pixels[x + 1, y0]) + np.array(pixels[x - 1, y0])
            for i in range(3):
                result += np.array(pixels[x + 1 - i, y0 + 1])
            result //= 5
            pixels_new[x, y0] = tuple(result)
        x0 -= int(x0_isborder)
        x1 += int(x1_isborder)

    elif y1_isborder:
        x0 += int(x0_isborder)
        x1 -= int(x1_isborder)
        for x in range(x0, x1+1):
            result = np.array(pixels[x + 1, y1]) + np.array(pixels[x - 1, y1])
            for i in range(3):
                result += np.array(pixels[x + 1 - i, y1 - 1])
            result //= 5
            pixels_new[x, y1] = tuple(result)
        x0 -= int(x0_isborder)
        x1 += int(x1_isborder)

    x0 += int(x0_isborder)
    x1 -= int(x1_isborder)
    y0 += int(y0_isborder)
    y1 -= int(y1_isborder)
    for x in range(x0, x1+1):
        for y in range(y0, y1+1):
            result = np.array(pixels[x+1, y]) + np.array(pixels[x-1, y])
            for i in range(3):
                result += np.array(pixels[x+1-i, y+1]) + np.array(pixels[x+1-i, y-1])
            result //= 8
            pixels_new[x, y] = tuple(result)

    return result_img

def pentagram(img, x, y, r, thickness, color):
    color = tuple(color)
    coordinates = []
    for i in range(1, 7):
        phi = (np.pi/5)*(2*((1+i*3)%5)+3/2)
        coordinates.append((int(x + r * np.cos(phi)), int(y + r * np.sin(phi))))
    draw = ImageDraw.Draw(img)
    draw.ellipse(((x-r, y-r, x+r, y+r)), outline=color, width=thickness)
    draw.line(coordinates, fill=color, width=thickness)
    return img
