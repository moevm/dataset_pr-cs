from PIL import Image, ImageDraw
from numpy import pi, cos, sin
import numpy as np
def check_pixel_position(x, y, width, heigth):
    return (x>=0 and x < width and y>=0 and y < heigth)

def swap(img, x0,y0,x1,y1,width):
    copy_img = img.copy()
    first_img = copy_img.crop((x0, y0, x0+width, y0+width))
    second_img = copy_img.crop((x1, y1, x1+width, y1+width))
    first_img = first_img.rotate(-90)
    second_img = second_img.rotate(-90)
    copy_img.paste(first_img, (x1, y1))
    copy_img.paste(second_img, (x0, y0))
    copy_img = copy_img.rotate(-90)
    return copy_img

def avg_color(img, x0,y0,x1,y1):
    copy_img = img.copy()
    width = img.size[0]
    heigth = img.size[1]
    for i in range(x0, min(x1 + 1, img.size[0])):
        for j in range(y0, min(y1 + 1, img.size[1])):
            new_color = np.array([0, 0, 0])
            count = 0
            for new_i in range(-1, 2):
                for new_j in range(-1, 2):
                    if not(new_i == 0 and new_j == 0) and check_pixel_position(i + new_i, j + new_j, width, heigth):
                        pixel_color = np.array(img.getpixel((i + new_i, j + new_j)))
                        count +=1
                        new_color += pixel_color
                result_color = new_color // count
            copy_img.putpixel((i, j), tuple(result_color))
    return copy_img

def pentagram(img, x, y, r, thickness, color):
    drawing = ImageDraw.Draw(img, "RGB")
    coordinates = ((x - r, y - r), (x + r, y + r))
    drawing.ellipse(coordinates, fill=None, width=thickness, outline=tuple(color))
    array_node = []
    for i in range(5):
        phi = (pi / 5) * (2 * i + 3 / 2)
        array_node.append((int(x + r * cos(phi)), int(y + r * sin(phi))))
    for i in range(5):
        drawing.line((array_node[i], array_node[(i + 2) % 5]), fill = tuple(color), width = thickness)
    return img