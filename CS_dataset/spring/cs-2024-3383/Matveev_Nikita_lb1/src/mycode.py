class Figure():
    def __init__(self, p, a, c):
        if isinstance(p, int) and isinstance(a, int) and c in 'rbg' and p>0 and a>0:
            self.perimeter = p
            self.area = a
            self.color = c
        else:
            raise ValueError('Invalid value')

class Polygon(Figure):  # Наследуется от класса Figure
    def __init__(self, p, a, c, angle_count, e, big_angle):
        super().__init__(p, a, c)
        if (isinstance(angle_count, int) and angle_count>2 and isinstance(big_angle, int) and big_angle>0 and isinstance(e, bool)):
            self.angle_count = angle_count
            self.biggest_angle = big_angle
            self.equilateral = e
        else:
            raise ValueError('Invalid value')

    def __str__(self):
        return f"Polygon: Периметр {self.perimeter}, площадь {self.area}, цвет фигуры {self.color}, количество углов {self.angle_count}, " \
               f"равносторонний {self.equilateral}, самый большой угол {self.biggest_angle}."
    def __add__(self):
        return self.area + self.perimeter

    def __eq__(self, other):
        if (self.perimeter == other.perimeter and self.area==other.area and self.angle_count==other.angle_count):
            return True
        else:
            return False

class Circle(Figure):  # Наследуется от класса Figure
    def __init__(self, p, a, c, r, d):
        super().__init__(p, a, c)
        if (isinstance(r, int) and r>0 and isinstance(d, int) and d==2*r):
            self.radius = r
            self.diametr = d
        else:
            raise ValueError('Invalid value')

    def __str__(self):
        return f"Circle: Периметр {self.perimeter}, площадь {self.area}, цвет фигуры {self.color}, радиус {self.radius}, " \
               f"диаметр {self.diametr}."
    def __add__(self):
        return self.area + self.perimeter

    def __eq__(self, other):
        if (self.radius == other.radius):
            return True
        else:
            return False

class PolygonList(list):

    def __init__(self, name):
        super().__init__()
        self.name = name

    def append(self, obj):
        if isinstance(obj, Polygon): super().append(obj)
        else:
            raise TypeError('Invalid type <тип_объекта p_object>')

    def print_colors(self):
        color_list = list(x.color for x in self)
        for i in range(len(color_list)):
            print(f"{i+1} многоугольник: {color_list[i]}")

    def print_count(self):
         print(len(self))

class CircleList(list):
    def __init__(self, name):
        super().__init__()
        self.name = name

    def extend(self, iterable):
        for i in iterable:
            if type(i) == Circle:
                super().append(i)

    def print_colors(self):
        color_list = list(x.color for x in self)
        for i in range(len(color_list)):
            print(f"{i+1} окружность: {color_list[i]}")

    def total_area(self):
        print(sum(x.area for x in self))
