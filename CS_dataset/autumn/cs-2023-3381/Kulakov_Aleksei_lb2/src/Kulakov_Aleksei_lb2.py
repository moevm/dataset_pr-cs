from PIL import Image, ImageDraw
import numpy as np
# Задача 1
def user_func(image, x0, y0, x1, y1, fill, width):
    ans = ImageDraw.Draw(image)
    ans.line((x0,y0,x1,y1),fill = fill,width = width)
    return image

# Задача 2
def check_coords(image, x0, y0, x1, y1):
    w, h = image.size
    if x1 > x0 and y1 > y0 and x0 >= 0 and y0 >= 0 and x1 <= w and y1 <= h:
        return True
    return False

def set_black_white(image, x0, y0, x1, y1):
    if not check_coords(image, x0, y0, x1, y1):
        return image
    region = image.crop((x0, y0, x1, y1))
    region = region.convert("1")
    image.paste(region, (x0, y0))
    return image

# Задача 3
def find_rect_and_recolor(image, old_color, new_color):
    w, h = image.size
    a = np.zeros((h,w))
    for i in range(h):
        for j in range(w):
            if image.getpixel((j,i)) == old_color:
                a[i][j]=1
    d,d1,d2 = [-1]*w, [0]*w, [0]*w
    arrm = 0
    x0m, y0m, x1m, y1m = 0,0,0,0
    stack = []
    for i in range(h):
        for j in range(w):
            if a[i][j] == 0:
                d[j] = i 
        for j in range(w):
            while stack and d[stack[-1]] <= d[j]:
                stack.pop()
            if (not stack):
                d1[j] = -1
            else:
                d1[j] = stack[-1]
            stack.append(j)
        stack.clear()
        for j in range(w-1,-1,-1):
            while stack and d[stack[-1]] <= d[j]:
                stack.pop()
            if (not stack):
                d2[j] = w
            else:
                d2[j] = stack[-1]
            stack.append(j)
        stack.clear()
        for j in range(w):
            if (i-d[j])*(d2[j]-d1[j]-1) > arrm:
                arrm = (i-d[j])*(d2[j]-d1[j]-1)
                x0m,y0m,x1m,y1m = d1[j]+1,d[j]+1,d2[j]-1,i
    draw = ImageDraw.Draw(image)
    draw.rectangle((x0m, y0m, x1m, y1m), fill=new_color)
    return image