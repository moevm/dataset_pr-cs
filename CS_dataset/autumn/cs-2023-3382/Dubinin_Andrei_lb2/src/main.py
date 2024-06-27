import PIL
import numpy

# Задача 1
def triangle(img, x0, y0, x1, y1, x2, y2, thickness, color, fill_color=None):
    color = tuple(color)
    drawing = ImageDraw.Draw(img)
    if fill_color == None:
        drawing.polygon([(x0, y0), (x1, y1), (x2, y2)], fill=None, outline=tuple(color), width=thickness)
    else:
        fill_color = tuple(fill_color)
        drawing.polygon([(x0, y0), (x1, y1), (x2, y2)], fill=fill_color, outline=tuple(color), width=thickness)
    return img



# Задача 2
def change_color(img1, color):
    img = img1
    pixels = img.load()
    pix_info = {}
    for x in range(img.width):
        for y in range(img.height):
            if str(pixels[x, y]) not in pix_info:
                pix_info[str(pixels[x, y])] = 0
            else:
                pix_info[str(pixels[x, y])] += 1

    val = list(pix_info.values())
    qq = list(pix_info.keys())[val.index(max(val))]

    for x in range(img.width):
        for y in range(img.height):
            if str(pixels[x, y]) == str(qq):
                pixels[x, y] = tuple(color)

    return img


# Задача 3
def collage(image, N, M):
    width, height = image.size
    photo = Image.new("RGB", (width*M, height*N), 'white')
    width_collage, height_collage = photo.size
    for x in range(0,width_collage,width):
        for y in range(0,height_collage,height):
            photo.paste(image, (x, y))

    return photo
