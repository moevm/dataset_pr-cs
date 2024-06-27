from PIL import Image,ImageDraw

def triangle(img, x0, y0, x1, y1, x2, y2, thickness, color, fill_color):
    img_draw = ImageDraw.Draw(img)
    if fill_color != None:
        img_draw.polygon([(x0, y0), (x1, y1), (x2, y2)], fill=tuple(fill_color), outline=tuple(color), width = thickness)
    else:
        img_draw.polygon([(x0, y0), (x1, y1), (x2, y2)], outline=tuple(color), width = thickness)
    return img

def change_color(img, color):
    cop = img.copy()
    l = cop.load()
    s = cop.size
    colors = dict()
    for x in range(s[0]):
        for y in range(s[1]):
            if l[x, y] in colors:
                colors[l[x, y]] += 1
            else:
                colors[l[x, y]] = 1
    colors_top = sorted(colors.items(), key = lambda x:x[1])[-1][0]
    for x in range(s[0]):
        for y in range(s[1]):
            if l[x, y] == colors_top:
                l[x, y] = tuple(color)
    return cop

def collage(img, N, M):
    s = img.size
    result = Image.new("RGB", (s[0] * M, s[1] * N), "white")
    for x in range(0, s[0] * M, s[0]):
        for y in range(0, s[1] * N , s[1]):
            result.paste(img, (x, y))
    return result