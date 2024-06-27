class Figure:
    '''Поля объекта класс Figure:
    perimeter - периметр фигуры (в сантиметрах, целое положительное число)
    area - площадь фигуры (в квадратных сантиметрах, целое положительное число)
    color - цвет фигуры (значение может быть одной из строк: 'r', 'b', 'g')
    При создании экземпляра класса Figure необходимо убедиться, что переданные в конструктор параметры удовлетворяют требованиям, иначе выбросить исключение ValueError с текстом 'Invalid value'.     
    '''
    def __init__(self, perimeter, area, color):
        if (isinstance(perimeter, int)) and (perimeter > 0):
            self.perimeter = perimeter
        else: raise ValueError('Invalid value')
        if(isinstance(area, int)) and (area > 0):
            self.area = area
        else: raise ValueError('Invalid value')
        if (color == 'r') or (color == 'b') or (color == 'g'):
            self.color = color
        else: raise ValueError('Invalid value')
        
    def __initList__(self, name):
        self.name = name

class Polygon(Figure): #Наследуется от класса Figure
    '''Поля объекта класс Polygon:
    perimeter - периметр фигуры (в сантиметрах, целое положительное число)
    area - площадь фигуры (в квадратных сантиметрах, целое положительное число)
    color - цвет фигуры (значение может быть одной из строк: 'r', 'b', 'g')
    angle_count - количество углов (целое положительное значение, больше 2)
    equilateral - равносторонний (значениями могут быть или True, или False)
    biggest_angle - самый большой угол (или любой угол, если многоугольник равносторонний) (в градусах, целое положительное число)
    При создании экземпляра класса Polygon необходимо убедиться, что переданные в конструктор параметры удовлетворяют требованиям, иначе выбросить исключение ValueError с текстом 'Invalid value'. 
    '''
    def __init__(self, perimeter, area, color, angle_count, equilateral, biggest_angle):
        super().__init__(perimeter, area, color)
        if (isinstance(angle_count, int)) and (angle_count > 2):
            self.angle_count = angle_count
        else: raise ValueError('Invalid value')
        if isinstance(equilateral, bool):
            self.equilateral = equilateral
        else: raise ValueError('Invalid value')
        if (isinstance(biggest_angle, int)) and (biggest_angle > 0):
            self.biggest_angle = biggest_angle
        else: raise ValueError('Invalid value')

    def __str__(self):
        '''Преобразование к строке вида: Polygon: Периметр <периметр>, площадь <площадь>, цвет фигуры <цвет фигуры>, количество углов <кол-во углов>, равносторонний <равносторонний>, самый большой угол <самый большой угол>.'''
        return "Polygon: Периметр " + str(self.perimeter) + ", площадь " + str(self.area) + ", цвет фигуры " + str(self.color) + ", количество углов " + str(self.angle_count) + ", равносторонний " + str(self.equilateral) + ", самый большой угол " + str(self.biggest_angle) + "."

    def __add__(self):
        '''Сложение площади и периметра многоугольника. Возвращает число, полученное при сложении площади и периметра многоугольника.'''
        return self.area + self.perimeter

    def __eq__(self, other): 
        '''Метод возвращает True, если два объекта класса равны и False иначе. Два объекта типа Polygon равны, если равны их периметр, площадь и количество углов.'''
        return (self.perimeter == other.perimeter) and (self.area == other.area) and (self.angle_count == other.angle_count)

class Circle(Figure): #Наследуется от класса Figure
    '''Поля объекта класс Circle:
    perimeter - периметр фигуры (в сантиметрах, целое положительное число)
    area - площадь фигуры (в квадратных сантиметрах, целое положительное число)
    color - цвет фигуры (значение может быть одной из строк: 'r', 'b', 'g')
    radius - радиус (целое положительное число)
    diametr - диаметр (целое положительное число, равен двум радиусам)
    При создании экземпляра класса Circle необходимо убедиться, что переданные в конструктор параметры удовлетворяют требованиям, иначе выбросить исключение ValueError с текстом 'Invalid value'.
    '''
    def __init__(self, perimeter, area, color, radius, diametr):
        super().__init__(perimeter, area, color)
        if (isinstance(radius, int)) and (radius > 0):
            self.radius = radius
        else: raise ValueError('Invalid value')
        if (isinstance(diametr, int)) and (diametr == 2 * radius) and (diametr > 0):
            self.diametr = diametr
        else: raise ValueError('Invalid value')

    def __str__(self):
        '''Преобразование к строке вида: Circle: Периметр <периметр>,  площадь <площадь>, цвет фигуры <цвет фигуры>, радиус <радиус>, диаметр <диаметр>.'''
        return "Circle: Периметр " + str(self.perimeter) + ", площадь " + str(self.area) + ", цвет фигуры " + str(self.color) + ", радиус " + str(self.radius) + ", диаметр " + str(self.diametr) + "."

    def __add__(self): 
        '''Сложение площади и периметра окружности. Возвращает число, полученное при сложении площади и периметра окружности.'''
        return self.area + self.perimeter

    def __eq__(self, other):
        '''Метод возвращает True, если два объекта класса равны и False иначе. Два объекта типа Circle равны, если равны их радиусы.'''
        return self.radius == other.radius

class PolygonList(Polygon, list): # – список многоугольников - наследуется от класса list.
    #Конструктор:
    '''1. Вызвать конструктор базового класса. 
    2. Передать в конструктор строку name и присвоить её полю name созданного объекта'''
    def __init__(self, name):
        super().__initList__(name)

    def append(self, p_object):
        '''Переопределение метода append() списка. В случае, если p_object - многоугольник (объект класса Polygon), элемент добавляется в список, иначе выбрасывается исключение TypeError с текстом:  Invalid type <тип_объекта p_object>'''
        if isinstance(p_object, Polygon):
            super().append(p_object)
        else: raise TypeError(f"Invalid type {type(p_object)}")

    def print_colors(self): 
        '''Вывести цвета всех многоугольников.'''
        for i in range(len(self)):
            print(f"{i + 1} многоугольник: {self[i].color}")

    def print_count(self): 
        '''Вывести количество многоугольников в списке'''
        print(len(self))

class CircleList(Circle, list): #– список изогнутых фигур - наследуется от класса list.
    #Конструктор:
    '''1. Вызвать конструктор базового класса. 
    2. Передать в конструктор строку name и присвоить её полю name созданного объекта'''
    def __init__(self, name):
        super().__initList__(name)

    def extend(self, iterable):
        '''Переопределение метода extend() списка. В качестве аргумента передается итерируемый объект iterable, в случае, если элемент iterable - объект класса Circle, этот элемент добавляется в список, иначе не добавляется.'''
        for i in iterable:
            if isinstance(i, Circle):
                super().append(i)

    def print_colors(self): 
        '''Вывести цвета всех изогнутых фигур.'''
        for i in range(len(self)):
            din = self[i]
            print(f"{i + 1} окружность: {din.color}")

    def total_area(self): 
        '''Посчитать и вывести общую площадь всех окружностей.'''
        big_area = 0;
        for i in self:
            big_area += i.area
        print(big_area)