import numpy as np
from PIL import Image, ImageDraw

def swap(img, x0,y0,x1,y1,width):
    part1 = img.copy().crop((x0, y0, x0 + width, y0 + width)).rotate(-90)
    part2 = img.copy().crop((x1, y1, x1 + width, y1 + width)).rotate(-90)
    res = img.copy()
    res.paste(part2, (x0, y0))
    res.paste(part1,(x1,y1))
    return res.rotate(-90)
 
def avg_color(img, x0, y0, x1, y1):
    res = img.copy()
    size = img.size
    for x in range(x0, x1 + 1):
        for y in range(y0, y1 + 1):
            sum_rgb = [0, 0, 0]
            pixels_around = ((x + 1, y - 1), (x + 1, y), (x + 1, y + 1), (x, y - 1),(x, y + 1), (x - 1, y - 1), (x - 1, y), (x - 1, y + 1))
            pixels_around = tuple(filter(lambda c: (0 <= c[0] <= size[0] - 1) and (0 <= c[1] <= size[1] - 1), pixels_around))
            for i in pixels_around:
                pixel = img.getpixel(i)
                for j in range(3):
                    sum_rgb[j] += pixel[j]
            length = len(pixels_around)
            averange_color = (int(sum_rgb[0] / length), int(sum_rgb[1] / length), int(sum_rgb[2] / length))
            res.putpixel((x, y), averange_color)
    return res


def pentagram(img, x, y, r, thickness, color):
    draw = ImageDraw.Draw(img, "RGB")
    x1 = x - r
    x2 = x + r
    y1 = y - r
    y2 = y + r
    draw.ellipse(((x1, y1), (x2, y2)),fill = None, width = thickness,outline= tuple(color))
    coord = []
    for i in range(5):
        phi = (np.pi / 5) * (2 * i + 3 / 2)
        node_i = (int(x + r * np.cos(phi)), int(y + r * np.sin(phi)))
        coord.append((node_i))
    coord = tuple(coord)
    for i in range(5):
        draw.line((coord[i],coord[(i + 2) % 5]),fill = tuple(color),width= thickness)
    return img
