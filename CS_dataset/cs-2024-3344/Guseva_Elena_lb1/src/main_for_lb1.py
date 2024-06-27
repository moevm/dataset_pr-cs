class Figure():
    def __init__(self, perimeter, area, color):
        self.perimeter = perimeter
        self.area = area
        self.color = color
        if not isinstance(self.perimeter, int) or self.perimeter <= 0 or not isinstance(self.area, int) or self.area <= 0 or self.color not in ['r', 'g', 'b']:
            raise ValueError('Invalid value')

class Polygon(Figure):
    def __init__(self, perimeter, area, color, angle_count, equilateral, biggest_angle):
        super().__init__(perimeter, area, color)
        self.angle_count = angle_count
        self.equilateral = equilateral
        self.biggest_angle = biggest_angle
        if not isinstance(self.angle_count, int) or self.angle_count <= 2 or not isinstance(self.equilateral, bool) or not isinstance(self.biggest_angle, int) or self.biggest_angle <= 0:
            raise ValueError('Invalid value')

    def __str__(self):
        return f"Polygon: Периметр {self.perimeter}, площадь {self.area}, цвет фигуры {self.color}, количество углов {self.angle_count}, равносторонний {self.equilateral}, самый большой угол {self.biggest_angle}."

    def __add__(self):
        return self.perimeter + self.area

    def __eq__(self, other):
        if other.__class__.__name__ == self.__class__.__name__:
            if self.perimeter == other.perimeter and self.area == other.area and self.angle_count == other.angle_count:
                return True
            else:
                return False

class Circle(Figure):
    def __init__(self, perimeter, area, color, radius, diametr):
        super().__init__(perimeter, area, color)
        self.radius = radius
        self.diametr = diametr
        if not isinstance(radius, int) or not isinstance(diametr, int) or not radius > 0 or not diametr == 2 * radius:
            raise ValueError('Invalid value')

    def __str__(self):
        return f"Circle: Периметр {self.perimeter}, площадь {self.area}, цвет фигуры {self.color}, радиус {self.radius}, диаметр {self.diametr}."

    def __add__(self):
        return self.perimeter + self.area

    def __eq__(self, other):
        if other.__class__.__name__ == self.__class__.__name__:
            if self.radius == other.radius:
                return True
            else:
                return False

class PolygonList(list):
    def __init__(self, name):
        super().__init__()
        self.name = name

    def append(self, p_object):
        if p_object.__class__.__name__ == "Polygon":
            super().append(p_object)
        else:
            raise TypeError(f"Invalid type {type(p_object)}")

    def print_colors(self):
        for i in range(len(list(self))):
            print(f"{i+1} многоугольник: {list(self)[i].color}")

    def print_count(self):
        print(len(list(self)))

class CircleList(list):
    def __init__(self, name):
        super().__init__()
        self.name = name

    def extend(self, iterable):
        for item in iterable:
            if isinstance(item, Circle):
                self.append(item)

    def print_colors(self):
        for i in range(len(list(self))):
            print(f"{i+1} окружность: {list(self)[i].color}")

    def total_area(self):
        total = 0
        for i in list(self):
            total += i.area
        print(total)
