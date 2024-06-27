import PIL

def triangle(img, x0, y0, x1, y1, x2, y2, thickness, color, fill_color):
    draw = ImageDraw.Draw(img)
    points = ((x0, y0), (x1, y1), (x2, y2))
    if fill_color is not None:
        draw.polygon(points, fill=tuple(fill_color),outline= tuple(color), width=thickness)
    else:
        draw.polygon(points, outline=tuple(color), width=thickness)
    return img

def change_color(img, color):
    colors = {}
    px = img.load()
    for x in range(img.width):
        for y in range(img.height):
            coordinate = x, y
            if colors.get(img.getpixel(coordinate), 0) != 0:
                colors[img.getpixel(coordinate)] += 1
            else:
                colors[img.getpixel(coordinate)] = 1

    for key, value in colors.items():
        if value == max(colors.values()):
            maxcolor = key

    for x in range(img.width):
        for y in range(img.height):
            coordinate = x, y
            if img.getpixel(coordinate) == maxcolor:
                px[coordinate] = tuple(color)
    return img

def collage(img, N, M):
    width, height = img.size
    collage_width = width * M
    collage_height = height * N
    collage = Image.new('RGB', (collage_width, collage_height))
    for y in range(N):
        for x in range(M):
            collage.paste(img, (x * width, y * height))
    return collage