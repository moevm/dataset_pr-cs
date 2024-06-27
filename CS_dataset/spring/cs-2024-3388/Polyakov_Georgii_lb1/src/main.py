class Figure:
    def __init__(self, perimeter, area, color):
        if (perimeter>0 and isinstance(perimeter, int)) and (area>0 and isinstance(area, int)) and (color in "rbg"):
            self.perimeter = perimeter
            self.area = area
            self.color = color
        else:
            raise ValueError("Invalid value")


class Polygon(Figure):
    def __init__(self, perimeter, area, color, angle_count, equilateral, biggest_angle):
        super().__init__(perimeter, area, color)
        if (isinstance(angle_count, int) and (angle_count > 2)) and isinstance(equilateral, bool) and (isinstance(biggest_angle, int) and 0<biggest_angle):
            self.angle_count = angle_count
            self.equilateral = equilateral
            self.biggest_angle = biggest_angle
        else:
            raise ValueError("Invalid value")
    def __str__(self):
        return f"Polygon: Периметр {self.perimeter}, площадь {self.area}, цвет фигуры {self.color}, количество углов {self.angle_count}, равносторонний {self.equilateral}, самый большой угол {self.biggest_angle}."

    def __add__(self):
        return self.area+self.perimeter

    def __eq__(self, other):
       return (self.perimeter == other.perimeter) and (self.area == other.area) and (self.angle_count == other.angle_count)


class Circle(Figure):
    def __init__(self, perimeter, area, color, radius, diametr):
        super().__init__(perimeter, area, color)
        if (radius>0 and isinstance(radius, int)) and (diametr>0 and isinstance(diametr, int) and diametr == 2*radius):
            self.radius = radius
            self.diametr = diametr
        else:
            raise ValueError("Invalid value")
    def __str__(self):
        return f"Circle: Периметр {self.perimeter}, площадь {self.area}, цвет фигуры {self.color}, радиус {self.radius}, диаметр {self.diametr}."

    def __add__(self):
        return self.area+self.perimeter

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
        for ind_colors in range(len(self)):
            print(f"{ind_colors + 1} многоугольник: {self[ind_colors].color}")

    def print_count(self):
        print(len(self))


class CircleList(list):
    def __init__(self, name):
        super().__init__(self)
        self.name = name

    def extend(self, iterable):
        super().extend(list(filter(lambda x: isinstance(x, Circle), iterable)))

    def print_colors(self):
        for ind_circles in range(len(self)):
            print(f"{ind_circles + 1} окружность: {self[ind_circles].color}")

    def total_area(self):
        areas = 0

        for circles in self:
            areas += circles.area
        print(areas)
