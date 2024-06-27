import numpy as np
from PIL import Image, ImageDraw


# Задача 1
def user_func(image, x0, y0, x1, y1, fill, width):
    coordinates = (x0, y0, x1, y1)
    drawing = ImageDraw.Draw(image)
    drawing.line(coordinates, fill, width)
    return image


# Задача 2
def check_coords(image, x0, y0, x1, y1):
    x, y = image.size
    return (x >= x1) and (x1 > x0) and (x0 >= 0) and (y >= y1) and (y1 > y0) and (y0 >= 0)


def set_black_white(image, x0, y0, x1, y1):
    if check_coords(image, x0, y0, x1, y1):
        crop_img = image.crop((x0, y0, x1, y1))
        crop_img = crop_img.convert("1")
        image.paste(crop_img, (x0, y0))
    return image


# Задача 3
def largestRectangleArea(heights):
    n, heights, st, ans = len(heights), [0] + heights + [0], [], 0
    for i in range(n + 2):
        while st and heights[st[-1]] > heights[i]:
            ans = max(ans, heights[st.pop(-1)] * (i - st[-1] - 1))
        st.append(i)
    return ans


def check_sqr(x, pixel, sqr, max_sqr, n, ans, coordinates):
    for y in range(len(pixel[x])):
        if n <= pixel[x][y]:
            sqr += n
        if y == len(pixel[x]) - 1 or pixel[x][y + 1] < n:
            if max_sqr < sqr:
                max_sqr = sqr
                coordinates = (y - max_sqr // n + 1, x - n + 1, y, x)
                if max_sqr == ans:
                    return True, max_sqr, sqr, coordinates
            sqr = 0
    return False, max_sqr, sqr, coordinates


def find_big_rect(image, old_color):
    pixel = np.array(image).tolist()
    for x in range(len(pixel)):
        for y in range(len(pixel[x])):
            pixel[x][y] = 1 if pixel[x][y] == list(old_color) else 0
    pixel = np.array(pixel)
    heights = [0] * len(pixel[0])
    ans = 0
    for x in range(len(pixel)):
        for y in range(len(pixel[x])):
            if pixel[x][y] == 0:
                heights[y] = 0
            else:
                heights[y] += 1
        ans = max(ans, largestRectangleArea(heights))
    for x in range(1, len(pixel)):
        for y in range(len(pixel[x])):
            if pixel[x][y] == 0:
                pixel[x][y] = 0
            else:
                pixel[x][y] += pixel[x - 1][y]
    max_sqr = 0
    coordinates = (0, 0, 0, 0)
    for x in range(len(pixel)):
        sqr = 0
        for n in set(pixel[x]):
            fl, max_sqr, sqr, coordinates = check_sqr(x, pixel, sqr, max_sqr, n, ans, coordinates)
            if fl:
                return coordinates
            else:
                continue
    return coordinates


def find_rect_and_recolor(image, old_color, new_color):
    coordinates = find_big_rect(image, old_color)
    res = np.array(image)
    res[coordinates[1]:coordinates[3] + 1, coordinates[0]:coordinates[2] + 1, :3] = new_color
    image = Image.fromarray(res)
    return image

