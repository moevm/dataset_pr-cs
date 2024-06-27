# Задача 1
def user_func(image, x0, y0, x1, y1, fill, width):
    draw = ImageDraw.Draw(image)
    draw.line((x0, y0, x1, y1), fill, width)
    return image

# Задача 2
def check_coords(image, x0, y0, x1, y1):
    height, width = image.height, image.width
    return not ((x0 >= x1) or (y0 >= y1) or (x0 < 0) or (y0 < 0) or (x1 >= width) or (y1 >= height))

def set_black_white(image, x0, y0, x1, y1):
    if check_coords(image, x0, y0, x1, y1) == 0:
        return image
    cropped_image = image.crop((x0, y0, x1, y1))
    cropped_image = cropped_image.convert("1")
    image.paste(cropped_image, (x0, y0))
    return image

# Задача 3
def find_rect_and_recolor(image, old_color, new_color):
    rect_coords = find_max_rect(image, old_color)
    if rect_coords == (0, 0, 0, 0):
        return image 
    arr = np.array(image)
    arr_slice = arr[rect_coords[1]:rect_coords[3] + 1, rect_coords[0]:rect_coords[2] + 1]
    mask = np.all(arr_slice == old_color, axis=-1) 
    arr_slice[mask] = new_color 
    return Image.fromarray(arr)
    
def find_max_rect(image, color):
    arr = np.array(image).tolist()
    for i in range(len(arr)):
        for j in range(len(arr[i])):
            arr[i][j] = int(arr[i][j] == list(color))
    arr = np.array(arr)
    for i in range(1, len(arr)):
        for j in range(len(arr[i])):
            if arr[i][j] == 0:
                arr[i][j] = 0
            else:
                arr[i][j] += arr[i - 1][j]
    max_space = 0
    coordinates = (0, 0, 0, 0)
    for i in range(len(arr)):
        space = 0
        for k in set(arr[i]):
            for j in range(len(arr[i])):
                if k <= arr[i][j]:
                    space += k
                if j == len(arr[i]) - 1 or arr[i][j + 1] < k:
                    if max_space < space:
                        max_space = space
                        coordinates = (j - space // k + 1, i - k + 1, j, i)
                    space = 0
    return coordinates
