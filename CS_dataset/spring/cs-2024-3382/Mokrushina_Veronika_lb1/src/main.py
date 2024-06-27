class Figure:
    def __init__(self, perimeter, area, color):
        if isinstance(perimeter, int) and perimeter > 0:
            self.perimeter = perimeter
        else:
            raise ValueError("Invalid value")

        if isinstance(area, int) and area > 0:
            self.area = area
        else:
            raise ValueError("Invalid value")

        if color in ['r', 'g', 'b']:
            self.color = color
        else:
            raise ValueError("Invalid value")


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

        if isinstance(biggest_angle, int) and biggest_angle > 0:
            self.biggest_angle = biggest_angle
        else:
            raise ValueError("Invalid value")

    def __str__(self):
        return f"Polygon: Периметр {self.perimeter}, площадь {self.area}, цвет фигуры {self.color}, количество углов {self.angle_count}, равносторонний {self.equilateral}, самый большой угол {self.biggest_angle}."

    def __add__(self):
        return self.perimeter + self.area

    def __eq__(self, other):
        return self.perimeter == other.perimeter and self.area == other.area and self.angle_count == other.angle_count


class Circle(Figure):
    def __init__(self, perimeter, area, color, radius, diametr):
        super().__init__(perimeter, area, color)
        if isinstance(radius, int) and radius > 0:
            self.radius = radius
        else:
            raise ValueError("Invalid value")

        if isinstance(diametr, int) and diametr > 0 and diametr == 2 * radius:
            self.diametr = diametr
        else:
            raise ValueError("Invalid value")

    def __str__(self):
        return f"Circle: Периметр {self.perimeter}, площадь {self.area}, цвет фигуры {self.color}, радиус {self.radius}, диаметр {self.diametr}."

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
        result = "\n".join(f"{i+1} многоугольник: {self[i].color}" for i in range(len(self)))
        if len(self) != 0:
            print(result)

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
        result = "\n".join(f"{i+1} окружность: {self[i].color}" for i in range(len(self)))
        if len(self) != 0:
            print(result)

    def total_area(self):
        result = 0
        for i in self:
            result += i.area
        print(result)
