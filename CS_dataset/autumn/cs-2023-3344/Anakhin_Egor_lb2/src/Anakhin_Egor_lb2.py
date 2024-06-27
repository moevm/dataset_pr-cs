from PIL import Image, ImageDraw

# Задача 1
def triangle(img, x0, y0, x1, y1, x2, y2, thickness, color, fill_color):
    
    draw = ImageDraw.Draw(img)
    coords = [(x0, y0), (x1, y1), (x2, y2)]
    if fill_color:
        draw.polygon(coords, width=thickness, outline=tuple(color), fill=tuple(fill_color))
    else:
        draw.polygon(coords, width=thickness, outline=tuple(color))
    return img

# Задача 2
def change_color(img, color):
    
    img_copy = img.copy()
    x_size, y_size = img.size
    colors = {}
    
    for x in range(x_size):
        for y in range(y_size):
            pixel_color = img.getpixel((x, y))
            if pixel_color not in colors:
                colors[pixel_color] = 0
            colors[pixel_color] += 1
    
    max_color_count = max(colors.values())
    color_name = ''
    
    for colorm in colors:
        if colors[colorm] == max_color_count:
            color_name = colorm
    
    for x in range(x_size):
        for y in range(y_size):
            if img.getpixel((x, y)) == color_name:
                img_copy.putpixel((x, y), tuple(color))
    
    return img_copy

# Задача 3
def collage(img, N, M):
    
    width, height = img.size
    new_img = Image.new("RGB", (width*M, height*N))
    
    for i in range(M):
        for j in range(N):
            new_img.paste(img, (width*i, height*j))
            
    return new_img
