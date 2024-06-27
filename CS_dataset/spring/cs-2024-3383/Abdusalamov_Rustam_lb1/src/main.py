class Figure:
    def __init__(self,perimeter,area,color):
        if not (isinstance(perimeter,int) and perimeter > 0):
            raise ValueError("Invalid value")
        self.perimeter = perimeter
        if not (isinstance(area,int) and area > 0):
            raise ValueError("Invalid value")
        self.area = area
        if not(color in ['r','g','b']):
            raise ValueError("Invalid value")
        self.color = color
    def __add__(self):
        return self.area + self.perimeter
class Polygon(Figure):
    def __init__(self,perimeter,area,color,angle_count,equilateral,biggest_angle):
        super().__init__(perimeter,area,color)
        if not (isinstance(angle_count, int) and angle_count > 2):
            raise ValueError("Invalid value")
        if not (isinstance(equilateral,bool)):
            raise ValueError("Invalid value")
        if not (isinstance(biggest_angle,int) and biggest_angle > 0):
            raise ValueError("Invalid value")
        self.angle_count = angle_count
        self.equilateral = equilateral
        self.biggest_angle = biggest_angle
    def __str__(self):
        return f"Polygon: Периметр {self.perimeter}, площадь {self.area}, цвет фигуры {self.color}, количество углов {self.angle_count}, равносторонний {self.equilateral}, самый большой угол {self.biggest_angle}."
    def __eq__(self,other):
        if  (self.perimeter, self.area, self.angle_count) == (other.perimeter, other.area, other.angle_count):
            return True
        else:
            return False
class Circle(Figure):
    def __init__(self, perimeter, area, color, radius, diametr):
        super().__init__(perimeter, area, color)
        if not (isinstance(radius, int) and radius > 0) or not (isinstance(diametr, int) and diametr == 2*radius):
            raise ValueError('Invalid value')
        self.radius = radius
        self.diametr = diametr
    def __str__(self):
            return f"Circle: Периметр {self.perimeter}, площадь {self.area}, цвет фигуры {self.color}, радиус {self.radius}, диаметр {self.diametr}."

    def __add__(self):
            return self.perimeter + self.area

    def __eq__(self, other):
            if isinstance(other, Circle):
                return self.radius == other.radius
            else: return False


class PolygonList(list):
    def __init__(self,name):
        super().__init__()
        self.name = name
    def append(self, p_object):
        if isinstance(p_object, Polygon):
            super().append(p_object)
        else:
            raise TypeError(f"Invalid type {type(p_object).__name__}")
    def print_colors(self):
        for i, polygon in enumerate(self, start=1):
            print(f"{i} многоугольник: {polygon.color}")
    def print_count(self):
        print(len(self))


class CircleList(list):
    def __init__(self,name):
        super().__init__()
        self.name = name
    def extend(self, iterable):
        for item in iterable:
            if isinstance(item, Circle):
                super().append(item)

    def print_colors(self):
        for i, circle in enumerate(self, start=1):
            print(f"{i} окружность: {circle.color}")
    def total_area(self):
        total = sum(item.area for item in self if isinstance(item, Circle))
        print(total)
