from PIL import Image, ImageDraw

# Задача 1
def user_func(image, x0, y0, x1, y1, fill, width):
    drawing = ImageDraw.Draw(image)
    drawing.line((x0, y0, x1, y1), fill=fill, width=width)
    #image.show()
    return image

# Задача 2
def check_coords(image, x0, y0, x1, y1):
    if x0 == abs(x0) and x1 == abs(x1) and y0 == abs(y0) and y1 == abs(y1):
        img_size = image.size
        if x0 <= img_size[0] and x1 <= img_size[0] and y0 <= img_size[1] and y1 <= img_size[1]:
            if x0 < x1 and y0 < y1:
                return True
    else:
        return False

def set_black_white(image, x0, y0, x1, y1):
    if check_coords(image, x0, y0, x1, y1):
        img_cut = image.crop((x0, y0, x1, y1))
        img_cut = img_cut.convert('1')
        image.paste(img_cut, (x0, y0))
        #image.show()
    return image

# Задача 3
def find_rect_and_recolor(image, old_color, new_color):
    img_width = image.width
    img_height = image.height
    img_data = list(image.getdata())
    img_matrix = [[] for i in range(img_height)]
    k = 0
    for i in range(img_height):
        for j in range(img_width):
            img_matrix[i].append(img_data[k])
            k += 1

    x1 = y1 = x2 = y2 = 0
    height = [0] * (img_width + 1)
    area = 0
    row_count = -1
    for row in img_matrix:
        row_count += 1
        for i in range(img_width):
            height[i] = height[i] + 1 if row[i] == old_color else 0
        stack = [-1]
        for i in range(img_width + 1):
            while height[i] < height[stack[-1]]:
                h = height[stack.pop()]
                w = i - 1 - stack[-1]
                if area < h * w:
                    x2 = i - 1
                    y2 = row_count
                    x1 = stack[-1] + 1
                    y1 = row_count - h + 1
                    area = max(area, h * w)
            stack.append(i)

    for i in range(y1, y2+1):
        for j in range(x1, x2 + 1):
            img_matrix[i][j] = new_color
    k = 0
    for i in range(0, img_height):
        for j in range(0, img_width):
            img_data[k] = img_matrix[i][j]
            k += 1
    image.putdata(img_data)
    #image.show()
    return image

#find_rect_and_recolor(Image.new('RGB', (200, 200), (255,0,0)), (255, 0, 0), (0,0,255))
#user_func(Image.new('RGB', (200, 200), (255,0,0)), 100, 20, 40, 100, 'blue', 10)
#set_black_white(Image.new('RGB', (200, 200), (255,0,0)), 100, 50, 200, 100)
