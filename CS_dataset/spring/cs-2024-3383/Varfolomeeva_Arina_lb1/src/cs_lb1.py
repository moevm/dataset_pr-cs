class Figure:
    def __init__(self, perimeter, area, color):
        self.perimeter = perimeter
        self.area = area
        self.color = color
        try:
            if (isinstance(perimeter, int) == 0 or self.perimeter <= 0) or (isinstance(area, int) == 0 or self.area <= 0) or ((isinstance(color, str) == 0) or self.color != 'r' and self.color != 'b' and self.color != 'g'):
                raise ValueError()
        except ValueError:
            raise ValueError("Invalid value")



class Polygon(Figure):  
    def __init__(self, perimeter, area, color, angle_count, equilateral, biggest_angle):
        super().__init__(perimeter, area, color)
        self.angle_count = angle_count
        self.equilateral = equilateral
        self.biggest_angle = biggest_angle
        try:
            if (isinstance(angle_count, int)==0 or self.angle_count <= 2) or (isinstance(biggest_angle, int)==0 or self.biggest_angle <= 0) or (isinstance(equilateral, bool)== 0):
                raise ValueError()
        except ValueError:
            raise ValueError("Invalid value")

    def __str__(self):
        return f'Polygon: Периметр {self.perimeter}, площадь {self.area}, цвет фигуры {self.color}, количество углов {self.angle_count}, равносторонний {self.equilateral}, самый большой угол {self.biggest_angle}.'

    def __add__(self):
        return self.area + self.perimeter

    def __eq__(self, other):
        if (self.perimeter == other.perimeter) and (self.area == other.area) and (self.angle_count == other.angle_count):
            return True
        return False

class Circle(Figure):
    def __init__(self, perimeter, area, color, radius, diametr):
        super().__init__(perimeter, area, color)
        self.radius = radius
        self.diametr = diametr
        try:
            if (self.radius <= 0) or (self.diametr <= 0) or (self.diametr != 2 * self.radius):
                raise ValueError()
        except ValueError:
            raise ValueError("Invalid value")

    def __str__(self):
        return f'Circle: Периметр {self.perimeter}, площадь {self.area}, цвет фигуры {self.color}, радиус {self.radius}, диаметр {self.diametr}.'

    def __add__(self):
        return self.area + self.perimeter

    def __eq__(self, other):
        if (self.radius == other.radius):
            return True
        return False


class PolygonList(list):
    def __init__(self, name):
        self.name = name
    def append(self, item):
        if isinstance(item, Polygon):
            super().append(item)
        else:
            raise TypeError('Invalid type <тип_объекта p_object>')
    def print_colors(self):
        for i in range(len(self)):
            print(f'{i+1} многоугольник: {self[i].color}')
    def print_count(self):
        print(len(self))

class CircleList(list):
    def __init__(self, name):
        self.name = name
    def extend(self, lst):
        for item in lst:
            if isinstance(item, Circle):
                super().append(item)
    def print_colors(self):
        for i in range(len(self)):
            print(f'{i+1} окружность: {self[i].color}')
    def total_area(self):
        total_area = 0
        for i in range(len(self)):
            total_area += self[i].area
        print(total_area)