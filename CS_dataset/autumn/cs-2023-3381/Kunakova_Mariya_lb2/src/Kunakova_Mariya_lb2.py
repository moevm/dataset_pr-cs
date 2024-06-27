from PIL import Image, ImageDraw
def triangle(img, x0, y0, x1, y1, x2, y2, thickness, color, fill_color):
    drawing = ImageDraw.Draw(img)
    if fill_color:
        fill_color = tuple(fill_color)
    drawing.polygon(((x0, y0), (x1, y1), (x2, y2)), fill_color, tuple(color), thickness)
    return img
    pass
def change_color(img, color):
    colors = {}
    for x in range(img.size[0]):
        for y in range(img.size[1]):
            if img.getpixel((x, y)) in colors:
                colors[img.getpixel((x, y))] += 1
            else:
                colors[img.getpixel((x, y))] = 1
    most_color = max(colors, key=colors.get)
    drawing = ImageDraw.Draw(img)
    for x in range(img.size[0]):
        for y in range(img.size[1]):
            if img.getpixel((x, y)) == most_color:
                drawing.point((x, y), tuple(color))
    return img
    pass
def collage(img, N, M):
    width, height = img.size
    img_collage = Image.new("RGB", (width * M, height * N), "black")
    coordinates = []
    for i in range(M):
        for j in range(N):
            coordinates.append((i * width, j * height))
    for i in range(len(coordinates)):
        img_collage.paste(img, coordinates[i])
    return img_collage
    pass