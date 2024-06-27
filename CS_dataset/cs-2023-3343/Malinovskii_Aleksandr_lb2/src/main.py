import numpy as np
from PIL import Image, ImageDraw

# Задача 1
def user_func(image, x0, y0, x1, y1, fill, width):
    draw=ImageDraw.Draw(image)
    draw.line((x0,y0,x1,y1),fill=(fill),width=width)
    return image

# Задача 2
def check_coords(image, x0, y0, x1, y1):
    if  (x0 < x1 and y0 < y1 and x0 > 0 and y0 > 0
        and x1 < image.width and y1 < image.height):
        return True
def set_black_white(image, x0, y0, x1, y1):
    if check_coords(image,x0,y0,x1,y1):
        area=image.crop((x0,y0,x1,y1))
        converted_area=area.convert("1")
        image.paste(converted_area, (x0,y0,x1,y1))
    return image

# Задача 3
def find_largest_rect(image, color):
    # преобразование изображения в матрицу
    array=np.array(image).tolist()
    for i in range(len(array)):
        for j in range(len(array[i])):
            # устанавливаем значение 1, если пиксель имеет искомый цвет
            array [i][j]=int(array[i][j]==list(color))
    array=np.array(array)

    # cчитаем максимальную высоту
    for i in range (1,len(array)):
        for j in range(len(array[i])):
            if array[i][j]!=0:
                array[i][j]+=array[i-1][j]
    #ищем максимальную площадь
    max_area=0
    coordinates=(0,0,0,0)
    for i in range(len(array)):
        temp_area=0
        for k in set(array[i]):
            for j in range(len(array[i])):
                if k<=array[i][j]:
                    temp_area+=k

                if j==len(array[i])-1 or array[i][j+1]<k :
                    if max_area<temp_area:
                        max_area=temp_area
                        coordinates=(j-temp_area//k+1,i-k+1,j,i)
                    area=0
    return coordinates

def find_rect_and_recolor(image, old_color, new_color):
    coords=find_largest_rect(image,old_color)
    arr=np.array(image)
    arr[coords[1]:coords[3]+1, coords[0]:coords[2]+1,:3]=list(new_color)
    image =Image.fromarray(arr)
    return image
