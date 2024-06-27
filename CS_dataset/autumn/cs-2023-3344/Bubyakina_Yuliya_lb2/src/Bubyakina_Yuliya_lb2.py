from PIL import Image, ImageDraw

# Задача 1
def user_func(image, x0, y0, x1, y1, fill, width):
    drawing = ImageDraw.Draw(image)
    drawing.line((x0, y0, x1, y1), fill, width)
    return image

# Задача 2
def check_coords(image, x0, y0, x1, y1):
    if x0>=0 and y0>=0 and x1>=0 and y1>=0 and x0<=image.size[0] and x1<=image.size[0] and y0<=image.size[1] and y1<=image.size[1] and x0<=x1 and y0<=y1:
        return True
    return False

def set_black_white(image, x0, y0, x1, y1):
    if check_coords(image, x0, y0, x1, y1):
        cut = image.crop((x0,y0,x1,y1))
        cut_final = cut.convert('1')
        image.paste(cut_final,(x0,y0,x1,y1))
        return image
    return image

# Задача 3
def find_rect_and_recolor(image, old_color, new_color):
    old_color=tuple(old_color)
    new_color = tuple(new_color)
    pixel_obj = image.load()
    width,height = image.size
    max_area=0
    max_coords=()
    for x in range(width):
        for y in range(height):
            if pixel_obj[x,y]==old_color:
                area=1
                x1=1
                y1=1
                while x1+x<width and pixel_obj[x1+x,y]==old_color:
                    x1+=1
                while y1+y<height and pixel_obj[x,y1+y]==old_color:
                    y1+=1
                area=y1*x1
                if area>max_area:
                    max_area=area
                    max_coords=(x,y,x+x1-1,y+y1-1)
    for x in range (max_coords[0],max_coords[2]+1):
        for y in range(max_coords[1], max_coords[3] + 1):
            image.putpixel((x,y),new_color)
    return image
