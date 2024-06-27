def check_int(params):
    if all(isinstance(obj, int) and obj > 0 for obj in params):
        return 1
    return 0

class Figure:
    def __init__(self, perimeter, area, color):
        if check_int([perimeter, area]) and color in ['r', 'g', 'b']:
            self.perimeter = perimeter
            self.area = area
            self.color = color
        else:
            raise ValueError("Invalid value")

class Polygon(Figure):
    def __init__(self, perimeter, area, color, angle_count, equilateral, biggest_angle):
        super().__init__(perimeter, area, color)
        if check_int([angle_count, biggest_angle]) and angle_count>2 and isinstance(equilateral, bool):
            self.angle_count = angle_count
            self.biggest_angle = biggest_angle
            self.equilateral = equilateral
        else: raise ValueError("Invalid value")

    def __str__(self):
        return f'Polygon: Периметр {self.perimeter}, площадь {self.area}, цвет фигуры {self.color}, количество углов {self.angle_count}, равносторонний {self.equilateral}, самый большой угол {self.biggest_angle}.'

    def __add__(self):
        return self.perimeter + self.area

    def __eq__(self, other):
        return self.perimeter == other.perimeter and self.area == other.area and self.angle_count == other.angle_count

class Circle(Figure):  # Наследуется от класса Figure
    def __init__(self, perimeter, area, color, radius, diametr):
        super().__init__(perimeter, area, color)
        if check_int([radius, diametr]) and diametr == 2*radius:
            self.radius = radius
            self.diametr = diametr
        else: raise ValueError("Invalid value")

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
        else: raise TypeError(f"Invalid type {type(p_object)}")

    def print_colors(self):
        print('\n'.join([f'{i+1} многоугольник: {self[i].color}' for i in range(len(self))]))

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
        print('\n'.join([f'{i+1} окружность: {self[i].color}' for i in range(len(self))]))

    def total_area(self):
        print(sum(i.area for i in self))