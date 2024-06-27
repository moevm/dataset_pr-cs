from PIL import Image, ImageDraw
# Задача 1
def triangle(img, x0, y0, x1, y1, x2, y2, thickness, color, fill_color):
    triangle = ImageDraw.Draw(img)
    if fill_color != None:
        triangle.polygon(xy=[(x0,y0), (x1, y1), (x2,y2)], fill = tuple(fill_color), width=thickness, outline=tuple(color))
    else:
        triangle.polygon(xy=[(x0,y0), (x1, y1), (x2,y2)], width=thickness, outline=tuple(color))
    return img

# Задача 2
def change_color(img, color):
    changer = ImageDraw.Draw(img)
    pixels = img.load()
    pixels = [pixels[x,y] for x in range(img.size[0]) for y in range(img.size[1])]
    unique_pixels = list(set(pixels))
    res = []
    for i in range(len(unique_pixels)):
        k = 0
        for t in range(len(pixels)):
            if unique_pixels[i] == pixels[t]:
                k += 1
        res.append([k, unique_pixels[i]])
    res = max(res)[1]
    
    for x in range(img.size[0]):
        for y in range(img.size[1]):
            if pixels[x*img.size[1]+y] == res:
                changer.point((x, y), tuple(color))
    return img

# Задача 3
def collage(img, N, M):
    new_image = Image.new("RGB", (img.size[0]*M, img.size[1]*N))
    for x in range(new_image.size[0]):
        for y in range(new_image.size[1]):
            new_image.paste(img, (x*img.size[0], y*img.size[1]))
    return new_image

