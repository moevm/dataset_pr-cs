class Figure:
    def __init__(self,perimeter,area,color):
        if not isinstance(perimeter, int) or perimeter < 1:
            raise ValueError('Invalid value')
        self.perimeter = perimeter
        if not isinstance(area, int) or area < 1:
            raise ValueError('Invalid value')
        self.area = area
        if color not in ['r', 'g', 'b']:
            raise ValueError('Invalid value')
        self.color = color
class Polygon(Figure):
    def __init__(self,perimeter,area,color,angle_count,equilateral,biggest_angle):
        super().__init__(perimeter, area,color)
        if not isinstance(angle_count, int) or angle_count < 3:
            raise ValueError('Invalid value')
        self.angle_count = angle_count
        if not isinstance(equilateral, bool):
            raise ValueError('Invalid value')
        self.equilateral = equilateral
        if not isinstance(biggest_angle, int) or biggest_angle < 1:
            raise ValueError('Invalid value')
        self.biggest_angle = biggest_angle
    def __str__(self):
        return f"Polygon: Периметр {self.perimeter}, площадь {self.area}, цвет фигуры {self.color}, количество углов {self.angle_count}, равносторонний {self.equilateral}, самый большой угол {self.biggest_angle}."
    def __add__(self):
        return self.perimeter + self.area
    def __eq__(self,other):
        if self.perimeter == other.perimeter and self.area == other.area and self.angle_count == other.angle_count:
            return True
        else:
            return False
class Circle(Figure):
    def __init__(self,perimeter,area,color,radius, diametr):
        super().__init__(perimeter, area,color)
        if not isinstance(radius, int) or radius < 1:
            raise ValueError('Invalid value')
        self.radius = radius
        if not isinstance(diametr, int) or diametr != 2 * radius:
            raise ValueError('Invalid value')
        self.diametr = diametr
    def __str__(self):
        return f"Circle: Периметр {self.perimeter}, площадь {self.area}, цвет фигуры {self.color}, радиус {self.radius}, диаметр {self.diametr}."
    def __add__(self):
        return self.perimeter + self.area
    def __eq__(self,other):
        if self.radius == other.radius:
            return True
        else:
            return False
class PolygonList(list):
    def __init__(self, name):
        super().__init__()
        self.name = name
    def append(self,p_object):
        if isinstance(p_object,Polygon):
            super().append(p_object)
        else:
            raise TypeError(f"invalid type {type(p_object)}")
    def print_colors(self):
        for i in range(len(list(self))):
            print(f"{i+1} многоугольник: {list(self)[i].color}")
    def print_count(self):
        print(len(list(self)))
class CircleList(list):
    def __init__(self, name):
        super().__init__()
        self.name = name
    def extend(self,iterable):
        for element in iterable:
            if isinstance(element,Circle):
                self.append(element)
    def print_colors(self):
        for i in range(len(list(self))):
            print(f"{i+1} окружность: {list(self)[i].color}")
    def total_area(self):
        summ = 0
        for item in list(self):
            summ += item.area
        print(summ)
