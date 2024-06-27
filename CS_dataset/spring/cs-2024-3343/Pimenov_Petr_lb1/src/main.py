class Figure:
    def __init__(self, perimeter, area, color):
        if not isinstance(perimeter, int) or not isinstance(area, int) or not isinstance(color, str):
            raise ValueError('Invalid value')
        if perimeter > 0 and area > 0 and color in {'r', 'g', 'b'}:
            self.perimeter = perimeter
            self.area = area
            self.color = color
        else:
            raise ValueError('Invalid value')


class Polygon(Figure):
    def __init__(self, perimeter, area, color, angle_count, equilateral, biggest_angle):
        super().__init__(perimeter, area, color)
        if not isinstance(angle_count, int) or not isinstance(equilateral, bool) or not isinstance(biggest_angle, int):
            raise ValueError('Invalid value')
        if angle_count > 2 and biggest_angle > 0:
            self.angle_count = angle_count
            self.equilateral = equilateral
            self.biggest_angle = biggest_angle
        else:
            raise ValueError('Invalid value')

    def __str__(self):
        return f'Polygon: Периметр {self.perimeter}, площадь {self.area}, цвет фигуры {self.color}, количество углов {self.angle_count}, равносторонний {self.equilateral}, самый большой угол {self.biggest_angle}.'

    def __add__(self):
        return self.area + self.perimeter

    def __eq__(self, other):
        if isinstance(other, Polygon):
            return self.perimeter == other.perimeter and self.area == other.area and self.angle_count == other.angle_count
        else:
            raise NotImplementedError(f'Cannot compare Polygon to {type(other)}')


class Circle(Figure):
    def __init__(self, perimeter, area, color, radius, diametr):
        super().__init__(perimeter, area, color)
        if not isinstance(radius, int) or not isinstance(diametr, int):
            raise ValueError('Invalid value')
        if radius > 0 and diametr > 0 and diametr == 2 * radius:
            self.radius = radius
            self.diametr = diametr
        else:
            raise ValueError('Invalid value')

    def __str__(self):
        return f'Circle: Периметр {self.perimeter}, площадь {self.area}, цвет фигуры {self.color}, радиус {self.radius}, диаметр {self.diametr}.'

    def __add__(self):
        return self.area + self.perimeter

    def __eq__(self, other):
        if isinstance(other, Circle):
            return self.perimeter == other.perimeter and self.area == other.area and self.radius == other.radius
        else:
            raise NotImplementedError(f'Cannot compare Circle to {type(other)}')


class PolygonList(list):
    def __init__(self, name):
        super().__init__()
        self.name = name

    def append(self, __object):
        if isinstance(__object, Polygon):
            super().append(__object)
        else:
            raise TypeError(f'Invalid type {type(__object)}')

    def print_colors(self):
        for i in range(len(self)):
            print(f'{i + 1} многоугольник: {self[i].color}')

    def print_count(self):
        print(len(self))


class CircleList(list):
    def __init__(self, name):
        super().__init__()
        self.name = name

    def extend(self, __iterable):
        for item in __iterable:
            if isinstance(item, Circle):
                super().append(item)

    def print_colors(self):
        for i in range(len(self)):
            print(f'{i + 1} окружность: {self[i].color}')

    def total_area(self):
        print(sum([x.area for x in self]))
