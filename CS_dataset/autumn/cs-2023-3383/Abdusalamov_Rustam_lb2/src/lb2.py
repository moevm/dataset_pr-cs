import PIL
import numpy as np

def triangle(img, x0, y0, x1, y1, x2, y2, thickness, color, fill_color):
    drawing = ImageDraw.Draw(img)
    if fill_color:
        drawing.polygon([(x0, y0), (x1, y1), (x2, y2)], fill=tuple(fill_color), outline=tuple(color), width=thickness)
    else:
        drawing.polygon([(x0, y0), (x1, y1), (x2, y2)], outline=tuple(color), width=thickness)
    return img

def change_color(img, color):
    img_array = np.array(img)
    colors, counts = np.unique(img_array.reshape(-1, img_array.shape[2]), axis=0, return_counts=True)
    most_common_color_index = np.argmax(counts)
    most_common_color = colors[most_common_color_index]
    img_array[(img_array == most_common_color).all(axis=2)] = color
    new_img = Image.fromarray(img_array)
    return new_img

def collage(img, N, M):
    img_width, img_height = img.size
    collage_height = N * img_height
    collage_width = M * img_width
    collage_img = Image.new("RGB", (collage_width, collage_height), 'white')
    for y in range(N):
        for x in range(M):
            collage_img.paste(img, (x * img_width, y * img_height))
    return collage_img

