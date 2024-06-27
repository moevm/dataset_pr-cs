import PIL
import numpy as np
from PIL import Image, ImageDraw, ImageOps

def take_center_x(x0):
    center_x = x0 + int((x1 - x0) / 2)
    return center_x

def take_center_y(y0):
    center_y = y0 + int((y1 - y0) / 2)
    return center_y

def pentagram(img, x0, y0, x1, y1, thickness, color):
    center_x = take_center_x(x0)
    center_y = take_center_y(y0)
    r = int((x1 - x0) / 2)
    
    drawing = ImageDraw.Draw(img)
    drawing.ellipse((x0, y0, x1, y1), fill = None, outline = tuple(color), width=thickness)

    points=()
    pentagram_coordinate=[0, 2, 4, 1, 3, 0]
    for i in pentagram_coordinate:
        angle = (np.pi/5)*(2*i+3/2)
        points_i = (int(center_x + r * np.cos(angle)), int(center_y + r * np.sin(angle)))
        points = points + (points_i,)
    drawing.line(points, fill = tuple(color), width = thickness)    
    return img

def invert(img, N, vertical):
    inv_img = ImageOps.invert(img)
    width, height = img.size
    if vertical: 
        for i in range(N, width, 2*N):
            strip = inv_img.crop((i, 0, i+N, height))
            img.paste(strip, (i, 0))
    else:
        for i in range (N, height, 2*N):
            strip = inv_img.crop((0, i, width, i+N))
            img.paste(strip, (0,i))
    return img

def mix(img, rules):
    width, height = img.size
    third_part_height = int(height / 3)
    arr = []
    for y in range (0, height, third_part_height):
        for x in range (0, height, third_part_height):
            part_img = img.crop((x, y, x + third_part_height, y + third_part_height))
            arr.append(part_img)
    number = 0
    for y in range (0, height, third_part_height):
        for x in range (0, height, third_part_height):
            need_part = rules[number]
            img.paste(arr[need_part], (x, y))
            number+=1
    return img
