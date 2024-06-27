import PIL
from PIL import Image, ImageDraw


# Задача 1
def user_func(image, x0, y0, x1, y1, fill, width):
    drawing = ImageDraw.Draw(image)
    drawing.line(((x0,y0), (x1,y1)), fill, width)
    return image

# Задача 2
def check_coords(image, x0, y0, x1, y1):
    if x0>0 and y0>0 and x1>0 and y1>0:
        if y0<image.size[1] and x1<image.size[0] and y1<image.size[1] and x0<image.size[0]:
            if x0<x1 and y0<y1:
                return True
    else:
        return False

def set_black_white(image, x0, y0, x1, y1):
    if check_coords(image, x0, y0, x1, y1):
        gray_img = image.crop((x0, y0, x1, y1))
        gray_img = gray_img.convert("1")
        image.paste(gray_img, (x0, y0))
        return image
    else:
        return image

# Задача 3
def find_rect_and_recolor(image, old_color, new_color):
    x_max_size = image.size[0]
    y_max_size = image.size[1]
    obj=image.load()
    maxplo=0
    coords=[]
    for x in range(x_max_size):
        for y in range(y_max_size):
            if obj[x,y]==old_color:
                x1=x
                y1=y
                while x1< x_max_size and obj[x1,y]==old_color:
                    x1+=1
                while y1<y_max_size and obj[x,y1]==old_color:
                    y1+=1
                if (x1-x)*(y1-y)>maxplo:
                    maxplo=(x1-x)*(y1-y)
                    coords=[x,y, x1,y1]
    for i in range(coords[0],coords[2]):
        for j in range(coords[1],coords[3]):
            obj[i,j]=new_color
    return image