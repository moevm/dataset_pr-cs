# Задача 1
def user_func(image, x0, y0, x1, y1, fill, width):
    draw = ImageDraw.Draw(image)
    draw.line(((x0, y0), (x1, y1)), fill=fill, width=width)
    return image

# Задача 2
def check_coords(image, x0, y0, x1, y1):
    if x0 < 0 or y0 < 0:
        return False

    image_width,image_height=image.size
    
    if (x1 > image_width or y1 > image_height or x1 <= x0 or y1 <= y0):
        return False
    else:
        return True

def set_black_white(image, x0, y0, x1, y1):
    if check_coords(image, x0, y0, x1, y1)==False:
        return image
    else:
        B_A_W_square=image.crop((x0, y0, x1, y1))
        B_A_W_square=B_A_W_square.convert("1")
        image.paste(B_A_W_square, (x0, y0))
        return image

    
# Задача 3
def find_rect_and_recolor(image, old_color, new_color):
    width, height = image.size
    max_square_area = 0
    max_square_coords=0

    for x in range(width):
        for y in range(height):
            pixel_color=image.getpixel((x, y))

            if pixel_color==old_color:
                square_coords,square_area=find_largest_square(image, x, y, old_color)
                if square_area > max_square_area:
                    max_square_area = square_area
                    max_square_coords = square_coords

    if max_square_coords!=0:
        x0, y0, x1, y1 = max_square_coords
        for x in range(x0, x1):
            for y in range(y0, y1):
                if image.getpixel((x, y)) == old_color:
                    image.putpixel((x, y), new_color)

    return image

def find_largest_square(image, x, y, old_color):
    width,height=image.size
    x0,y0,x1,y1=x,y,x,y

    while((x1 < width)and(image.getpixel((x1, y))==old_color)):
        x1 += 1

    while((y1 < height)and(image.getpixel((x, y1))==old_color)):
        y1 += 1

    return (x0, y0, x1, y1), (x1-x0)*(y1 - y0)
