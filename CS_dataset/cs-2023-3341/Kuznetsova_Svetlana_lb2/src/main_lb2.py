# Задача 1
def user_func(image, x0, y0, x1, y1, fill, width):
    drawing = ImageDraw.Draw(image)
    drawing.line(((x0,y0),(x1,y1)), fill, width)
    return image

# Задача 2
def check_coords(image, x0, y0, x1, y1):
    x,y=image.size
    return ((x0>=0 and x1>=0 and y0>=0 and y1>=0) and ((x1-x0)>=0 and (x1-x0)<=x) and ((y1-y0)>=0 and (y1-y0)<=y))

def set_black_white(image,x0,y0,x1,y1):
    if check_coords(image,x0,y0,x1,y1)==True:
        img1 = image.crop((x0,y0,x1,y1))
        gray_img = img1.convert("1")
        image.paste(gray_img, (x0,y0))
    return image

# Задача 3
def find_rect_and_recolor(image, old_color, new_color):
    img_copy=image.copy()
    pixdata = img_copy.load()
    width, height = image.size[0], image.size[1]  
    s_max = 0

    for x in range(width):
        for y in range(height):
            if pixdata[x, y] == old_color:
                coords = fill(x, y, width, height, pixdata, old_color)
                s_rect = (coords[3]+1 - coords[1]) * (coords[2]+1 - coords[0])
                if s_rect > s_max:
                    s_max = s_rect
                    coords_max = coords

    res_img = image.load()                    
    for x in range(coords_max[0], coords_max[2]+1):
        for y in range(coords_max[1], coords_max[3]+1):
            res_img[x, y] = new_color

    return image

def fill(x, y, width, height, pixdata, old_color):
    top = [0, 0]
    bottom = [width, height]
    curr = [(x, y)]

    while len(curr)>0:
        x1, y1 = curr.pop()
        if (0 <= x1 < width and 0 <= y1 < height and pixdata[x1, y1] == old_color):
            bottom = [min(bottom[0], x1), min(bottom[1], y1)]
            top = [max(top[0], x1), max(top[1], y1)]
            curr+=[(x1-1,y1),(x1+1,y1),(x1,y1-1),(x1,y1+1)]
            pixdata[x1, y1] = (0, 0, 0)

    return (bottom[0], bottom[1], top[0], top[1])
