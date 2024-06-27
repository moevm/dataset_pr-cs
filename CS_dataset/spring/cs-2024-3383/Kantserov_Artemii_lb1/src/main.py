class Figure:
    def __init__(self, perimeter, area, color):
        if isinstance(perimeter, int) == 0 or perimeter <= 0: raise ValueError('Invalid value')
        self.perimeter = perimeter
        if isinstance(area, int) == 0 or area <= 0: raise ValueError('Invalid value')
        self.area = area
        if isinstance(color, str) == 0 or color not in 'rgb': raise ValueError('Invalid value')
        self.color = color


class Polygon(Figure):
    def __init__(self, perimeter, area, color, angle_count, equilateral, biggest_angle):
        if isinstance(perimeter, int) == 0 or perimeter <= 0: raise ValueError('Invalid value')
        self.perimeter = perimeter
        if isinstance(area, int) == 0 or area <= 0: raise ValueError('Invalid value')
        self.area = area
        if color not in "rgb" or isinstance(color, str) == 0: raise ValueError('Invalid value')
        self.color = color
        if angle_count < 3 or isinstance(angle_count, int) == 0: raise ValueError('Invalid value')
        self.angle_count = angle_count
        if isinstance(equilateral, bool) == 0: raise ValueError('Invalid value')
        self.equilateral = equilateral
        if 0 >= biggest_angle or biggest_angle > (angle_count - 2) * 180 or isinstance(biggest_angle, int) == 0:raise ValueError('Invalid value')
        self.biggest_angle = biggest_angle

    def __str__(self):
        return f"Polygon: Периметр {self.perimeter}, площадь {self.area}, цвет фигуры {self.color}, количество углов {self.angle_count}, равносторонний {self.equilateral}, самый большой угол {self.biggest_angle}."

    def __add__(self):
        return self.area + self.perimeter

    def __eq__(self, other):
        if not isinstance(other, Polygon):
            return False
        if self.perimeter == other.perimeter and self.area == other.area and self.angle_count == other.angle_count:
            return True
        return False


class Circle(Figure):
    def __init__(self, perimeter, area, color, radius, diametr):
        if isinstance(perimeter, int) == 0 or perimeter <= 0: raise ValueError('Invalid value')
        self.perimeter = perimeter
        if isinstance(area, int) == 0 or area <= 0: raise ValueError('Invalid value')
        self.area = area
        if color not in "rgb" or isinstance(color, str) == 0: raise ValueError('Invalid value')
        self.color = color
        if radius <= 0 or isinstance(radius, int) == 0: raise ValueError('Invalid value')
        self.radius = radius
        if isinstance(diametr, int) == 0 or diametr <= 0 or diametr != 2 * radius: raise ValueError('Invalid value')
        self.diametr = diametr

    def __str__(self):
        return f"Circle: Периметр {self.perimeter}, площадь {self.area}, цвет фигуры {self.color}, радиус {self.radius}, диаметр {self.diametr}."

    def __add__(self):
        return self.area + self.perimeter

    def __eq__(self, other):
        if not isinstance(other, Circle):
            return False
        if self.radius == other.radius:
            return True
        return False


class PolygonList(list):
    def __init__(self, name):
        super().__init__()
        self.name = name

    def append(self, polygons):
        if isinstance(polygons, Polygon) == 0:
            raise TypeError('Invalid type <тип_объекта p_object>')
        super().append(polygons)

    def print_colors(self):
        for i in range(len(self)):
            print(f"{i + 1} многоугольник: {self[i].color}")

    def print_count(self):
        print(len(self))


class CircleList(list):
    def __init__(self, name):
        super().__init__()
        self.name = name

    def extend(self, circles):
        super().extend([i for i in circles if isinstance(i, Circle)])

    def print_colors(self):
        for i in range(len(self)):
            print(f"{i + 1} окружность: {self[i].color}")

    def total_area(self):
        print(sum(i.area for i in self))
