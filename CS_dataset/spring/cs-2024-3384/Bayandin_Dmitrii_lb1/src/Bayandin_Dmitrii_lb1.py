class Figure:
    def __init__(self, perimeter, area, color):
        if perimeter <= 0 or area <= 0 or (color != 'r' and color != 'g' and color != 'b') or \
                (not isinstance(perimeter, int)) or (not isinstance(area, int)):
            raise ValueError("Invalid value")
        self.perimeter = perimeter
        self.area = area
        self.color = color


class Polygon(Figure):
    def __init__(self, perimeter, area, color, angle_count, equilateral, biggest_angle):
        super().__init__(perimeter, area, color)
        if angle_count <= 2 or (not isinstance(angle_count, int)) or (not isinstance(equilateral, bool)) \
                or biggest_angle <= 0 or (not isinstance(biggest_angle, int)):
            raise ValueError("Invalid value")
        self.angle_count = angle_count
        self.equilateral = equilateral
        self.biggest_angle = biggest_angle

    def __str__(self):
        return f"Polygon: Периметр {self.perimeter}, площадь {self.area}, цвет фигуры {self.color}, количество углов " \
               f"{self.angle_count}, равносторонний {self.equilateral}, самый большой угол {self.biggest_angle}."

    def __add__(self):
        return self.perimeter + self.area

    def __eq__(self, other):
        return self.perimeter == other.perimeter and self.area == other.area and self.angle_count == other.angle_count


class Circle(Figure):
    def __init__(self, perimeter, area, color, radius, diametr):
        super().__init__(perimeter, area, color)
        if radius <= 0 or (not isinstance(radius, int)) or diametr <= 0 or (not isinstance(diametr, int)) \
                or radius * 2 != diametr:
            raise ValueError("Invalid value")
        self.radius = radius
        self.diametr = diametr

    def __str__(self):
        return f"Circle: Периметр {self.perimeter}, площадь {self.area}, цвет фигуры {self.color}, " \
               f"радиус {self.radius}, диаметр {self.diametr}."

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
        j = 1
        for i in self:
            print(j, f"многоугольник: {i.color}")
            j += 1

    def print_count(self):
        print(len(self))


class CircleList(list):
    def __init__(self, name):
        super().__init__(self)
        self.name = name

    def extend(self, iterable):
        array = []
        for i in iterable:
            if isinstance(i, Circle):
                array += [i]
        super().extend(array)

    def print_colors(self):
        j = 1
        for i in self:
            print(j, f"окружность: {i.color}")
            j += 1

    def total_area(self):
        s = 0
        for i in self:
            s += i.area
        print(s)
