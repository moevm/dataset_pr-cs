class Figure:
    def __init__(self, perimeter, area, color):
        if not isinstance(perimeter, int) or not isinstance(area, int) or color not in ['r', 'b', 'g']:
            raise ValueError('Invalid value')
        if perimeter <= 0 or area <= 0:
            raise ValueError('Invalid input')
        self.perimeter = perimeter
        self.area = area
        self.color = color

class Polygon(Figure):
    def __init__(self, perimeter, area, color, angle_count, equilateral, biggest_angle):
        super().__init__(perimeter, area, color)
        if not isinstance(angle_count, int) or angle_count <= 2 or not isinstance(equilateral, bool) or not isinstance(biggest_angle, int):
            raise ValueError('Invalid value')
        if biggest_angle <= 0 or biggest_angle >= 180:
            raise ValueError('Invalid value')
        self.angle_count = angle_count
        self.equilateral = equilateral
        self.biggest_angle = biggest_angle

    def __str__(self):
        return f'Polygon: Периметр {self.perimeter}, площадь {self.area}, цвет фигуры {self.color}, количество углов {self.angle_count}, равносторонний {self.equilateral}, самый большой угол {self.biggest_angle}.'

    def __add__(self):
        return self.perimeter + self.area

    def __eq__(self, other):
        return self.perimeter == other.perimeter and self.area == other.area and self.angle_count == other.angle_count

class Circle(Figure):
    def __init__(self, perimeter, area, color, radius, diametr):
        super().__init__(perimeter, area, color)
        if not isinstance(radius, int) or not isinstance(diametr, int) or diametr != 2 * radius:
            raise ValueError('Invalid value')
        self.radius = radius
        self.diametr = diametr

    def __str__(self):
        return f'Circle: Периметр {self.perimeter}, площадь {self.area}, цвет фигуры {self.color}, радиус {self.radius}, диаметр {self.diametr}.'

    def __add__(self):
        return self.perimeter + self.area

    def __eq__(self, other):
        return self.radius == other.radius

class PolygonList(list):
    def __init__(self, name):
        super().__init__()
        self.name = name

    def append(self, p_object):
        if isinstance(p_object, Polygon):
            super().append(p_object)
        else:
            raise TypeError(f'Invalid type {type(p_object)}')

    def print_colors(self):
        i = 1 
        for polygon in self:
            print(f'{i} многоугольник: {polygon.color}')
            i += 1 

    def print_count(self):
        print(f'{len(self)}')

class CircleList(list):
    def __init__(self, name):
        super().__init__()
        self.name = name

    def extend(self, iterable):
        for item in iterable:
            if isinstance(item, Circle):
                self.append(item)
    def print_colors(self):
        i = 1  
        for circle in self:
            print(f'{i} окружность: {circle.color}')
            i += 1 

    def total_area(self):
        total_area = sum(circle.area for circle in self)
        print(f'{total_area}')
