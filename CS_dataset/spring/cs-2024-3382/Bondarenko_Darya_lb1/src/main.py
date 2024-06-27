class Figure:
    def __init__(self, perimeter, area, color):
        if isinstance(perimeter, int) and perimeter > 0 and isinstance(area, int) and area > 0 and color in ['r', 'b', 'g']:
            self.perimeter = perimeter
            self.area = area
            self.color = color
        else:
            raise ValueError("Invalid value")


class Polygon(Figure):
    def __init__(self, perimeter, area, color, angle_count, equilateral, biggest_angle):
        super().__init__(perimeter, area, color)
        if isinstance(angle_count, int) and angle_count > 2 and isinstance(equilateral, bool) and isinstance(biggest_angle, int) and biggest_angle > 0:
            self.angle_count = angle_count
            self.equilateral = equilateral
            self.biggest_angle = biggest_angle
        else:
            raise ValueError("Invalid value")

    def __str__(self):
        return f'Polygon: Периметр {self.perimeter}, площадь {self.area}, цвет фигуры {self.color}, количество углов {self.angle_count}, равносторонний {self.equilateral}, самый большой угол {self.biggest_angle}.'

    def __add__(self):
        return self.perimeter + self.area

    def __eq__(self, other):
        return self.perimeter == other.perimeter and self.area == other.area and self.angle_count == other.angle_count


class Circle(Figure):
    def __init__(self, perimeter, area, color, radius, diametr):
        super().__init__(perimeter, area, color)

        if isinstance(radius, int) and radius > 0 and isinstance(diametr, int) and diametr > 0 and diametr == 2 * radius:
            self.radius = radius
            self.diametr = diametr
        else:
            raise ValueError("Invalid value")

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
        for i, polygon in enumerate(self, 1):
            print(f'{i} многоугольник: {polygon.color}')

    def print_count(self):
        print(len(self))


class CircleList(list):
    def __init__(self, name):
        super().__init__()
        self.name = name

    def extend(self, iterable):
        for i in iterable:
            if isinstance(i, Circle):
                super().append(i)

    def print_colors(self):
        for i, circle in enumerate(self, 1):
            print(f'{i} окружность: {circle.color}')

    def total_area(self):
        print(sum(i.area for i in self))