import PIL
import numpy as np

# Задача 1
def triangle(img, x0, y0, x1, y1, x2, y2, thickness, color, fill_color):
    drawing = ImageDraw.Draw(img)
    
    if fill_color:
        drawing.polygon([(x0, y0), (x1, y1), (x2, y2)], fill=tuple(fill_color), outline=tuple(color), width=thickness)
    else:
        drawing.polygon([(x0, y0), (x1, y1), (x2, y2)], outline=tuple(color), width=thickness)
    
    return img

# Задача 2
def change_color(img, color):
    pixels = np.array(img)
    colors, counts = np.unique(pixels.reshape(-1, pixels.shape[2]), axis = 0, return_counts = True)
    
    mc_color_index = np.argmax(counts)
    mc_color = colors[mc_color_index]
    
    pixels[(pixels == mc_color).all(axis = 2)] = color
    new_img = Image.fromarray(pixels)
    
    return new_img

# Задача 3
def collage(img, N, M):
    img_width, img_height = img.size
    
    collage_height = N * img_height
    collage_width = M * img_width
    collage = Image.new("RGB", (collage_width, collage_height))
    
    for y in range(N):
        for x in range(M):
            collage.paste(img, (x * img_width, y * img_height))
    
    return collage