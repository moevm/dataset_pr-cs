# Задача 1
def user_func(image, x0, y0, x1, y1, fill, width):
    draw = ImageDraw.Draw(image)
    draw.line([(x0, y0), (x1, y1)], fill, width)

    return image


# Задача 2
def check_coords(image, x0, y0, x1, y1):
    if x0 >= 0 and y0 >= 0 and x1 <= image.width and y1 <= image.height and x1 >= x0 and y1 >= y0:
        return True
    return False


def set_black_white(image, x0, y0, x1, y1):
    if not check_coords(image, x0, y0, x1, y1):
        return image

    # Преобразвание изображения в ч/б
    region = image.crop((x0, y0, x1, y1))
    region = region.convert('1')

    image.paste(region, (x0, y0, x1, y1))

    return image


# Задача 3
def find_rect_and_recolor(image, old_color, new_color):
    img_width, img_height = image.size
    img_data = list(image.getdata())
    img_matrix = [img_data[i:i+img_width] for i in range(0, len(img_data), img_width)]

    x1 = y1 = x2 = y2 = 0
    n = img_width
    height = [0] * (n + 1)
    area = 0
    row_count = -1

    for row in img_matrix:
        row_count += 1
        for i in range(n):
            height[i] = height[i] + 1 if row[i] == old_color else 0

        stack = [-1]
        for i in range(n + 1):
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

    for i in range(y1, y2 + 1):
        for j in range(x1, x2 + 1):
            img_matrix[i][j] = new_color

    img_data = [pixel for row in img_matrix for pixel in row]
    image.putdata(img_data)
    return image
