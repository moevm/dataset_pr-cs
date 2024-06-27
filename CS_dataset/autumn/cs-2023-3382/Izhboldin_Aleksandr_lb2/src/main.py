from PIL import Image, ImageDraw, ImageOps
from typing import Union
import numpy as np 
import math


def pentagram(img: Image.Image, x0: int, y0: int, x1: int, y1: int, thickness: int, line_color: Union[tuple, list]) -> Image.Image:
    draw = ImageDraw.Draw(img, "RGB")
    coords = []

    line_color = tuple(line_color)

    radius = abs(x1 - x0) // 2
    x_center = x1 - (abs(x1 - x0) // 2)
    y_center = y1 - (abs(y1 - y0) // 2)

    draw.ellipse(((x0, y0), (x1, y1)), outline = line_color, width = thickness)

    for i in range(5):
        phi = (np.pi / 5) * (2 * i + 3/2)
        node_i = (int(x_center + radius * np.cos(phi)), int(y_center + radius * np.sin(phi)))
        coords.append(node_i)

    for i in range(5):
        draw.line((coords[i],coords[(i + 2) % 5]), fill = line_color, width = thickness)

    return img


def invert(img: Image.Image, line_width: int, line_type: bool) -> Image.Image:
    if line_type:
        for line_number in range(math.ceil(img.width / line_width)):
            if line_number % 2 != 0:
                coords = (line_width * line_number, 0, line_width * (line_number + 1), img.height)
                crop = img.crop(coords)
                crop = ImageOps.invert(crop)
                img.paste(crop, coords)
    else:
        for line_number in range(math.ceil(img.height / line_width)):
            if line_number % 2 != 0:
                coords = (0, line_width * line_number, img.width, line_width * (line_number + 1))
                crop = img.crop(coords)
                crop = ImageOps.invert(crop)
                img.paste(crop, coords)
    
    return img

    
def mix(img: Image.Image, rules: dict) -> Image.Image:
    new_img = Image.new("RGB", (img.size[0], img.size[1]))
    side_size = img.size[0] // 3 
    crops = []

    for line in range(img.size[1] // side_size):
        for column in range(img.size[0] // side_size):
            coords = (column * side_size, line * side_size, (column + 1) * side_size, (line + 1) * side_size)
            crops.append(img.crop(coords))
    
    for new_position, crop in rules.items():
        new_img.paste(crops[crop],
                      ((new_position % 3) * side_size, (new_position // 3) * side_size))

    return new_img
