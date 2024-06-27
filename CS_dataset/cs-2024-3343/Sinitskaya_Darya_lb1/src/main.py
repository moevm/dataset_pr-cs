import math

class Figure:
    def __init__(self, perimeter, area, color):
        if not isinstance(perimeter, int) or perimeter <= 0:
            raise ValueError('Invalid value')
        if not isinstance(area, int) or area <= 0:
            raise ValueError('Invalid value')
        if color not in ['r', 'b', 'g']:
            raise ValueError('Invalid value')

        self.perimeter = perimeter
        self.area = area
        self.color = color

class Polygon(Figure):
    def __init__(self, perimeter, area, color, angle_count, equilateral, biggest_angle):
        super().__init__(perimeter, area, color)
        
        if not isinstance(angle_count, int) or angle_count <= 2:
            raise ValueError('Invalid value')

        if not isinstance(equilateral, bool):
            raise ValueError('Invalid value')

        if not isinstance(biggest_angle, int) or biggest_angle <= 0:
            raise ValueError('Invalid value')

        self.angle_count = angle_count
        self.equilateral = equilateral
        self.biggest_angle = biggest_angle

    def __str__(self):
        return f'Polygon: Периметр {self.perimeter}, площадь {self.area}, цвет фигуры {self.color}, количество углов {self.angle_count}, равносторонний {self.equilateral}, самый большой угол {self.biggest_angle}.'

    def __add__(self):
        return self.area + self.perimeter
        
    def __eq__(self, other):
        if isinstance(other, Polygon):
            return self.perimeter == other.perimeter and self.area == other.area and self.angle_count == other.angle_count
        return False
        
class Circle(Figure):
    def __init__(self, perimeter, area, color, radius, diametr):
        super().__init__(perimeter, area, color)

        if not isinstance(radius, int) or radius <= 0 or diametr != 2 * radius:
            raise ValueError('Invalid value')

        
        self.radius = radius
        self.diametr = diametr

    def __str__(self):
        return f'Circle: Периметр {self.perimeter}, площадь {self.area}, цвет фигуры {self.color}, радиус {self.radius}, диаметр {self.diametr}.'

    def __add__(self):
        return self.area + self.perimeter
        
    def __eq__(self, other):
        if isinstance(other, Circle):
            return self.radius == other.radius
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
        output = ''
        for idx, polygon in enumerate(self, start=1):
            output += f'{idx} многоугольник: {polygon.color}\n'
        output = output.rstrip()
        print(output)

    def print_count(self):
        print(len(self))

class CircleList(list):
    def __init__(self, name):
        super().__init__()
        self.name = name

    def extend(self, iterable):
        circles = [item for item in iterable if isinstance(item, Circle)]
        super().extend(circles)

    def print_colors(self):
        output = ''
        for idx, circle in enumerate(self, start=1):
            output += f'{idx} окружность: {circle.color}\n'
        output = output.rstrip()
        print(output)
  
    def total_area(self):
        total_area = sum([math.pi * circle.radius ** 2 for circle in self])
        print(math.ceil(total_area))
