class Figure:
    def __init__(self, perimeter, area, color):
        if not isinstance(perimeter, int) or not isinstance(area, int) or not isinstance(color, str) or perimeter <= 0 or area <= 0 or color not in 'rgb':
            raise ValueError('Invalid value')
        self.perimeter = perimeter
        self.area = area
        self.color = color


class Polygon(Figure):
    def __init__(self, perimeter, area, color, angle_count, equilateral, biggest_angle):
        super().__init__(perimeter, area, color)
        if not isinstance(angle_count, int) or not isinstance(equilateral, bool) or not isinstance(biggest_angle, int) or angle_count <= 2 or biggest_angle <= 0:
            raise ValueError('Invalid value')
        self.angle_count = angle_count
        self.equilateral = equilateral
        self.biggest_angle = biggest_angle

    def __str__(self):
        return f'Polygon: Периметр {self.perimeter}, площадь {self.area}, цвет фигуры {self.color}, ' \
               f'количество углов {self.angle_count}, равносторонний {self.equilateral}, самый большой угол {self.biggest_angle}.'

    def __add__(self):
        return self.perimeter + self.area

    def __eq__(self, other):
        return isinstance(other, Polygon) and self.perimeter == other.perimeter \
               and self.area == other.area and self.angle_count == other.angle_count


class Circle(Figure):
    def __init__(self, perimeter, area, color, radius, diametr):
        super().__init__(perimeter, area, color)
        if not isinstance(radius, int) or not isinstance(diametr, int) or diametr != 2 * radius:
            raise ValueError('Invalid value')
        self.radius = radius
        self.diametr = diametr

    def __str__(self):
        return f'Circle: Периметр {self.perimeter}, площадь {self.area}, цвет фигуры {self.color}, ' \
               f'радиус {self.radius}, диаметр {self.diametr}.'

    def __add__(self):
        return self.perimeter + self.area

    def __eq__(self, other):
        return isinstance(other, Circle) and self.radius == other.radius


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
        count = 0
        for p in self:
            count += 1
            print(f'{count} многоугольник: {p.color}')

    def print_count(self):
        print(len(self))


class CircleList(list):
    def __init__(self, name):
        super().__init__()
        self.name = name

    def extend(self, iterable):
        for item in iterable:
            if isinstance(item, Circle):
                self.append(item)

    def print_colors(self):
        count = 0
        for c in self:
            count += 1
            print(f'{count} окружность: {c.color}')

    def total_area(self):
        total = sum(c.area for c in self)
        print(total)
