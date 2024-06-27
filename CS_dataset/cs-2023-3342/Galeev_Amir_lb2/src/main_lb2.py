from PIL import Image, ImageDraw
import math

def swap(img, x0,y0,x1,y1,width):
    new_img = img.copy()
    box0 = (x0, y0, x0 + width, y0 + width)
    box1 = (x1, y1, x1 + width, y1 + width)
    region0 = new_img.crop(box0)
    region1 = new_img.crop(box1)
    new_img.paste(region1, box0)
    new_img.paste(region0, box1)
    region0 = new_img.crop(box0).rotate(-90)
    region1 = new_img.crop(box1).rotate(-90)
    new_img.paste(region0, box0)
    new_img.paste(region1, box1)
    new_img = new_img.rotate(-90)

    return new_img
    
def avg_color(img, x0, y0, x1, y1):
    new_img = img.copy()
    for y in range(y0, y1 + 1):
        for x in range(x0, x1 + 1):
            pixel_color = img.getpixel((x, y))
            x_min = max(x - 1, 0)
            x_max = min(x + 1, img.width - 1)
            y_min = max(y - 1, 0)
            y_max = min(y + 1, img.height - 1)
            neighbors = []
            for ny in range(y_min, y_max + 1):
                for nx in range(x_min, x_max + 1):
                    if nx != x or ny != y:
                        neighbors.append(img.getpixel((nx, ny)))
            count = len(neighbors)
            avg_color = (
                int(sum([c[0] for c in neighbors]) / count),
                int(sum([c[1] for c in neighbors]) / count),
                int(sum([c[2] for c in neighbors]) / count))
            new_img.putpixel((x, y), avg_color)
            
    return new_img
    
def pentagram(img, x, y, r, thickness, color):
    draw = ImageDraw.Draw(img)
    vertices = []
    for i in range(5):
        phi = (math.pi/5)*(2*i + 3/2)
        vertex = (int(x + r * math.cos(phi)), int(y + r * math.sin(phi)))
        vertices.append(vertex)
    draw.ellipse((x - r, y - r, x + r, y + r), outline=tuple(color), width=thickness)
    for i in range(5):
        draw.line([vertices[i], vertices[(i + 2) % 5]], fill=tuple(color), width=thickness)

    return img
