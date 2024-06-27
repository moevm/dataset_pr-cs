from PIL import Image, ImageDraw, ImageOps
import numpy

# Задача 1

def user_func(image, x0, y0, x1, y1, fill, width):
    draw = ImageDraw.Draw(image)
    draw.line((x0, y0, x1, y1), fill, width)
    return image

# Задача 2

def check_coords(image, x0, y0, x1, y1):
    height, width = image.size
    if x1>x0 and y1>y0 and min(x0,y0)>=0 and x1<=height and y1<=width and x0%1==0 and x1%1==0 and y0%1==0 and y1%1==0:
        return True
    else:
        return False

def set_black_white(image, x0, y0, x1, y1):
    if check_coords(image, x0, y0, x1, y1):
        image.paste(image.crop((x0, y0, x1, y1)).convert('1'), (x0, y0))
    return image
        

# Задача 3
def find_rect_and_recolor(image, old_color, new_color):
    if not isinstance(old_color, tuple):
        old_color = PIL.ImageColor.getrgb(old_color)
    width, height = image.size
    max_area = 0
    best_xy = None
    part = numpy.zeros(image.size, dtype=numpy.uint32)
    for i in range(width):
        for j in range(height):
            part[i, j] = int(image.getpixel((i, j)) == old_color)
    hist = numpy.zeros(height, dtype=numpy.uint32)
    for i in range(width):
        hist = numpy.multiply((hist + 1), part[i])
        area, y = max_area_histogram(hist)
        if y is not None:
            width = area // (y[1] - y[0])
            assert width == min(hist[y[0] : y[1]])
        if area > max_area:
            max_area = area
            best_xy = (i + 1 - width, y[0]), (i, y[1] - 1)
    if best_xy is not None:
        draw = ImageDraw.Draw(image)
        draw.rectangle(best_xy, fill=new_color, outline=new_color)
    return image
    
    
def max_area_histogram(hist):
    stack = []
    max_area = 0
    best_y = None
    index = 0
    while index < len(hist):
        if (not stack) or (hist[stack[-1]] <= hist[index]):
            stack.append(index)
            index += 1
        else:
            top = stack.pop()
            y = (stack[-1] + 1, index) if stack else (0, index)
            area = hist[top] * (y[1] - y[0])
            if area > max_area:
                max_area = area
                best_y = y
    while stack:
        top = stack.pop()
        y = (stack[-1] + 1, index) if stack else (0, index)
        area = hist[top] * (y[1] - y[0])
        if area > max_area:
            max_area = area
            best_y = y
    return max_area, best_y