from PIL import Image, ImageDraw

import numpy as np

# Функция 1

#Функция user_func принимает изображение image и координаты двух точек (x0, y0) и (x1, y1), а также цвет fill и ширину линии width
def user_func(image, x0, y0, x1, y1, fill, width):
    
    draw = ImageDraw.Draw(image)
    
    # Функция использует библиотеку PIL (Python Imaging Library) для рисования линии между заданными точками на изображении
    draw.line(((x0, y0), (x1, y1)), fill, width)
    
    #Функция возвращает измененное изображение
    return image

# Функция 2

#Функция check_coords принимает изображение image и координаты двух точек (x0, y0) и (x1, y1)
def check_coords(image, x0, y0, x1, y1):
    
    size_y = image.size[1]
    
    size_x = image.size[0]
    
    #Функция проверяет, что все координаты положительны (больше нуля), а также что (x1, y1) больше (x0, y0) и находятся в пределах размеров изображения
    if(x0 > 0 and y0 > 0 and x1 > 0 and y1 > 0) and (x1 > x0 and y1 > y0) and (x1 < size_x and y1 < size_y):
        
        #Если все условия выполняются, функция возвращает True, иначе - False
        return True
        
    else:
        
        return False
        
#Функция set_black_white принимает изображение image и координаты двух точек (x0, y0) и (x1, y1)        
def set_black_white(image, x0, y0, x1, y1):
    
    #Функция использует функцию check_coords для проверки правильности координат
    if check_coords(image, x0, y0, x1, y1):
        
        #сли координаты верны, функция обрезает изображение по данным координатам, конвертирует его в черно-белый формат и заменяет обрезанную часть исходного изображения на новое черно-белое изображение
        img_convertd = image.crop((x0, y0, x1, y1))
        
        img_convertd = img_convertd.convert("1")
        
        image.paste(img_convertd, (x0, y0))
    
    #Возвращается измененное изображение.    
    return image

# Функция 3

#Функция find_rect_and_recolor принимает изображение image, старый цвет old_color и новый цвет new_color
def find_rect_and_recolor(image, old_color, new_color):
    
    #Функция преобразует изображение в массив numpy, затем проверяет каждый пиксель на соответствие старому цвету и заменяет его на 1, если цвет соответствует, или на 0 в противном случае
    color = list(old_color)
    
    array = np.array(image).tolist()
    
    for i in range(len(array)):
        
        for j in range(len(array[i])):
            
            array[i][j] = int(array[i][j] == color)
            
    array = np.array(array)
    
    for i in range(1, len(array)):
        
        for j in range(len(array[i])):
            
            if array[i][j] == 1:
                
                array[i][j] += array[i-1][j]
                
    max_size = 0
    
    coords = (0, 0, 0, 0)
    
    for i in range(len(array)):
        
        curr_size = 0
        
        last_j = 0
        
        for j in range(len(array[i])-1):
            
            curr_size += array[i][j]
            
            if curr_size > max_size:
                
                max_size = curr_size
                
                coords = (j - (max_size // array[i][j]) + 1, i - array[i][j] + 1, j, i)
                
            if array[i][j] != array[i][j+1]:
                
                curr_size = 0
                
            last_j = j
            
        if array[i][last_j] == array[i][last_j+1]:
            
            curr_size += array[i][last_j+1]
            
            if curr_size > max_size:
                
                max_size = curr_size
                
                coords = (last_j - (max_size // array[i][last_j+1]) + 1, i - array[i][last_j+1] + 1, last_j+1, i)
                
    array = np.array(image).tolist()
    
    for i in range(coords[1], coords[3]+1):
        
        for j in range(coords[0], coords[2]+1):
            
            array[i][j] = new_color
            
    image = Image.fromarray(np.uint8(array))
    
    #Затем функция заменяет цвет пикселей в найденном прямоугольнике на новый цвет и возвращает измененное изображение
    return image