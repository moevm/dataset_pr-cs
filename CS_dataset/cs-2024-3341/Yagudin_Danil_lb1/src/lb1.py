class Figure:
    def __init__(self, perimeter, area, color):
        try:
            color_type = ['r', 'g', 'b']
            if (perimeter <= 0) or (area <= 0) or (color not in color_type):
                raise ValueError
            else:
                self.perimeter = perimeter
                self.area = area
                self.color = color
        except ValueError:
            raise ValueError

class Polygon(Figure):
    def __init__(self, perimeter, area, color, angle_count, equilateral, biggest_angle):
        try:
            color_type = ['r', 'g', 'b']
            if (perimeter <= 0) or (area <= 0) or (color not in color_type) or (angle_count <= 2) or (type(equilateral) != bool) or (biggest_angle <= 0):
                raise ValueError
            else:
                self.perimeter = perimeter
                self.area = area
                self.color = color
                self.angle_count = angle_count
                self.equilateral = equilateral
                self.biggest_angle = biggest_angle
        except ValueError:
            raise ValueError

    def __str__(self):
        return f"Polygon: Периметр {self.perimeter}, площадь {self.area}, цвет фигуры {self.color}, количество углов {self.angle_count}, равносторонний {self.equilateral}, самый большой угол {self.biggest_angle}."

    def __add__(self):
        return self.area + self.perimeter

    def __eq__(self, other):
        if (self.area == other.area) and (self.perimeter == other.perimeter) and (self.angle_count == other.angle_count):
            return True
        return False

class Circle(Figure):
    def __init__(self, perimeter, area, color, radius, diametr):
        try:
            color_type = ['r', 'g', 'b']
            if (perimeter <= 0) or (area <= 0) or (color not in color_type) or (radius <= 0) or (diametr <= 0 or diametr != (radius * 2)):
                raise ValueError
            else:
                self.perimeter = perimeter
                self.area = area
                self.color = color
                self.radius = radius
                self.diametr = diametr
        except ValueError:
            raise ValueError

    def __str__(self):
        return f"Circle: Периметр {self.perimeter}, площадь {self.area}, цвет фигуры {self.color}, радиус {self.radius}, диаметр {self.diametr}."

    def __add__(self):
        return self.area + self.perimeter

    def __eq__(self, other):
        if self.radius == other.radius:
            return True
        return False

class PolygonList(list):
    def __init__(self, name):
        super().__init__()
        self.name = name

    def append(self, p_object):
        try:
            if type(p_object) != Polygon:
                raise TypeError
            else:
                super().append(p_object)

        except TypeError:
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
        if hasattr(iterable, "__iter__"):
            for i in range(len(iterable)):
                if type(iterable[i]) == Circle:
                    super().append(iterable[i])
        else:
            raise TypeError

    def print_colors(self):
        for i in range(len(self)):
            print(f"{i + 1} окружность: {self[i].color}")

    def total_area(self):
        sum = 0
        for i in range(len(self)):
            sum += self[i].area
        print(sum)
