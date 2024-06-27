# Задача 1
def user_func(image, x0, y0, x1, y1, fill, width):
    drawing=ImageDraw.Draw(image)
    drawing.line((x0, y0, x1, y1), fill=fill, width=width)
    
    return image

# Задача 2
def check_coords(image, x0, y0, x1, y1):
    width, height = image.size
    if x0 < 0 or y0 < 0 or x1 >= width or y1 >= height or x1 <= x0 or y1 <= y0:
        return False
    
    return True
        
def set_black_white(image, x0, y0, x1, y1):
    if check_coords(image, x0, y0, x1, y1):
        bw_ver=image.crop((x0, y0, x1, y1))
        bw_ver=bw_ver.convert('1')
        image.paste(bw_ver, (x0, y0, x1, y1))
    return image

# Задача 3
def find_rect_and_recolor(image, old_color, new_color):
    pixels = image.load()
    width, height = image.size
    max_rect = (0, 0, 0, 0)
    max_rect_area = 0
    for x in range(width):
        for y in range(height):
            if pixels[x, y] == old_color:
                rect = largest_rectangle(image, old_color, x, y)
                rect_area = (rect[2] - rect[0]) * (rect[3] - rect[1]) # площадь
                if rect_area > max_rect_area:
                    max_rect = rect
                    max_rect_area = rect_area

    draw = ImageDraw.Draw(image)
    draw.rectangle(max_rect, fill=new_color)

    return image

def largest_rectangle(image, color, start_x, start_y):
    pixels = image.load()
    width, height = image.size
    x, y = start_x, start_y
    while x < width and pixels[x, y] == color:
        x += 1
    x -= 1
    while y < height and pixels[x, y] == color:
        y += 1
    y -= 1
    
    return (start_x, start_y, x, y)
