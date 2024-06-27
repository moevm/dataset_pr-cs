def int_positive_check(item):
    if isinstance(item, int) and item > 0:
        return True


def value_check(value, condition):
    if condition(value):
        return value
    else:
        raise ValueError("Invalid value")


class Figure:
    def __init__(self, perimeter, area, color):
        self.perimeter = value_check(perimeter, int_positive_check)
        self.area = value_check(area, int_positive_check)
        self.color = value_check(color, lambda x: x in ('r', 'b', 'g'))


class Polygon(Figure):  # Наследуется от класса Figure
    def __init__(self, perimeter, area, color, angle_count, equilateral, biggest_angle):
        super().__init__(perimeter, area, color)
        self.angle_count = value_check(angle_count, lambda x: int_positive_check(x) and x > 2)
        self.equilateral = value_check(equilateral, lambda x: isinstance(x, bool))
        self.biggest_angle = value_check(biggest_angle, int_positive_check)

    def __str__(self):
        return f"Polygon: Периметр {self.perimeter}, площадь {self.area}, цвет фигуры {self.color}, количество углов {self.angle_count}, равносторонний {self.equilateral}, самый большой угол {self.biggest_angle}."

    def __add__(self):
        return self.area + self.perimeter

    def __eq__(self, other):
        return self.perimeter == other.perimeter and self.area == other.area and self.angle_count == other.angle_count


class Circle(Figure):  # Наследуется от класса Figure
    def __init__(self, perimeter, area, color, radius, diametr):
        super().__init__(perimeter, area, color)
        self.radius = value_check(radius, int_positive_check)
        self.diametr = value_check(diametr, lambda x: int_positive_check(x) and x == self.radius*2)

    def __str__(self):
        return f"Circle: Периметр {self.perimeter}, площадь {self.area}, цвет фигуры {self.color}, радиус {self.radius}, диаметр {self.diametr}."

    def __add__(self):
        return self.area + self.perimeter

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
            raise TypeError(f"Invalid type {type(p_object)}")

    def print_colors(self):
        for i in range(len(self)):
            print(f"{i+1} многоугольник: {self[i].color}")

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
        for i in range(len(self)):
            print(f"{i+1} окружность: {self[i].color}")

    def total_area(self):
        area = 0
        for i in self:
            area += i.area
        print(area)