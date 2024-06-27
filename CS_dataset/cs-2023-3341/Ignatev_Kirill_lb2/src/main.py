import PIL
from PIL import Image, ImageDraw

def user_func(image, x0, y0, x1, y1, fill, width):
    drawing = ImageDraw.Draw(image)
    drawing.line((x0,y0,x1,y1),fill,width)
    return image

def check_coords(image, x0, y0, x1, y1):
    width, height = image.size

    return not ((x0 < 0 or y0 < 0 or x1 < 0 or y1 < 0) or (x0 >= width or x1 >= width or y0 >= height or y1 >= height) or (x1 <= x0 or y1 <= y0))

def set_black_white(image, x0, y0, x1, y1):
    if check_coords(image, x0, y0, x1, y1):
        region = image.crop((x0, y0, x1, y1))
        region = region.convert('1')
        image.paste(region, (x0, y0, x1, y1))
    return image

def find_max_rect(pix, width, height, x,y,old_color):
    min_cord = [0, 0]
    max_cord = [width, height]
    curr = [(x, y)]
    while len(curr) > 0:
        x1, y1 = curr.pop()
        if (0 <= x1 < width and 0 <= y1 < height and pix[x1, y1] == old_color):
            max_cord = [min(max_cord[0], x1), min(max_cord[1], y1)]
            min_cord = [max(min_cord[0], x1), max(min_cord[1], y1)]
            curr += [(x1 - 1, y1), (x1 + 1, y1), (x1, y1 - 1), (x1, y1 + 1)]
            pix[x1, y1] = (0, 0, 0)
    return (max_cord[0], max_cord[1], min_cord[0], min_cord[1])

def find_rect_and_recolor(image, old_color, new_color):
    img=image.copy()
    pix=img.load()
    width, height=img.size[0], image.size[1]
    max_rect=0
    for x in range(width):
        for y in range(height):
            if pix[x,y]==old_color:
                cords=find_max_rect(pix, width, height, x,y,old_color)
                rect= (cords[3]+1 - cords[1])*(cords[2]+1 - cords[0])
                if rect>max_rect:
                    max_cords=cords
                    max_rect=rect
    res_img=image.load()
    for x in range (max_cords[0], max_cords[2]+1):
        for y in range (max_cords[1], max_cords[3]+1):
            res_img[x,y]=new_color
    return image

