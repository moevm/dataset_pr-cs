from PIL import Image, ImageDraw
import numpy as np

def triangle(img, x0, y0, x1, y1, x2, y2, thickness, color, fill_color):
    color = tuple(color)
    if fill_color != None:
    	fill_color = tuple(fill_color)
    draw = ImageDraw.Draw(img)
    points = [(x0, y0), (x1, y1), (x2, y2)]
    draw.polygon(points, fill = fill_color, outline = color, width=thickness)
    return img

def change_color(img, color):
    img_array = np.array(img)
    target_color = tuple(color)
    colors, counts = np.unique(img_array.reshape(-1, 3), axis=0, return_counts=True)
    most_common_color = colors[np.argmax(counts)]
    img_array[np.where((img_array == most_common_color).all(axis=-1))] = target_color
    return Image.fromarray(img_array)

def collage(img, N, M):
    width, height = img.size 
    collage_img = Image.new('RGB', (M * width, N * height))
    for i in range(N):
        for j in range(M):
            collage_img.paste(img, (j * width, i * height))
    return collage_img

    