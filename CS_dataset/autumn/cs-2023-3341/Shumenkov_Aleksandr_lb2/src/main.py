import PIL
from PIL import Image, ImageDraw

#1

def user_func(image, x0, y0, x1, y1, fill, width):
    idr = ImageDraw.Draw(image)
    idr.line((x0,y0,x1,y1),fill,width)
    return image

#2

def check_coords(image, x0, y0, x1, y1):
    x,y=image.size
    return (((x1-x0)>=0 and ((y1-y0)>=0 and (x1-x0)<=x) and (y1-y0)<=y) and (x0>=0 and x1>=0 and y0>=0 and y1>=0))

def set_black_white(image,x0,y0,x1,y1):
    if check_coords(image,x0,y0,x1,y1)==True:
        img_one = image.crop((x0,y0,x1,y1))
        g_img = img_one.convert("1")
        image.paste(g_img, (x0,y0))
    return image


def check_coords(image, x0, y0, x1, y1):
    x,y=image.size
    return (((y1-y0)>=0 and (y1-y0)<=y) and (((x1-x0)>=0 and (x1-x0)<=x)) and  (x0>=0 and x1>=0) and (y0>=0 and y1>=0))


#3

def helperpr(x, y, width, height, datapx, old_color):
    top = [0, 0]
    bottom = [width, height]
    curr = [(x, y)]

    while len(curr)>0:
        x1, y1 = curr.pop()
        if (0 <= x1 < width and 0 <= y1 < height and datapx[x1, y1] == old_color):
            bottom = [min(bottom[0], x1), min(bottom[1], y1)]
            top = [max(top[0], x1), max(top[1], y1)]
            curr+=[(x1-1,y1),(x1+1,y1),(x1,y1-1),(x1,y1+1)]
            datapx[x1, y1] = (0, 0, 0)

    return (bottom[0], bottom[1], top[0], top[1])


def find_rect_and_recolor(image, old_color, new_color):
    max = 0
    cimg=image.copy()
    datapx = cimg.load()
    height, width = image.size[1], image.size[0]  
    for x in range(width):
        for y in range(height):
            if datapx[x, y] == old_color:
                crds = helperpr(x, y, width, height, datapx, old_color)
                s_rect = (crds[3]+1 - crds[1]) * (crds[2]+1 - crds[0])
                if s_rect > max:
                    max = s_rect
                    crds_max = crds

    image_r = image.load()                    
    for x in range(crds_max[0], crds_max[2]+1):
        for y in range(crds_max[1], crds_max[3]+1):
            image_r[x, y] = new_color

    return image

