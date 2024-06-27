class Figure:
    color_list = {'r', 'g', 'b'}

    def __init__(self, perimeter, area, color):
        if isinstance(perimeter, int) and perimeter > 0:
            self.perimeter = perimeter
        else:
            raise ValueError("Invalid value")

        if isinstance(area, int) and area > 0:
            self.area = area
        else:
            raise ValueError("Invalid value")

        if isinstance(color, str) and color in self.color_list:
            self.color = color
        else:
            raise ValueError("Invalid value")

    def __add__(self):
        return self.perimeter + self.area


class Polygon(Figure):
    def __init__(self, perimeter, area, color, angle_count, equilateral, biggest_angle):
        super().__init__(perimeter, area, color)

        if isinstance(angle_count, int) and angle_count > 2:
            self.angle_count = angle_count
        else:
            raise ValueError("Invalid value")

        if isinstance(equilateral, bool):
            self.equilateral = equilateral
        else:
            raise ValueError("Invalid value")

        if isinstance(biggest_angle, int) and 0 < biggest_angle < 180 * (self.angle_count - 2):
            self.biggest_angle = biggest_angle
        else:
            raise ValueError("Invalid value")

    def __str__(self):
        return (f"Polygon: Периметр {self.perimeter}, " +
                f"площадь {self.area}, " +
                f"цвет фигуры {self.color}, " +
                f"количество углов {self.angle_count}, " +
                f"равносторонний {self.equilateral}, " +
                f"самый большой угол {self.biggest_angle}.")

    def __eq__(self, other):
        return isinstance(other, Polygon) and self.__dict__ == other.__dict__


class Circle(Figure):
    def __init__(self, perimeter, area, color, radius, diametr):
        super().__init__(perimeter, area, color)

        if isinstance(radius, int) and radius > 0:
            self.radius = radius
        else:
            raise ValueError("Invalid value")

        if isinstance(diametr, int) and diametr == 2 * self.radius:
            self.diametr = diametr
        else:
            raise ValueError("Invalid value")

    def __str__(self):
        return (f"Circle: Периметр {self.perimeter}, " +
                f"площадь {self.area}, " +
                f"цвет фигуры {self.color}, " +
                f"радиус {self.radius}, " +
                f"диаметр {self.diametr}.")

    def __eq__(self, other):
        return isinstance(other, Circle) and self.radius == other.radius


class PolygonList(list):
    def __init__(self, name):
        super().__init__()

        self.name = str(name)

    def append(self, p_object):
        if isinstance(p_object, Polygon):
            super().append(p_object)
        else:
            raise TypeError(f"Invalid type <{type(p_object)} p_object>")

    def print_colors(self):
        for i in range(super().__len__()):
            print(f"{i + 1} многоугольник: {self[i].color}")

    def print_count(self):
        print(len(self))


class CircleList(list):
    def __init__(self, name):
        super().__init__()
        self.name = str(name)

    def extend(self, iterable):
        arr = [x for x in iterable if isinstance(x, Circle)]
        super().extend(arr)

    def print_colors(self):
        for i in range(super().__len__()):
            print(f"{i + 1} окружность: {self[i].color}")

    def total_area(self):
        print(sum(x.area for x in self))