class Figure:
    def __init__(self, perimeter, area, color):
        if not (isinstance(perimeter, int) and (perimeter > 0) and isinstance(area, int) and (area > 0) and color in ['r', 'b', 'g']):
            raise ValueError("Invalid value")
        self.perimeter = perimeter
        self.area = area
        self.color = color


class Polygon(Figure):
    def __init__(self, perimeter, area, color, angle_count, equilateral, biggest_angle):
        super().__init__(perimeter, area, color)
        self.angle_count = angle_count
        self.equilateral = equilateral
        self.biggest_angle = biggest_angle
        if not (
            isinstance(angle_count, int) and (angle_count > 2) and isinstance(equilateral, bool) and isinstance(biggest_angle, int) and 0 < biggest_angle < 180
        ):
            raise ValueError("Invalid value")

    def __str__(self):
        return f"Polygon: Периметр {self.perimeter}, площадь {self.area}, цвет фигуры {self.color}, количество углов {self.angle_count}, равносторонний {self.equilateral}, самый большой угол {self.biggest_angle}."

    def __add__(self):
        return self.area + self.perimeter

    def __eq__(self, other):
        return self.perimeter == other.perimeter and self.area == other.area and self.angle_count == other.angle_count


class Circle(Figure):
    def __init__(self, perimeter, area, color, radius, diametr):
        if not (
            isinstance(perimeter, int) and (perimeter > 0) and isinstance(area, int) and (area > 0) and color in ['r', 'b', 'g'] and
            isinstance(radius, int) and (radius > 0) and isinstance(diametr, int) and diametr > 0 and diametr == 2 * radius
        ):
            raise ValueError("Invalid value")
        super().__init__(perimeter, area, color)
        self.radius = radius
        self.diametr = diametr

    def __str__(self):
        return f"Circle: Периметр {self.perimeter}, площадь {self.area}, цвет фигуры {self.color}, радиус {self.radius}, диаметр {self.diametr}."

    def __add__(self):
        return self.area + self.perimeter

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
            raise TypeError(f"Invalid type {type(p_object)}")

    def print_colors(self):
        for i in range(len(self)):
            print(f"{i + 1} многоугольник: {self[i].color}")

    def print_count(self):
        print(len(self))


class CircleList(list):
    def __init__(self, name):
        super().__init__(self)
        self.name = name

    def extend(self, iterable):
        super().extend(list(filter(lambda x: isinstance(x, Circle), iterable)))

    def print_colors(self):
        for i in range(len(self)):
            print(f"{i + 1} окружность: {self[i].color}")

    def total_area(self):
        sum_areas = 0
        for i in self:
            sum_areas += i.area
        print(sum_areas)
