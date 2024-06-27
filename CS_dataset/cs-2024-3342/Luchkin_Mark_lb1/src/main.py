class Figure:
    def __init__(self, perimeter, area, color):
        if not (isinstance(perimeter, int) and isinstance(area, int)
                and isinstance(color, str) and perimeter > 0 and area > 0 and
                color in ['r', 'g', 'b']):
            raise ValueError('Invalid value')

        self.perimeter = perimeter
        self.area = area
        self.color = color


class Polygon(Figure):
    def __init__(self, perimeter, area, color, angle_count, equilateral, biggest_angle):
        super().__init__(perimeter, area, color)
        if not ( angle_count > 2 and isinstance(biggest_angle, int) and biggest_angle > 0\
                and isinstance(equilateral, bool)) is True:
            raise ValueError('Invalid value')

        self.angle_count = angle_count
        self.equilateral = equilateral
        self.biggest_angle = biggest_angle

    def __str__(self):
        return (f'Polygon: Периметр {self.perimeter}, площадь {self.area}, цвет фигуры {self.color}, '
                f'количество углов {self.angle_count}, равносторонний {self.equilateral}, самый большой угол {self.biggest_angle}.')

    def __add__(self):
        return self.perimeter + self.area

    def __eq__(self, other):
        return True if self.perimeter == other.perimeter and self.area == other.area \
                       and self.angle_count == other.angle_count else False


class Circle(Figure):
    def __init__(self, perimeter, area, color, radius, diametr):
        super().__init__(perimeter, area, color)
        if not (isinstance(radius, int) and radius > 0 and isinstance(diametr, int) and 
                radius * 2 == diametr):
            raise ValueError('Invalid value')

        self.radius = radius
        self.diametr = diametr

    def __str__(self):
        return (f'Circle: Периметр {self.perimeter}, площадь {self.area}, цвет фигуры {self.color}, '
                f'радиус {self.radius}, диаметр {self.diametr}.')

    def __add__(self):
        return self.perimeter + self.area

    def __eq__(self, other):
        return True if self.radius == other.radius else False


class PolygonList(list):
    def __init__(self, name):
        super().__init__()
        self.name = name

    def append(self, p_object):
        if isinstance(p_object, Polygon):
            super().append(p_object)

        else:
            raise TypeError(f'Invalid type {p_object.__class__.__name__}')

    def print_colors(self):
        for i, poly in enumerate(self, start=1):
            print(f"{i} многоугольник: {poly.color}")

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
        for i, el in enumerate(self, start=1):
            print(f"{i} окружность: {el.color}")

    def total_area(self):
        total_area_sum = sum(el.area for el in self)
        print(total_area_sum)
