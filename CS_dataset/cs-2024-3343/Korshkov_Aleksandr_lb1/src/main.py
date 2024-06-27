class Figure:
    def __init__(self, perimeter, area, color):
        if type(perimeter) is not int or type(area) is not int or type(color) is not str:
            raise ValueError("Invalid value")
        if (perimeter <= 0) or (area <= 0) or color not in ("r", "g", "b"):
            raise ValueError("Invalid value")
        self.perimeter = perimeter
        self.area = area
        self.color = color


class Polygon(Figure):
    def __init__(self, perimeter, area, color, angle_count, equilateral, biggest_angle):
        super().__init__(perimeter, area, color)
        if type(angle_count) is not int or type(equilateral) is not bool or type(biggest_angle) is not int:
            raise ValueError("Invalid value")
        if (angle_count < 3) or (biggest_angle <= 0):
            # убрано лишнее условие и исправлена ошибка с кол-вом углов (защита)
            raise ValueError("Invalid value")
        self.angle_count = angle_count
        self.equilateral = equilateral
        self.biggest_angle = biggest_angle

    def __str__(self):
        return (f"Polygon: Периметр {self.perimeter}, площадь {self.area}, цвет фигуры {self.color}, "
                f"количество углов {self.angle_count}, равносторонний {self.equilateral}, "
                f"самый большой угол {self.biggest_angle}.")

    def __add__(self):
        return self.perimeter + self.area

    def __eq__(self, other):
        return self.perimeter == other.perimeter and self.area == other.area and self.angle_count == other.angle_count


class Circle(Figure):  # Наследуется от класса Figure
    def __init__(self, perimeter, area, color, radius, diametr):
        super().__init__(perimeter, area, color)
        if type(radius) is not int or type(diametr) is not int:
            raise ValueError("Invalid value")
        if radius <= 0 or diametr != 2 * radius:
            raise ValueError("Invalid value")
        self.radius = radius
        self.diametr = diametr

    def __str__(self):
        return (f"Circle: Периметр {self.perimeter}, площадь {self.area}, "
                f"цвет фигуры {self.color}, радиус {self.radius}, диаметр {self.diametr}.")

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
            raise TypeError(f"Invalid type {type(p_object)}")

    def print_colors(self):
        for i in range(len(self)):
            print(f"{i + 1} многоугольник: {self[i].color}")

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
            print(f"{i + 1} окружность: {self[i].color}")

    def total_area(self):
        k = 0
        for i in self:
            k += i.area
        print(k)

