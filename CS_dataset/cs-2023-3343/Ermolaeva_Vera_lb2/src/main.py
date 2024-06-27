from PIL import ImageDraw
import numpy as np

def swap(img, x0, y0, x1, y1, width):
    img1 = img.copy()
    square1 = img1.crop((x0, y0, x0 + width, y0 + width))
    square2 = img1.crop((x1, y1, x1 + width, y1 + width))

    square1 = square1.rotate(270) 
    square2 = square2.rotate(270)

    img1.paste(square2, (x0, y0))
    img1.paste(square1, (x1, y1))

    img1 = img1.rotate(270)
    return img1

def get_pixel(img, x, y):
    neighbours = [img.getpixel((x-1, y)), img.getpixel((x-1, y-1)), img.getpixel((x, y-1)), img.getpixel((x+1, y-1)), 
                    img.getpixel((x+1, y)), img.getpixel((x+1, y+1)), img.getpixel((x, y+1)), img.getpixel((x-1, y+1))]

    avg_color = (
        int(sum(color[0] for color in neighbours)/8),
        int(sum(color[1] for color in neighbours)/8),
        int(sum(color[2] for color in neighbours)/8),
    )

    return avg_color

def avg_color(img, x0, y0, x1, y1): 
    img_copy = img.copy()

    for x in range(x0, x1+1):
        for y in range(y0, y1+1):
            img_copy.putpixel((x,y), get_pixel(img, x, y))

    return img_copy

def pentagram(img, x, y, r, thickness, color):
    draw = ImageDraw.Draw(img)
    color = tuple(color)

    draw.ellipse([x-r, y-r, x+r, y+r], None, color, thickness)
    points = []
    
    for i in range(5):
        phi = (np.pi/5)*(2*i+3/2)
        points.append((int(x+r*np.cos(phi)), int(y+r*np.sin(phi))))
    
    points[1], points[2], points[3], points[4] = points[2], points[4], points[1], points[3]

    for i in range(4):
        draw.line((points[i], points[i+1]), color, thickness)
    draw.line((points[4], points[0]), color, thickness)
    
    return img