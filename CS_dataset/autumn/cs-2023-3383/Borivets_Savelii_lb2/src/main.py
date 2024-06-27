# Задача 1
def user_func(image, x0, y0, x1, y1, fill, width):
    draw = ImageDraw.Draw(image)
    draw.line((x0, y0, x1, y1), fill, width)
    return image

# Задача 2
def check_coords(image, x0, y0, x1, y1):
    if 0 <= x0 < image.size[0] and 0 <= y1 < image.size[1] and 0 <= x1 < image.size[0] and 0 <= y1 < image.size[1] and x0 < x1 and y0 < y1:
        return True
    return False

def set_black_white(image, x0, y0, x1, y1):
    if check_coords(image, x0, y0, x1, y1):
        img2 = image.crop((x0, y0, x1, y1))
        img2 = img2.convert('1')
        image.paste(img2, (x0, y0, x1, y1))
    return image

# Задача 3
def mx(rects):
    mx = -1
    mx_ind = 0
    for i in range(len(rects)):
        if mx < (rects[i][1] - rects[i][0])*(rects[i][3] - rects[i][2]):
            mx = (rects[i][1] - rects[i][0])*(rects[i][3] - rects[i][2]) 
            mx_ind = i
    return mx_ind
    
def find_rect_and_recolor(image, old_color, new_color):
    rects = []
    for x in range(image.size[0]):
        for y in range(image.size[1]):
            if image.getpixel((x, y)) == old_color:
                up = x
                down = x
                left = y
                right = y
                while down + 1 < image.size[0]:
                    if image.getpixel((down + 1, y)) == old_color:
                        down += 1
                    else:
                        break
                while right + 1 < image.size[1]:
                    if image.getpixel((x, right + 1)) == old_color:
                        right += 1
                    else:
                        break
                rects.append((up, down, left, right))
    mx_ind = mx(rects)
    for x in range(rects[mx_ind][0], rects[mx_ind][1] + 1):
        for y in range(rects[mx_ind][2], rects[mx_ind][3] + 1):
            image.putpixel((x,y), new_color)
    return image








