class Figure:
    clr = "rbg"
    def __init__(self, perimeter, area, color):
        if not isinstance(perimeter, int) or not isinstance(area, int) or (color not in self.clr) or perimeter <= 0 or area <= 0:
            raise ValueError('Invalid value')
        self.perimeter = perimeter
        self.area = area
        self.color = color
class Polygon(Figure): #Наследуется от класса Figure
    def __init__(self, perimeter, area, color, angle_count, equilateral, biggest_angle):
        super().__init__(perimeter, area, color)
        if not isinstance(angle_count, int) or not isinstance(equilateral, bool) or not isinstance(biggest_angle, int) or angle_count <= 2 or biggest_angle <= 0 or angle_count <= 0 or biggest_angle < 0:
            raise ValueError('Invalid value')
        self.angle_count = angle_count
        self.equilateral = equilateral
        self.biggest_angle = biggest_angle
    def __str__(self):
        return f'Polygon: Периметр {self.perimeter}, площадь {self.area}, цвет фигуры {self.color}, количество углов {self.angle_count}, равносторонний {self.equilateral}, самый большой угол {self.biggest_angle}.'
    def __add__(self):
        summ = self.perimeter + self.area 
        return summ
    def __eq__(self, obj):
        if (self.area == obj.area) and (self.perimeter == obj.perimeter) and (self.angle_count == obj.angle_count):
            return True
        else:
            return False
class Circle(Figure):
    def __init__(self, perimeter, area, color, radius, diametr):
        super().__init__(perimeter, area, color)
        if not isinstance(radius, int) or not isinstance(diametr, int) or diametr <= 0 or (diametr != 2 * radius) or radius <= 0:
            raise ValueError('Invalid value')
        self.radius = radius
        self.diametr = diametr
    def __str__(self):
        return f'Circle: Периметр {self.perimeter}, площадь {self.area}, цвет фигуры {self.color}, радиус {self.radius}, диаметр {self.diametr}.'
    def __add__(self):
        summ = self.perimeter + self.area 
        return summ
    def __eq__(self, obj):
        if (self.radius == obj.radius) and (self.diametr == obj.diametr):
            return True
        else:
            return False
class PolygonList(list):
    def __init__(self, name):
        super().__init__()
        self.name = name
    def append(self, p_object):
        if isinstance(p_object, Polygon):
            super().append(p_object)
        else:
            raise TypeError(f'Invalid type {type(p_object).__name__}')
    def print_colors(self):
        for i in range(len(self)):
            print(f'{1 + i} многоугольник: {self[i].color}')
    def print_count(self):
        print(len(self))
class CircleList(list):
    def __init__(self, name):
        super().__init__()
        self.name = name
    def extend(self, iterable):
        for el in iterable:
            if isinstance(el, Circle):
                self.append(el)
    def print_colors(self):
        for i in range(len(self)):
            print(f'{1 + i} окружность: {self[i].color}')
    def total_area(self):
        smm = 0
        for i in self:
            smm += i.area
        print(smm)
