from PIL import Image,ImageDraw
import numpy as np

def user_func(image, x0, y0, x1, y1, fill, width):
    drawing = ImageDraw.Draw(image)
    drawing.line(((x0, y0), (x1, y1)), fill, width)
    return image

def check_coords(image, x0, y0, x1, y1):
    if (x0 > x1 or y0 > y1):
        return False
    if (x0 < 0 or y0 < 0):
        return False
    if (image.width < x1 or image.height < y1):
        return False
    return True

def set_black_white(image, x0, y0, x1, y1):
    if (not(check_coords(image, x0, y0, x1, y1))):
        return image
    colorless_image = image.crop((x0, y0, x1, y1))
    colorless_image = colorless_image.convert("1")
    image.paste(colorless_image,(x0, y0, x1, y1))
    return image

def count_max_area(pixels, max_area, i, j):
    value = pixels[i][j]
    x1 = j
    y1 = i
    if max_area == 0:
        x0 = x1
        y0 = y1
        return x0, y0, x1, y1
    x0 = x1 - (max_area // value) + 1
    y0 = i - value + 1
    return x0, y0, x1, y1

def get_largest_rectangle(image, color):
    #Преобразование изображения в массив RGB цветов
    color = list(color)
    pixels=np.array(image).tolist()

    #Обнуление ячеек, отличных от требуемого цвета
    for i in range(len(pixels)):
        for j in range(len(pixels[i])):
            pixels[i][j] = 1 if pixels[i][j] == color else 0
    pixels=np.array(pixels)

    #Сохранение в ячейках числа непрерывных элементов
    #необходимого цвета, находящихся выше в том же столбце
    for i in range (1,len(pixels)):
        for j in range(len(pixels[i])):
            if pixels[i][j] == 1:
                pixels[i][j] += pixels[i-1][j]

    max_area = 0
    x0 = y0 = x1 = y1 = -1

    #Вычисление координат самого большого прямоугольника заданного цвета 
    for i in range(len(pixels)):
        temp = 0
        for j in range(len(pixels[i])-1):
            #Вычисление координат прямоугольника
            temp += pixels[i][j]
            if temp > max_area:
                max_area = temp
                x0, y0, x1, y1 = count_max_area(pixels,max_area,i,j)

            #Обнуление размера при изменении цвета следущего элемента
            if pixels[i][j] != pixels[i][j+1]:
                temp = 0

        #Случай, когда пиксель нужного цвета единственный и
        #находится в самой правой позиции
        if max_area == 0:
            max_area = pixels[i][len(pixels[i])-1]
            x0, y0, x1, y1 = count_max_area(pixels,max_area,i,len(pixels[i])-1)

        #Проверка равенства двух предпоследних символов в строке
        if pixels[i][len(pixels[i])-1] == pixels[i][len(pixels[i])-2]:
            temp += pixels[i][len(pixels[i])-1]
            if temp > max_area:
                max_area = temp
                x0, y0, x1, y1 = count_max_area(pixels,max_area,i,len(pixels[i])-1)
    
    return (x0,y0,x1,y1)

def find_rect_and_recolor(image, color, new_color):
    coords=get_largest_rectangle(image,color)

    #Проверка на присутствие запрашиваемого цвета в изображении
    if any([i == -1 for i in coords]):
        return image
    
    #Перекраска изображения
    pixels=np.array(image).tolist()
    for i in range(len(pixels)):
        for j in range(len(pixels[i])):
            if coords[1] <= i <= coords[3] and coords[0] <= j <= coords[2]:
                pixels[i][j] = new_color
    image = Image.fromarray(np.uint8(pixels)) 
    return image