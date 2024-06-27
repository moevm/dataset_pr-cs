from PIL import Image, ImageDraw
from PIL.Image import Image
import numpy as np


# Задача 1
def user_func(image: Image, x0, y0, x1, y1, fill, width):
    ImageDraw.Draw(image).line((x0, y0, x1, y1), fill, width)
    return image


# Задача 2
def check_coords(image: Image, x0, y0, x1, y1):
    return (
        x0 <= x1
        and y0 <= y1
        and x0 >= 0
        and y0 >= 0
        and x1 <= image.width
        and y1 <= image.height
    )
    # using black formatter


def set_black_white(image: Image, x0, y0, x1, y1):
    if not check_coords(image, x0, y0, x1, y1):
        return image
    _img = image.crop((x0, y0, x1, y1))
    _img = _img.convert("1")
    image.paste(_img, (x0, y0))
    return image


# Задача 3
def find_rect_and_recolor(image: Image, old_color: tuple, new_color: tuple):
    image = image.convert("RGB")
    width, height = image.size
    max_pos = (0, 0, 0, 0)
    max_area = 0
    bars = np.zeros((width,), dtype=int)

    bit_mask = np.all(np.array(image) == old_color, axis=2)

    # processing top to bottom (cus why not)
    for y in range(height):
        left_boundary = np.zeros(width, dtype=int)
        right_boundary = np.zeros(width, dtype=int)

        # y is bottom line of bars
        bars[bit_mask[y]] += 1  # numpy shenanigans :D (vectorised)
        bars[~bit_mask[y]] = 0
        # this is same as:
        # for x in range(width):
        #     if bit_mask[y][x]:
        #         bars[x] += 1
        #     else:
        #         bars[x] = 0

        temp = []
        for x in range(width):
            while temp and bars[temp[-1]] >= bars[x]:
                temp.pop()
            left_boundary[x] = temp[-1] if temp else -1
            temp.append(x)

        temp = []
        for x in range(width - 1, -1, -1):
            while temp and bars[temp[-1]] >= bars[x]:
                temp.pop()
            right_boundary[x] = temp[-1] if temp else width
            temp.append(x)

        # area for every bar
        for x in range(width):
            area = bars[x] * (right_boundary[x] - left_boundary[x] - 1)
            if area > max_area:
                max_area = area
                max_pos = (
                    left_boundary[x] + 1,
                    y - bars[x] + 1,
                    right_boundary[x] - 1,
                    y,
                )

    if max_area != 0:
        ImageDraw.Draw(image).rectangle(max_pos, new_color)
    return image


# if __name__ == "__main__":
#     with Image.open("test.png") as im:
#         o = find_rect_and_recolor(im, (0, 0, 0), (200, 0, 0))
#     o.save("o.png")
