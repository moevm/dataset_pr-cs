import numpy as np
import PIL
from PIL import Image, ImageDraw

# Задача 1
def triangle(img, x0, y0, x1, y1, x2, y2, thickness, color, fill_color):
    draw = ImageDraw.Draw(img) # объект для рисования на изображении
    points = [(x0, y0), (x1, y1), (x2, y2)] # список, содержащий координаты вершин
    if fill_color is None: # проверка на отстутствие цвета заливки
        korteg=None
    else:
        korteg=tuple(fill_color) # преобразование списка в кортеж 
    draw.polygon(points, outline=tuple(color), width=thickness, fill=korteg) # вызов метода для отрисовки треугольника
    return img
    

# Задача 2
def change_color(img, color):
    pixels = np.array(img) # преобразование в массив пикселей
    r, g, b = color # извлечение значений цветов

    # поиск самого часто встречающегося цвета
    # функция reshape(-1, 3) преобразует массив в двумерный массив, где каждая строка представляет один пиксель изображения
    # функция unique() находит все уникальные строки пикселей в массиве и возвращает их в порядке первого появления
    unique_colors, counts = np.unique(pixels.reshape(-1, 3), axis=0, return_counts=True) 
    most_common_color = unique_colors[np.argmax(counts)] # определение самого часто встречающегося цвета

    # замена самого часто встречающегося цвета на заданный цвет
    pixels[np.where((pixels == most_common_color).all(axis=2))] = color

    new_image = Image.fromarray(pixels) # преобразование в обьект изображения
    return new_image

# Задача 3
def collage(img, N, M):
    width, height = img.size # определение ширины и высоты исходного изображения
    # создание нового пустого изображания, размер которого позволит создавать повторные размещения
    new_image = Image.new(img.mode, (M * width, N * height))  

    for i in range(N):
        for j in range(M):
            # вставка исходного изображения
            new_image.paste(img, (j * width, i * height))

    return new_image

