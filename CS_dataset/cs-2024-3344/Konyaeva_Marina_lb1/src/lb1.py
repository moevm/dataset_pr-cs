class Figure:
    def __init__(self, perimeter, area, color):
        if not (
            isinstance(perimeter, int)
            and isinstance(area, int)
            and isinstance(color, str)
            and area > 0
            and perimeter > 0
            and color in "rgb"
        ):
            raise ValueError("Invalid value")
        self.perimeter = perimeter
        self.area = area
        self.color = color
        
    def __add__(self):
        return self.area + self.perimeter    

class Polygon(Figure):  # Наследуется от класса Figure
    def __init__(self, perimeter, area, color, angle_count, equilateral, biggest_angle):
        super().__init__(perimeter, area, color)
        if not (
            isinstance(angle_count, int)
            and isinstance(equilateral, bool)
            and isinstance(biggest_angle, int)
            and biggest_angle > 0
            and angle_count > 2
        ):
            raise ValueError("Invalid value")
        self.angle_count = angle_count
        self.equilateral = equilateral
        self.biggest_angle = biggest_angle

    def __str__(self):
        return (f'Polygon: Периметр {self.perimeter}, площадь {self.area}, цвет фигуры {self.color}, количество углов {self.angle_count}, равносторонний {self.equilateral}, самый большой угол {self.biggest_angle}.')
    
    def __eq__(self, other):
        if self.area == other.area and self.perimeter == other.perimeter and self.angle_count == other.angle_count:
            return True
        return False

class Circle(Figure):  # Наследуется от класса Figure
    def __init__(self, perimeter, area, color, radius, diametr):
        super().__init__(perimeter, area, color)
        if not (
                isinstance(radius, int)
                and isinstance(diametr, int)
                and radius > 0
                and diametr > 0
                and 2 * radius == diametr
        ):
            raise ValueError("Invalid value")
        self.radius = radius
        self.diametr = diametr

    def __str__(self):
        return (f'Circle: Периметр {self.perimeter}, площадь {self.area}, цвет фигуры {self.color}, радиус {self.radius}, диаметр {self.diametr}.')

    def __eq__(self, other):
        if self.area == other.area and self.perimeter == other.perimeter:
            return True
        return False

class PolygonList(list):
    def __init__(self, name):
        super().__init__()
        self.name = name

    def append(self, p_object):
        if not isinstance(p_object, Polygon):
            raise TypeError(f"Invalid type {type(p_object)}")
        super().append(p_object)

    def print_colors(self):
        for i in range(len(self)):
            print (f"{i+1} многоугольник: {self[i].color}")

    def print_count(self):
        print(len(self))


class CircleList(list):
    def __init__(self, name):
        super().__init__()
        self.name = name

    def extend(self,iterable):
        for i in iterable:
            if isinstance(i, Circle):
                super().append(i)

    def print_colors(self):
        for i in range(len(self)):
            print (f"{i+1} окружность: {self[i].color}")

    def total_area(self):
        result = 0
        for i in self:
            result+= i.area
        print(result)
