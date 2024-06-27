import PIL
from PIL import Image, ImageDraw

# Задача 1
def triangle(img, x0, y0, x1, y1, x2, y2, thickness, color, fill_color):
    drawing = ImageDraw.Draw(img)
    coordinates = [(x0,y0),(x1,y1),(x2,y2)]
    if fill_color is None:
        drawing.polygon(coordinates, outline=tuple(color), width=thickness)
    else:
        drawing.polygon(coordinates, fill=tuple(fill_color),outline= tuple(color), width=thickness)
    return img
    
# Задача 2
def change_color(img, color):
    image = img
    arr = {}
    width, height = img.size
    for x in range(width):
        for y in range(height):
            pixel_color = img.getpixel((x, y))
            if pixel_color not in arr.keys():
                arr.update({pixel_color:0})
            else:
                arr[pixel_color]+=1
    m = max(arr.values())
    keys = [key for key, value in arr.items() if value == m]
    for x in range(width):
        for y in range(height):
            if (image.getpixel((x, y)) == keys[0]):
                image.putpixel((x, y), tuple(color))
    return image
    
# Задача 3
def collage(img, N, M):
    w = img.size[0] * M
    h = img.size[1] * N
    collage = Image.new("RGB",(w,h))
    for x in range(M):
        for y in range(N):
            collage.paste(img,(img.size[0]*x,img.size[1]*y))
    return collage
