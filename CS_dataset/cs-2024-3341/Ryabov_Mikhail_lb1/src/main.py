class Figure:
    def __init__(self, perimeter, area, color):
        condition_per = perimeter > 0 and isinstance(perimeter, int)
        condition_sqr = area > 0 and isinstance(area, int)
        condition_clr = color in ('r', 'b', 'g')
        if condition_per and condition_sqr and condition_clr:
            self.area = area
            self.perimeter = perimeter
            self.color = color
        else:

            raise ValueError("Invalid value")


class Polygon(Figure):
    def __init__(self, perimeter, area, color, angle_count, equilateral, biggest_angle):
        super().__init__(perimeter, area, color)
        angle_cond = angle_count > 2
        cond_eq = isinstance(equilateral, bool)
        cond_big = isinstance(biggest_angle, int) and biggest_angle > 0
        if angle_cond and cond_eq and cond_big:
            self.angle_count = angle_count
            self.equilateral = equilateral
            self.biggest_angle = biggest_angle
        else:
            raise ValueError("Invalid value")

    def __str__(self):
        return (f"Polygon: Периметр {self.perimeter}, площадь {self.area}, цвет фигуры {self.color}, количество углов "
                f"{self.angle_count}, равносторонний {self.equilateral}, самый большой угол {self.biggest_angle}.")

    def __add__(self):
        return self.area + self.perimeter

    def __eq__(self, other):
        return True if self.perimeter == other.perimeter and self.area == other.area and self.angle_count == other.angle_count else False


class Circle(Figure):
    def __init__(self, perimeter, square, color, radius, diametr):
        super().__init__(perimeter, square, color)
        if isinstance(radius, int) and radius > 0 and isinstance(diametr, int) and diametr/radius == 2:
            self.radius = radius
            self.diametr = diametr
        else:
            raise ValueError("Invalid value")

    def __str__(self):
        return f"Circle: Периметр {self.perimeter}, площадь {self.area}, цвет фигуры {self.color}, радиус {self.radius}, диаметр {self.diametr}."

    def __add__(self):
        return self.area + self.perimeter

    def __eq__(self, other):
        return True if self.radius == other.radius else False


class PolygonList(list):
    def __init__(self, name):
        super().__init__()
        self.name = name

    def append(self, __object):
        if isinstance(__object, Polygon):
            super().append(__object)
        else:
            raise TypeError("Invalid type <тип_объекта p_object>")

    def print_colors(self):
        for i in range(0, super().__len__()):
            print(f"{i+1} многоугольник: {super().__getitem__(i).color}")

    def print_count(self):
        print(super().__len__())


class CircleList(list):
    def __init__(self, name):
        super().__init__()
        self.name = name

    def extend(self, __iterable):
        for __obj in __iterable:
            if isinstance(__obj, Circle):
                super().append(__obj)

    def print_colors(self):
        for i in range(0, super().__len__()):
            print(f"{i+1} окружность: {super().__getitem__(i).color}")

    def total_area(self):
        total = 0
        for i in range(0, super().__len__()):
            total += super().__getitem__(i).area
        print(total)
