import numpy as np
import PIL
from PIL import Image, ImageDraw

def triangle(img, x0, y0, x1, y1, x2, y2, thickness, color, fill_color):
    use_color = tuple(color)
    if fill_color!= None:
        to_fill = tuple(fill_color)
    else: to_fill = fill_color
    
    draw = ImageDraw.Draw(img)
    
    draw.polygon([x0,y0,x1,y1,x2,y2],to_fill,use_color,thickness)
        
    return img
    
    
def change_color(img, color):
    img2 = img.copy()
    draw = ImageDraw.Draw(img2)
    pixels = img.load()
    replacement_color = tuple(color)
    
    hwmch = {}
    
    for i in range(img.size[0]):
        for j in range(img.size[1]):
            current_color = img.getpixel((i,j))
            if current_color in hwmch:
                hwmch[current_color]+=1
            else:
                hwmch[current_color]=1
    
    maxx = max(hwmch.values())
    for keys in hwmch:
        if hwmch[keys]==maxx:most_used_color = keys
    
    for x in range(img.size[0]):
        for y in range(img.size[1]):
            if img2.getpixel((x,y))==most_used_color:
                draw.point((x,y),fill = replacement_color)
    
    return img2
    
def collage(img, N, M):
    img_copied = np.copy(img)
    combined = img_copied
    for i in range(1,M):
        combined = np.hstack((combined,img_copied))
    
    temp = combined
    for j in range(N-1):
        combined = np.vstack((combined,temp))
        
    background = Image.fromarray(combined)
    
    return background
