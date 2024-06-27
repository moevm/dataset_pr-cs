class Figure:
    '''Поля объекта класс Figure:
    perimeter - периметр фигуры (в сантиметрах, целое положительное число)
    area - площадь фигуры (в квадратных сантиметрах, целое положительное число)
    color - цвет фигуры (значение может быть одной из строк: 'r', 'b', 'g')
    При создании экземпляра класса Figure необходимо убедиться, что переданные в конструктор параметры удовлетворяют требованиям, иначе выбросить исключение ValueError с текстом 'Invalid value'.     
    '''
    def __init__(self, perimeter, area, color):
        if((isinstance(perimeter, int) and perimeter > 0) and (isinstance(area, int) and area > 0) and (isinstance(color, str) and color in "rgb")):
            self.perimeter = perimeter
            self.area = area
            self.color = color
        else: raise ValueError("Invalid value")

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
        if((isinstance(angle_count, int) and angle_count > 2) and isinstance(equilateral, bool) and (isinstance(biggest_angle, int) and biggest_angle > 0)):
            super().__init__(perimeter, area, color)
            self.angle_count = angle_count
            self.equilateral = equilateral
            self.biggest_angle = biggest_angle
        else: raise ValueError("Invalid value")
    
    def __str__(self):
        return "Polygon: Периметр " + str(self.perimeter) + ", площадь " + str(self.area) + ", цвет фигуры " + self.color + ", количество углов " + str(self.angle_count) + ", равносторонний " + str(self.equilateral) + ", самый большой угол " + str(self.biggest_angle) + "."
    '''Преобразование к строке вида: Polygon: Периметр <периметр>, площадь <площадь>, цвет фигуры <цвет фигуры>, количество углов <кол-во углов>, равносторонний <равносторонний>, самый большой угол <самый большой угол>.'''
        
    def __add__(self):
        return self.perimeter + self.area
    '''Сложение площади и периметра многоугольника. Возвращает число, полученное при сложении площади и периметра многоугольника.'''
    
    def __eq__(self, other):
        return ((self.perimeter == other.perimeter) and (self.area == other.area) and (self.angle_count == other.angle_count))
    '''Метод возвращает True, если два объекта класса равны и False иначе. Два объекта типа Polygon равны, если равны их периметр, площадь и количество углов.'''
class Circle(Figure):
    def __init__(self, perimeter, area, color, radius, diametr):
        if((isinstance(radius, int) and radius > 0) and (isinstance(diametr, int) and (diametr == radius * 2))):
            super().__init__(perimeter, area, color)
            self.radius = radius
            self.diametr = diametr
        else: raise ValueError("Invalid value")
    
    def __str__(self):
        return  "Circle: Периметр " + str(self.perimeter) + ", площадь " + str(self.area) + ", цвет фигуры " + self.color + ", радиус " + str(self.radius) + ", диаметр " + str(self.diametr) + "."
    '''Преобразование к строке вида: Circle: Периметр <периметр>,  площадь <площадь>, цвет фигуры <цвет фигуры>, радиус <радиус>, диаметр <диаметр>.'''
    
    def __add__(self):
        return self.area + self.perimeter
    '''Сложение площади и периметра окружности. Возвращает число, полученное при сложении площади и периметра окружности.'''
    
    def __eq__(self, other):
        return (self.radius == other.radius)
    '''Метод возвращает True, если два объекта класса равны и False иначе. Два объекта типа Circle равны, если равны их радиусы.'''
    
class PolygonList(list):
    def __init__(self, name):
        super().__init__()
        self.name = name
        '''1. Вызвать конструктор базового класса. 
           2. Передать в конструктор строку name и присвоить её полю name созданного объекта'''
           
    def append(self, p_object):
        if(isinstance(p_object, Polygon)):
            super().append(p_object)
        else: raise TypeError("Invalid type " +type(object))
        '''Переопределение метода append(p_object) списка. В случае, если p_object - многоугольник (объект класса Polygon), элемент добавляется в список, иначе выбрасывается исключение TypeError с текстом:  Invalid type <тип_объекта p_object>'''
            
    def print_colors(self):
        for i in range(len(self)):
            print(str(i+1) + " многоугольник: " + self[i].color)
        '''Вывести цвета всех многоугольников.'''
            
    def print_count(self):
        print(len(self))
        '''Вывести количество многоугольников. в списке'''

class CircleList(list):
    def __init__(self, name):
        super().__init__()
        self.name = name
        '''1. Вызвать конструктор базового класса. 
           2. Передать в конструктор строку name и присвоить её полю name созданного объекта'''
           
    def extend(self, iterable):
        for i in iterable:
            if(isinstance(i, Circle)):
                super().append(i)
        '''Переопределение метода extend() списка. В качестве аргумента передается итерируемый объект iterable, в случае, если элемент iterable - объект класса Circle, этот элемент добавляется в список, иначе не добавляется.'''
        
    def print_colors(self):
        for i in range(len(self)):
            print(str(i+1) + " окружность: " + self[i].color)
        '''Вывести цвета всех изогнутых фигур.'''
        
    def total_area(self):
        sum = 0
        for i in  self:
            sum += i.area
        print(sum)
        '''Посчитать и вывести общую площадь всех окружностей.'''