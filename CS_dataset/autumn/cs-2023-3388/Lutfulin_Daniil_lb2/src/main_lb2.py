from PIL import Image, ImageDraw

# Задача 1
def user_func(image, x0, y0, x1, y1, fill, width):
    drawing = ImageDraw.Draw(image)
    drawing.line(((x0, y0), (x1, y1)), fill, width)
    return image


# Задача 2
def check_coords(image, x0, y0, x1, y1):
    size_x, size_y = image.size
    return (0 < x0 < x1 < size_x) and (0 < y0 < y1 < size_y)


def set_black_white(image, x0, y0, x1, y1):
    if check_coords(image, x0, y0, x1, y1):
        changed = image.crop((x0, y0, x1, y1))
        changed = changed.convert("1")
        image.paste(changed, (x0, y0))
        return image
    else:
        return image


# Задача 3
def max_under_pillar(data):
    stack = []
    max_rect = [0, 0, 0, 0]
    i = 0
    while (i < len(data) or stack):
        if (i < len(data)) and (not stack or data[stack[-1]] <= data[i]):
            stack.append(i)
            i += 1
        else:
            width = i
            height = data[stack.pop()]
            if stack:
                width = (i - stack[-1] - 1)
            area = width * height
            if area > max_rect[0]:
                max_rect = [area, width, height, i - 1]
    return max_rect


def max_in_matrix(matrix):
    max_rect = max_under_pillar(matrix[0]) + [0]
    for y in range(1, len(matrix)):
        for x in range(len(matrix[0])):
            if matrix[y][x]:
                matrix[y][x] += matrix[y - 1][x]
        new_rectangle = max_under_pillar(matrix[y]) + [y]
        if max_rect[0] < new_rectangle[0]:
            max_rect = new_rectangle
    return max_rect


def find_rect_and_recolor(image, old_color, new_color):
    pix = image.load()
    matrix = []
    for y in range(image.height):
        matrix.append([])
        for x in range(image.width):
            flag = (pix[x, y] == old_color)
            matrix[y].append(int(flag))
    area, w, h, x2, y2 = max_in_matrix(matrix)
    x1, y1 = x2 - w + 1, y2 - h + 1
    draw = ImageDraw.Draw(image)
    draw.rectangle((x1, y1, x2, y2), fill=new_color)
    return image
