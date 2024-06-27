class Figure:
    '''Поля объекта класс Figure:
    perimeter - периметр фигуры (в сантиметрах, целое положительное число)
    area - площадь фигуры (в квадратных сантиметрах, целое положительное число)
    color - цвет фигуры (значение может быть одной из строк: 'r', 'b', 'g')
    При создании экземпляра класса Figure необходимо убедиться, что переданные в конструктор параметры удовлетворяют требованиям, иначе выбросить исключение ValueError с текстом 'Invalid value'.
    '''
    def __init__(self, perimeter, area, color):
        if not(isinstance(perimeter, int) and isinstance(area, int) and color in ['r', 'g', 'b'] and perimeter > 0 and area > 0):
            raise ValueError('Invalid value')
        self.perimeter = perimeter
        self.area = area
        self.color = color

class Polygon(Figure):  # Наследуется от класса Figure
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
        if not(isinstance(angle_count, int) and isinstance(equilateral, bool) and isinstance(biggest_angle, int) and angle_count > 2 and biggest_angle > 0):
            raise ValueError('Invalid value')
        self.angle_count = angle_count
        self.equilateral = equilateral
        self.biggest_angle = biggest_angle

    def __str__(self):
        '''Преобразование к строке вида: Polygon: Периметр <периметр>, площадь <площадь>, цвет фигуры <цвет фигуры>, равносторонний <равносторонний>, прямоугольный <прямоугольный>.'''
        return f"Polygon: Периметр {self.perimeter}, площадь {self.area}, цвет фигуры {self.color}, количество углов {self.angle_count}, равносторонний {self.equilateral}, самый большой угол {self.biggest_angle}."

    def __add__(self):
        '''Сложение площади и периметра многоугольника. Возвращает число, полученное при сложении площади и периметра многоугольника.'''
        summ = 0
        summ = self.area + self.perimeter
        return summ
    def __eq__(self, obj):
        '''Метод возвращает True, если два объекта класса равны и False иначе. Два объекта типа Polygon равны, если равны их периметр, площадь и количество углов.'''
        if(self.area == obj.area and self.perimeter == obj.perimeter and self.angle_count == obj.angle_count):
            return True
        else:
            return False

class Circle(Figure):  # Наследуется от класса Figure
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
        if not(isinstance(radius, int) and isinstance(diametr, int) and radius > 0 and diametr == radius * 2):
            raise ValueError("Invalid value")
        self.radius = radius
        self.diametr = diametr

    def __str__(self):
        '''Преобразование к строке вида: Circle: Периметр <периметр>,  площадь <площадь>, цвет фигуры <цвет фигуры>, радиус <радиус>, диаметр <диаметр>.'''
        return f"Circle: Периметр {self.perimeter}, площадь {self.area}, цвет фигуры {self.color}, радиус {self.radius}, диаметр {self.diametr}."
    def __add__(self):
        '''Сложение площади и периметра окружности. Возвращает число, полученное при сложении площади и периметра окружности.'''
        summ = 0
        summ = self.area + self.perimeter
        return summ
    def __eq__(self, obj):
        '''Метод возвращает True, если два объекта класса равны и False иначе. Два объекта типа Circle равны, если равны их радиусы.'''
        if(self.radius == obj.radius):
            return True
        else:
            return False

class PolygonList(list): #– список многоугольников - наследуется от класса list.
    '''1. Вызвать конструктор базового класса.
   2. Передать в конструктор строку name и присвоить её полю name созданного объекта'''
    def __init__(self, name):
        super().__init__()
        self.name = name
    '''Переопределение метода append() списка. В случае, если p_object - многоугольник (объект класса Polygon), элемент добавляется в список, иначе выбрасывается исключение TypeError с текстом:  Invalid type <тип_объекта p_object>'''
    def append(self, p_object):
        if(isinstance(p_object, Polygon)):
            super().append(p_object)
        else:
            raise TypeError(f'Invalid type {p_object.__class__.__name__}')
    '''Вывести цвета всех многоугольников.'''
    def print_colors(self):
        for i in range(len(self)):
            print(f'{i+1} многоугольник: {self[i].color}')
    '''Вывести количество многоугольников. в списке'''
    def print_count(self):
        print(len(self))



class CircleList(list): #– список изогнутых фигур - наследуется от класса list.
    '''1. Вызвать конструктор базового класса.
    2. Передать в конструктор строку name и присвоить её полю name созданного объекта'''
    def __init__(self, name):
        super().__init__()
        self.name = name

    '''Переопределение метода extend() списка. В качестве аргумента передается итерируемый объект iterable, в случае, если элемент iterable - объект класса Circle, этот элемент добавляется в список, иначе не добавляется.'''
    def extend(self, iterable):
        for i in iterable:
            if(isinstance(i, Circle)):
                super().append(i)

    '''Вывести цвета всех изогнутых фигур.'''
    def print_colors(self):
        for i in range(len(self)):
            print(f'{i+1} окружность: {self[i].color}')

    '''Посчитать и вывести общую площадь всех окружностей.'''
    def total_area(self):
        summ = 0
        for i in range(len(self)):
            summ += self[i].area
        print(summ)
