from functools import reduce


class Figure:
    def __init__(self, perimeter, area, color):
        self.perimeter = perimeter
        self.area = area
        self.color = color

    @property
    def perimeter(self):
        return self._perimeter

    @perimeter.setter
    def perimeter(self, value):
        if isinstance(value, int) and value > 0:
            self._perimeter = value
        else:
            raise ValueError('Invalid value')

    @property
    def area(self):
        return self._area

    @area.setter
    def area(self, value):
        if isinstance(value, int) and value > 0:
            self._area = value
        else:
            raise ValueError('Invalid value')

    @property
    def color(self):
        return self._color

    @color.setter
    def color(self, value):
        if value in ('r', 'g', 'b'):
            self._color = value
        else:
            raise ValueError('Invalid value')

    def __str__(self):
        return f'{self.__class__.__name__}: Периметр {self.perimeter}, площадь {self.area}, цвет фигуры {self.color}, '

    def __add__(self):
        return self.area + self.perimeter

    def __eq__(self, other):
        if isinstance(other, Polygon):
            return (self.perimeter == other.perimeter) and (self.area == other.area) and (self.angle_count == other.angle_count)
        if isinstance(other, Circle):
            return self.radius == other.radius


class Polygon(Figure):
    def __init__(self, perimeter, area, color, angle_count, equilateral, biggest_angle):
        super().__init__(perimeter, area, color)
        self.angle_count = angle_count
        self.equilateral = equilateral
        self.biggest_angle = biggest_angle

    @property
    def angle_count(self):
        return self._angle_count

    @angle_count.setter
    def angle_count(self, value):
        if isinstance(value, int) and value > 2:
            self._angle_count = value
        else:
            raise ValueError('Invalid value')

    @property
    def equilateral(self):
        return self._equilateral

    @equilateral.setter
    def equilateral(self, value):
        if isinstance(value, bool):
            self._equilateral = value
        else:
            raise ValueError('Invalid value')

    @property
    def biggest_angle(self):
        return self._biggest_angle

    @biggest_angle.setter
    def biggest_angle(self, value):
        if isinstance(value, int) and value > 0:
            self._biggest_angle = value
        else:
            raise ValueError('Invalid value')

    def __str__(self):
        return super().__str__() + f'количество углов {self.angle_count}, равносторонний {self.equilateral}, самый большой угол {self.biggest_angle}.'


class Circle(Figure):
    def __init__(self, perimeter, area, color, radius, diametr):
        super().__init__(perimeter, area, color)
        self.radius = radius
        self.diametr = diametr

    @property
    def radius(self):
        return self._radius

    @radius.setter
    def radius(self, value):
        if isinstance(value, int) and value > 0:
            self._radius = value
        else:
            raise ValueError('Invalid value')

    @property
    def diametr(self):
        return self._diametr

    @diametr.setter
    def diametr(self, value):
        if isinstance(value, int) and value > 0 and value == self.radius * 2:
            self._diametr = value
        else:
            raise ValueError('Invalid value')

    def __str__(self):
        return super().__str__() + f'радиус {self.radius}, диаметр {self.diametr}.'


class PolygonList(list):
    def __init__(self, name):
        super().__init__()
        self.name = name

    @property
    def name(self):
        return self._name

    @name.setter
    def name(self, value):
        self._name = value

    def append(self, __object):
        if isinstance(__object, Polygon):
            super().append(__object)
        else:
            raise TypeError(f'Invalid type {__object.__class__}')

    def print_colors(self):
        for obj_num in range(len(self)):
            print(f'{obj_num + 1} многоугольник: {self[obj_num].color}')

    def print_count(self):
        print(len(self))


class CircleList(list):
    def __init__(self, name):
        super().__init__()
        self.name = name

    @property
    def name(self):
        return self._name

    @name.setter
    def name(self, value):
        self._name = value

    def extend(self, __iterable):
        for obj in __iterable:
            if isinstance(obj, Circle):
                self.append(obj)

    def print_colors(self):
        for obj_num in range(len(self)):
            print(f'{obj_num + 1} окружность: {self[obj_num].color}')

    def total_area(self):
        print(reduce(lambda x, y: x + y.area, self, 0))


