from PIL import Image

def triangle(img, x0, y0, x1, y1, x2, y2, thickness, color, fill_color):
    new_img = img.copy()
    draw = ImageDraw.Draw(new_img)
    if fill_color is None:
        draw.polygon([(x0,y0), (x1, y1), (x2,y2)], outline=(color[0], color[1], color[2]), width=thickness)
    else:
        draw.polygon([(x0,y0), (x1, y1), (x2,y2)], fill=(fill_color[0], fill_color[1], fill_color[2]), outline=(color[0], color[1], color[2]), width=thickness)
    return new_img
    
def change_color(img, color):
    colors = img.getcolors(100000)
    colors.sort(reverse=True, key=lambda x: x[0])
    most_common_color = colors[0][1]
    new_img = img.copy()
    pixels = new_img.load()
    width, height = new_img.size
    for x in range(width):
        for y in range(height):
            if pixels[x, y] == most_common_color:
                pixels[x, y] = tuple(color)
    return new_img
    
def collage(img, n, m):
    width, height = img.size
    collage_width = width * m
    collage_height = height * n
    collage_img = Image.new('RGB', (collage_width, collage_height))
    for i in range(n):
        for j in range(m):
            collage_img.paste(img, (j * width, i * height))
    return collage_img
