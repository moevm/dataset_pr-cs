class ErrorMessages:
    _value_error_message = 'Invalid value'
    _invalid_type_error_message = 'Invalid type {x}'


class Figure(ErrorMessages):
    __valid_colors = ['r', 'g', 'b']

    def __init__(self, perimeter, area, color):
        self.perimeter = perimeter
        self.area = area
        self.color = color

        self.__check_values()

    def __check_values(self):
        checks = (
            (type(self.perimeter) is int) and (self.perimeter > 0),
            (type(self.area) is int) and (self.area > 0),
            (type(self.color) is str) and (self.color in self.__valid_colors)
        )

        if not all(checks):
            raise ValueError(self._value_error_message)


class Polygon(Figure):
    def __init__(self, perimeter, area, color, angle_count, equilateral, biggest_angle):
        super().__init__(perimeter, area, color)

        self.angle_count = angle_count
        self.equilateral = equilateral
        self.biggest_angle = biggest_angle

        self.__check_values()

    def __check_values(self):
        checks = (
            (type(self.angle_count) is int) and (self.angle_count > 2),
            type(self.equilateral) is bool,
            (type(self.biggest_angle) is int) and (self.biggest_angle > 0),
        )

        if not all(checks):
            raise ValueError(self._value_error_message)

    def __str__(self):
        d = {
            'Периметр': self.perimeter,
            'площадь': self.area,
            'цвет фигуры': self.color,
            'количество углов': self.angle_count,
            'равносторонний': self.equilateral,
            'самый большой угол': self.biggest_angle
        }

        return 'Polygon: ' + ', '.join(map(lambda x: f'{x} {d[x]}', d)) + '.'

    def __add__(self):
        return self.perimeter + self.area

    def __eq__(self, other):
        checks = (
            self.perimeter == other.perimeter,
            self.area == other.area,
            self.angle_count == other.angle_count
        )

        return all(checks)


class Circle(Figure):
    def __init__(self, perimeter, area, color, radius, diametr):
        super().__init__(perimeter, area, color)

        self.radius = radius
        self.diametr = diametr

        self.__check_values()

    def __check_values(self):
        checks = (
            (type(self.radius) is int) and (self.radius > 0),
            self.diametr == self.radius * 2,
        )

        if not all(checks):
            raise ValueError(self._value_error_message)

    def __str__(self):
        d = {
            'Периметр': self.perimeter,
            'площадь': self.area,
            'цвет фигуры': self.color,
            'радиус': self.radius,
            'диаметр': self.diametr,
        }

        return 'Circle: ' + ', '.join(map(lambda x: f'{x} {d[x]}', d)) + '.'

    def __add__(self):
        return self.perimeter + self.area

    def __eq__(self, other):
        checks = (
            self.radius == other.radius,
        )

        return all(checks)


class PolygonList(list, ErrorMessages):
    def __init__(self, name: str):
        super().__init__(self)
        self.name = name

    def append(self, p_object):
        if not isinstance(p_object, Polygon):
            raise TypeError(self._value_error_message.format(x=type(p_object)))

        super().append(p_object)

    def print_colors(self):
        for i in range(len(self)):
            print(f'{i + 1} многоугольник: {self[i].color}')

    def print_count(self):
        print(len(self))


class CircleList(list):
    def __init__(self, name: str):
        super().__init__(self)
        self.name = name

    def extend(self, iterable):
        for el in iterable:
            if isinstance(el, Circle):
                self.append(el)

    def print_colors(self):
        for i in range(len(self)):
            print(f'{i + 1} окружность: {self[i].color}')

    def total_area(self):
        print(sum(circle.area for circle in self))