from PIL import Image, ImageDraw


# Задача 1
def list_to_tuple(obj):
    if type(obj) == list:
        obj = tuple(obj)
    return obj
    
def triangle(img, x0, y0, x1, y1, x2, y2, thickness, color, fill_color):
    draw = ImageDraw.Draw(img)
    draw.polygon(((x0, y0), (x1, y1), (x2, y2)),list_to_tuple(fill_color),list_to_tuple(color),thickness)
    return img

# Задача 2
def change_color(img, color):
    array_image = np.array(img)
    color = np.array(color)
    array_uniq,count = np.unique(array_image.reshape(-1, 3), return_counts=True,axis=0)

    index_frequent_color = np.argmax(count)

    most_frequent_color = array_uniq[index_frequent_color]
    for i in range(len(array_image)):
        for j in range(len(array_image[i])):
            if np.array_equal(array_image[i, j], most_frequent_color):
                array_image[i, j] = color

    image_change = Image.fromarray(array_image)
    return image_change
            
    

# Задача 3
def collage(img, N, M):
    img_array = np.array(img)
    collage_array = np.tile(img_array,(N,M,1))
    collage_image = Image.fromarray(collage_array)
    return collage_image
        

