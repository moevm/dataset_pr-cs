class Figure:
    def __init__(self, perimeter, area, color):
        if all([isinstance(perimeter, int) and perimeter > 0, isinstance(area, int) and area > 0, isinstance(color, str) and color in "rgb"]):
            self.perimeter = perimeter
            self.area = area
            self.color = color
        else:
            raise ValueError("Invalid value")


class Polygon(Figure):
    def __init__(self, perimeter, area, color, angle_count, equilateral, biggest_angle):
        if all([isinstance(angle_count, int) and angle_count > 2, isinstance(equilateral, bool), isinstance(biggest_angle, int) and biggest_angle > 0]):
            super().__init__(perimeter, area, color)
            self.angle_count = angle_count
            self.equilateral = equilateral
            self.biggest_angle = biggest_angle
        else:
            raise ValueError("Invalid value")

    def __str__(self):
        return f"Polygon: Периметр {self.perimeter}, площадь {self.area}, цвет фигуры {self.color}, количество углов {self.angle_count}, равносторонний {self.equilateral}, самый большой угол {self.biggest_angle}."

    def __add__(self):
        return self.area + self.perimeter

    def __eq__(self, second):
        if all([self.perimeter == second.perimeter, self.area == second.area, self.angle_count == second.angle_count]):
            return True
        return False


class Circle(Figure):
    def __init__(self, perimeter, area, color, radius, diametr):
        if all([isinstance(radius, int) and radius > 0, isinstance(diametr, int) and diametr == 2 * radius]):
            super().__init__(perimeter, area, color)
            self.radius = radius
            self.diametr = diametr
        else:
            raise ValueError("Invalid value")

    def __str__(self):
        return f"Circle: Периметр {self.perimeter}, площадь {self.area}, цвет фигуры {self.color}, радиус {self.radius}, диаметр {self.diametr}."

    def __add__(self):
        return self.area + self.perimeter

    def __eq__(self, second):
        if self.radius == second.radius:
            return True
        return False


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
        answer = 0
        for i in self:
            answer += i.area
        print(answer)