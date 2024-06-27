from PIL import Image,ImageDraw
# Задача 1
def triangle(img, x0, y0, x1, y1, x2, y2, thickness, color, fill_color):
    drawing = ImageDraw.Draw(img)
    if fill_color:
        drawing.polygon([(x0, y0), (x1, y1), (x2, y2)],width=thickness, outline=tuple(color), fill=tuple(fill_color) )
    else:
        drawing.polygon([(x0, y0), (x1, y1), (x2, y2)],width=thickness, outline=tuple(color) )
    return img
# Задача 2
def change_color(img,color):
    size=img.size
    img.load()
    colors={}
    for x in range(size[0]):
        for y in range(size[1]):
            pixel_color=img.getpixel((x,y))
            if not pixel_color in colors.keys():
                colors[pixel_color]=1
            else:
                colors[pixel_color]+=1
    M=max(colors.values())
    m_color=(0,0,0)
    for x in colors.keys():
        if colors[x]==M:
            m_color=x
    for  x in range(size[0]):
        for y in range(size[1]):
            pixel_color=img.getpixel((x,y))
            if pixel_color==m_color:
                img.putpixel((x,y),tuple(color))
    return img


# Задача 3

def collage(img, N, M):
    img.load()
    size = img.size
    new_image = Image.new("RGB", (size[0] * M, size[1] * N), "white")
    for m in range(M):
        for n in range(N):
            new_image.paste(img,(size[0]*m,size[1]*n))
    return new_image



