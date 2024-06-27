import numpy as np
from PIL import Image, ImageDraw


def user_func(image, x0, y0, x1, y1, fill, width):
    draw = ImageDraw.Draw(image)
    draw.line((x0, y0, x1, y1), fill, width)
    return image


def check_coords(image, x0, y0, x1, y1):
    width, height = image.size

    coord_not_negative = x0 >= 0 and x1 >= 0 and y0 >= 0 and y1 >= 0
    coord_fit = x1 <= width and y1 <= height
    x1y1_greater_x0y0 = x1 > x0 and y1 > y0

    if coord_not_negative and coord_fit and x1y1_greater_x0y0:
        return True
    return False


def set_black_white(image, x0, y0, x1, y1):
    coord_check_not_passed = not (check_coords(image, x0, y0, x1, y1))

    if coord_check_not_passed:
        return image

    img_crp = image.crop((x0, y0, x1, y1)).convert('1')
    image.paste(img_crp, (x0, y0, x1, y1))
    return image


def find_rect(image, color):
    pixels = image.load()
    width, height = image.size

    vector = np.zeros(width, dtype=int)

    area_size, left_i, left_j, right_i, right_j = 0, 0, 0, 0, 0

    for j in range(height):
        for i in range(width):
            if pixels[i, j] == color:
                vector[i] += 1
            else:
                vector[i] = 0


        heights_set = set(vector)

        max_area, max_area_left_i, max_area_right_i, max_area_left_j, max_area_right_j = 0, 0, 0, 0, 0
        for set_elem in heights_set:
            max_chunk, max_chunk_i, max_chunk_j, chunk, chunk_i, chunk_j = 0, 0, 0, 0, 0, 0
            for vec_i in range(width):
                if vector[vec_i] >= set_elem:
                    if chunk == 0:
                        chunk_i = vec_i
                        chunk_j = set_elem
                    chunk += 1
                else:
                    if chunk > max_chunk:
                        max_chunk = chunk
                        max_chunk_i = chunk_i
                        max_chunk_j = chunk_j
                    chunk = 0
            else:
                if chunk > max_chunk:
                    max_chunk = chunk
                    max_chunk_i = chunk_i
                    max_chunk_j = chunk_j

            new_area_size = max_chunk * set_elem
            if new_area_size > max_area:
                max_area = new_area_size
                max_area_left_i = max_chunk_i
                max_area_right_i = max_area_left_i + max_chunk - 1
                max_area_left_j = j - set_elem + 1
                max_area_right_j = j

        if max_area > area_size:
            area_size = max_area
            left_i = max_area_left_i
            right_i = max_area_right_i
            left_j = max_area_left_j
            right_j = max_area_right_j

    return area_size, (left_i, left_j), (right_i, right_j)


def recolor_rect(image, i, j, new_color):
    drawing = ImageDraw.Draw(image)
    drawing.rectangle((i, j), new_color)
    return image


def find_rect_and_recolor(image, old_color, new_color):
    area_size, left, right = find_rect(image, old_color)
    if area_size > 0:
        upd_image = recolor_rect(image, left, right, new_color)
        return upd_image
    else:
        return image

