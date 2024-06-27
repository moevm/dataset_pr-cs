from PIL import Image, ImageDraw

def triangle(img, x0, y0, x1, y1, x2, y2, thickness, color, fill_color=None):
    draw = ImageDraw.Draw(img)
    coordinates = [(x0, y0), (x1, y1), (x2, y2)]
    if fill_color:
        draw.polygon(coordinates, fill = tuple(fill_color), outline = tuple(color), width = thickness)
    else: 
        draw.polygon(coordinates, outline = tuple(color), width = thickness)
    return img

def change_color(img, color=None):
    if img.size[0] == 0 or img.size[1] == 0 or color == None:
        return img
    colour = {}
    pixels = img.load()
    for pixel in img.getdata():
        if pixel in colour:
            colour[pixel] += 1
        else:
            colour[pixel] = 1
    sortcolour = sorted([(v,k) for (k,v) in colour.items()])
    res = [(v,k) for (k,v) in sortcolour[-1:]]
    for i in range(img.size[0]):
        for j in range(img.size[1]):
            if pixels[i,j]==res[0][0]:
                pixels[i,j]=tuple(color)
    return img

def collage(img, N, M):
    a = img.size
    img1 = img.crop((0, 0, a[0], a[1]))
    imgnew = Image.new("RGB", (a[0] * M, a[1] * N))
    for i in range(M):
        for j in range(N):
            imgnew.paste((img1), (i*a[0], j*a[1]))
    return imgnew
