class Figure:
    def __init__(self, perimeter, area, color):
        if not(perimeter > 0 and isinstance(perimeter, int) and area > 0 and isinstance(area, int) and (color == 'r' or color == 'g' or color == 'b')):
            raise ValueError('Invalid value')
        self.perimeter = perimeter
        self.area = area
        self.color = color

class Polygon(Figure):
    def __init__(self, perimeter, area, color, angle_count, equilateral, biggest_angle):
        if not(perimeter > 0 and isinstance(perimeter, int) and area > 0 and isinstance(area, int) and (color == 'r' or color == 'g' or color == 'b') and angle_count > 2 and isinstance(angle_count, int) and isinstance(equilateral, bool) and biggest_angle > 0 and isinstance(biggest_angle, int)):
            raise ValueError('Invalid value')
        super().__init__(perimeter, area, color)
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
        if not(perimeter > 0 and isinstance(perimeter, int) and area > 0 and isinstance(area, int) and (color == 'r' or color == 'g' or color == 'b') and radius > 0 and isinstance(radius, int) and diametr > 0 and isinstance(diametr, int) and diametr == 2 * radius):
            raise ValueError('Invalid value')
        super().__init__(perimeter, area, color)
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
        super().__init__(self)
        self.name = name
    def append(self, p_object):
        if isinstance(p_object, Polygon):
            super().append(p_object)
        else:
            raise TypeError(f'Invalid type {type(p_object)}')
    def print_colors(self):
        for i in range(len(self)):
            print(f'{i + 1} многоугольник: {self[i].color}')
    def print_count(self):
        print(len(self))

class CircleList(list):
    def __init__(self, name):
        super().__init__(self)
        self.name = name
    def extend(self, iterable):
        for item in iterable:
            if isinstance(item, Circle):
                self.append(item)
    def print_colors(self):
        for i in range(len(self)):
            print(f'{i + 1} окружность: {self[i].color}')
    def total_area(self):
        sum_areas = 0
        for i in range(len(self)):
            sum_areas += self[i].area
        print(sum_areas)