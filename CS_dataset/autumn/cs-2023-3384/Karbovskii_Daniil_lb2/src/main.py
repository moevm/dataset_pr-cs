
import numpy as np
from PIL import Image, ImageDraw
# Задача 1
def user_func(image, x0, y0, x1, y1, fill, width):
    xy = (x0, y0, x1, y1)
    drawing = ImageDraw.Draw(image)
    drawing.line(xy, fill, width)
    return image
# Задача 2
def check_coords(image, x0, y0, x1, y1):
    x, y = image.size
    if (x >= x1) and (x1 > x0) and (x0 >= 0) and (y >= y1) and (y1 > y0) and (y0 >= 0):
        return True
    return False
def set_black_white(image, x0, y0, x1, y1):
    if check_coords(image, x0, y0, x1, y1):
        crop_image = image.crop((x0, y0, x1, y1))
        crop_image = crop_image.convert("1")
        image.paste(crop_image, (x0, y0))
    return image
# Задача 3
def largestRectangleArea(heights):
    n, heights, st, ans = len(heights), [0] + heights + [0], [], 0
    for i in range(n + 2):
        while st and heights[st[-1]] > heights[i]:
            ans = max(ans, heights[st.pop(-1)] * (i - st[-1] - 1))
        st.append(i)
    return ans
def check_sqr(x, pixel, sqr, max_sqr, n, ans, xy):
    for y in range(len(pixel[x])):
        if n <= pixel[x][y]:
            sqr += n
        if y == len(pixel[x]) - 1 or pixel[x][y + 1] < n:
            if max_sqr < sqr:
                max_sqr = sqr
                xy = (y - max_sqr // n + 1, x - n + 1, y, x)
                if max_sqr == ans:
                    return True, max_sqr, sqr, xy
            sqr = 0
    return False, max_sqr, sqr, xy
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
    xy = (0, 0, 0, 0)
    for x in range(len(pixel)):
        sqr = 0
        for n in set(pixel[x]):
            fl, max_sqr, sqr, xy = check_sqr(x, pixel, sqr, max_sqr, n, ans, xy)
            if fl:
                return xy
    return xy
def find_rect_and_recolor(image, old_color, new_color):
    xy = find_big_rect(image, old_color)
    res = np.array(image)
    res[xy[1]:xy[3] + 1, xy[0]:xy[2] + 1, :3] = list(new_color)
    image = Image.fromarray(res)
    return image