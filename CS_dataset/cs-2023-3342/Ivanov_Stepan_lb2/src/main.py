from numpy import (
    pi,
    sin,
    cos
)

from PIL import ImageDraw


def get_peak(get_fi, get_node, node_num):
    fi = get_fi(node_num)
    return get_node(fi)


def pentagram(img, x, y, r, thickness, color):
    draw = ImageDraw.Draw(img)
    
    draw.ellipse(
        [x - r, y - r, x + r, y + r], 
        None, 
        tuple(color), 
        thickness
    )
    
    peaks = [
        get_peak(
            lambda n: (pi / 5) * (2 * n + 3 / 2),
            lambda fi: (int(x + r * cos(fi)), int(y + r * sin(fi))),
            n
        ) for n in range(5)
    ]
    
    for i in range(5):
        draw.line((peaks[i], peaks[(i + 2) % 5]), tuple(color), thickness)
    
    return img


def swap(img, x0, y0, x1, y1, width):
    new_img = img.copy()
    fi = -90

    picture1 = img.crop((x0, y0, x0 + width, y0 + width)).rotate(fi)
    picture2 = img.crop((x1, y1, x1 + width, y1 + width)).rotate(fi)

    new_img.paste(picture1, (x1, y1))
    new_img.paste(picture2, (x0, y0))

    new_img = new_img.rotate(fi)

    return new_img



def check_boundary(pixel, scope):
    return pixel[0] >= 0 and pixel[0] < scope[0] and pixel[1] >= 0 and pixel[1] < scope[1]


def avg_color(img, x0, y0, x1, y1):
    new_img = img.copy()
    img_arr = new_img.load()
    shape_img = new_img.size

    for x in range(x0, x1 + 1):
        for y in range(y0, y1 + 1):

            near_pixels_cord = tuple(p for p in (
                    (x - 1, y - 1), (x, y - 1), (x + 1, y - 1), (x + 1, y), 
                    (x + 1, y + 1), (x, y + 1), (x - 1, y + 1), (x - 1, y)
                ) if check_boundary(p, shape_img)
            )

            near_pixels = tuple(img.getpixel(p) for p in near_pixels_cord)
            count_of_near_pixels = len(near_pixels)

            r = (p[0] for p in near_pixels)
            g = (p[1] for p in near_pixels)
            b = (p[2] for p in near_pixels)
            
            color = (
                int(sum(r) / count_of_near_pixels), 
                int(sum(g) / count_of_near_pixels), 
                int(sum(b) / count_of_near_pixels)
            )

            img_arr[x, y] = color

    return new_img
