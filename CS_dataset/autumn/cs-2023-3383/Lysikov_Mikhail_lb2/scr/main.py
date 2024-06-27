from PIL import Image
import numpy as np


def user_func(image, x0, y0, x1, y1, fill, width):
    draw = ImageDraw.Draw(image)
    draw.line((x0, y0, x1, y1), fill, width)
    return image

def check_coords(image, x0, y0, x1, y1):
    width, height = image.size
    if ((0 <= x0 < width) and (0 <= y0 < height) and (0 <= x1 < width) and (0 <= y1 < height) and (x1 > x0 and y1 > y0)):
        return True
    else:
        return False

def set_black_white(image, x0, y0, x1, y1):
    if not check_coords(image, x0, y0, x1, y1):
        return image
    region = image.crop((x0, y0, x1, y1))
    bw_region = region.convert('1')
    image.paste(bw_region, (x0, y0, x1, y1))
    return image

def find_coordinates(matrix):

    max_area = 0
    x_init, y_init, x_end, y_end = 0, 0, 0, 0

    for pixel_h in range(len(matrix)):
        for pixel_v in range(len(matrix[pixel_h])):
            
            if matrix[pixel_h][pixel_v] == 0:
                
                for height in range(pixel_h, len(matrix)):
                    if matrix[height][pixel_v] != 0:
                        height -= 1
                        break

                for width in range(pixel_v, len(matrix[pixel_h])):
                    if matrix[pixel_h][width] != 0:
                        width -= 1
                        break

                if max_area < (width - pixel_h + 1) * (height - pixel_v + 1):
                    max_area = (width - pixel_h + 1) * (height - pixel_v + 1)
                    x_init, y_init, x_end, y_end = pixel_v, pixel_h, width, height

    return x_init, y_init, x_end, y_end


def find_rect_and_recolor(image, old_color, new_color):
    
    old_color = list(old_color)
    matrix = np.array(image).tolist()
    
    for pixel_h in range(len(matrix)):
        for pixel_v in range(len(matrix[pixel_h])):
            
            if matrix[pixel_h][pixel_v] == old_color:
                matrix[pixel_h][pixel_v] = 0
                
            else:
                matrix[pixel_h][pixel_v] = 1
                
    coordinates = find_coordinates(matrix)
    draw = ImageDraw.Draw(image)
    draw.rectangle(coordinates, new_color)
    return image
