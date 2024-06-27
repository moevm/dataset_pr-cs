import numpy
from PIL import Image, ImageDraw

def pentagram(img, x, y, r, thickness, color):
    drawing = ImageDraw.Draw(img)
    drawing.ellipse((x - r, y - r, x + r, y + r), outline = tuple(color), width=thickness)
    points = []
    for i in range(5):
        phi = (np.pi / 5) * (2 * i + 3 / 2)
        node_i = (int(x + r * np.cos(phi)), int(y + r * np.sin(phi)))
        points.append(node_i)
    for i in range(5):
        drawing.line((points[(i * 2) % 5], points[((i + 1) * 2) % 5]), fill=tuple(color), width=thickness)
    return img
    
def swap(img, x0,y0,x1,y1,width):
    picture = img.copy()
    section1 = img.crop((x0, y0, x0+width, y0+width)).rotate(270)
    section2 = img.crop((x1, y1, x1+width, y1+width)).rotate(270)
    picture.paste(section1,( x1, y1))
    picture.paste(section2,( x0, y0))
    return picture.rotate(270)    

def avg_color(img, x0,y0,x1,y1):
    new_img = img.copy()
    size = img.size
    for x in range(x0, x1 + 1):
        for y in range(y0, y1 + 1):
            sum = [0]*3
            pix_around = [(x-1,y-1), (x,y+1), (x,y-1), (x+1,y), (x+1,y-1), (x+1,y+1), (x-1,y+1), (x-1,y)]
            count = len(pix_around)
            for k in range(count):
                if not is_within_bounds(pix_around[count-k-1],size):
                    pix_around.pop(count-k-1)
            for n in pix_around:
                pixel = img.getpixel(n)
                for m in range(3):
                    sum[m] += pixel[m]        
            count = len(pix_around)
            new_color = (int(sum[0] / count), int(sum[1] / count), int(sum[2] / count))
            new_img.putpixel((x, y), new_color)
    return new_img
            
            
def is_within_bounds(coord,size):
    return (coord[0] >= 0) and (coord[0] < size[0]) and (coord[1] >= 0) and (coord[1] < size[1])