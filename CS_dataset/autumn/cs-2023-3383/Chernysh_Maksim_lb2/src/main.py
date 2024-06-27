from PIL import Image, ImageDraw

def user_func(image, x0, y0, x1, y1, fill, width):
    drawing = ImageDraw.Draw(image)
    drawing.line((x0, y0, x1, y1), fill, width)
    return image
    
    
def check_coords(image, x0, y0, x1, y1):
    height, width=image.size
    return (height>=x1) and (x1>x0) and (x0>=0) and (width>=y1) and (y1>y0) and (y0>=0)
    
    
def set_black_white(image, x0, y0, x1, y1):
    if not check_coords(image, x0, y0, x1, y1):
        return image
    cropped_image = image.crop((x0, y0, x1, y1))
    cropped_image = cropped_image.convert("1")
    image.paste(cropped_image, (x0, y0))
    return image
 
    
def find_rect_and_recolor(image, old_color, new_color):
    width, height = image.size
    pix = image.load()
    max_rect_size = 0
    max_rect_position = (0, 0, 0, 0)
    for x in range(width):
        for y in range(height):
            if pix[x, y] == old_color:
                rect_size = get_rect_size(pix, x, y, old_color, width, height)
                if rect_size > max_rect_size:
                    max_rect_size = rect_size
                    max_rect_position = (x, y, x + rect_size, y + rect_size)
    if max_rect_size > 0:
        for x in range(max_rect_position[0], max_rect_position[2]):
            for y in range(max_rect_position[1], max_rect_position[3]):
                if pix[x, y] == old_color:
                    pix[x, y] = new_color

    return image

def get_rect_size(pix, start_x, start_y, color, width, height):
    rect_size = 0
    for x in range(start_x, width):
        if pix[x, start_y] == color:
            rect_size += 1
        else:
            break
    return rect_size
