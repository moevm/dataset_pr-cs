from PIL import Image, ImageDraw
import numpy as np

# Задача 1
def user_func(image, x0, y0, x1, y1, fill, width):
    drawing = ImageDraw.Draw(image)
    drawing.line(((x0,y0,x1,y1)), fill, width)
    return image

# Задача 2
def check_coords(image, x0, y0, x1, y1):
    if x0>=0 and y0>=0 and x1>=0 and y1>=0:
        if x0<x1 and y0<y1:
            if y1<=image.size[1] and x1<=image.size[0]:
                return True
            else:
                return False

def set_black_white(image, x0, y0, x1, y1):
    if check_coords(image, x0, y0, x1, y1):
        img = image.crop((x0, y0, x1, y1))
        img = img.convert('1')
        image.paste(img, (x0, y0))
    return image

# Задача 3
def find_rect_and_recolor(image, old_color, new_color):
    square=0
    x0,y0,x1,y1 = 0,0,0,0
    w=image.size[0]
    h=image.size[1]
    a=np.zeros((h,w))
    vertical=np.zeros((h,w))
    for i in range(h):
        for j in range(w):
            if image.getpixel((j,i))==old_color:
                a[i][j]=1
                if (i>0):
                    vertical[i][j]=vertical[i-1][j]+1
                else:
                    vertical[i][j]=1
    left=[0]*w
    right=[0]*w
    for i in range(h):
        s=[]
        for j in range(w):
            while len(s)>0 and vertical[i][s[-1]] >= vertical[i][j]:
                s.pop(-1)
            if len(s)==0:
                left[j]=0
            else:
                left[j]=s[-1]+1
            s.append(j)
        s=[]
        for j in range(w-1,-1,-1):
            while len(s)>0 and vertical[i][s[-1]]>=vertical[i][j]:
                s.pop(-1)
            if len(s)==0:
                right[j]=w-1
            else:
                right[j]=s[-1]-1
            s.append(j)
        for j in range(w):
            if square<(vertical[i][j])*(right[j]-left[j]+1):
                square=(vertical[i][j])*(right[j]-left[j]+1)
                x0,y0,x1,y1 = left[j],i-vertical[i][j]+1,right[j],i
    draw = ImageDraw.Draw(image)
    draw.rectangle((x0,y0,x1,y1),new_color)
    return image