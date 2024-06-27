class Figure:
    def __init__(self, perimeter: int, area: int, color: str) -> None:
        if not all(isinstance(x, int) and x > 0 for x in (perimeter, area)) or color not in {'r', 'b', 'g'}:
            raise ValueError('Invalid parameters')
        self.perimeter, self.area, self.color = perimeter, area, color

    def __str__(self):
        return f'{self.__class__.__name__}: Периметр {self.perimeter}, площадь {self.area}, цвет фигуры {self.color}'

class Polygon(Figure):
    def __init__(self, perimeter: int, area: int, color: str, angle_count: int, equilateral: bool, biggest_angle: int) -> None:
        if not all(isinstance(x, int) and x > 0 for x in (perimeter, angle_count, area, biggest_angle)) or angle_count < 2 or not isinstance(equilateral, bool):
            raise ValueError('Invalid parameters')
        super().__init__(perimeter, area, color)
        self.angle_count, self.equilateral, self.biggest_angle = angle_count, equilateral, biggest_angle

    def __str__(self):
        return f'{super().__str__()}, количество углов {self.angle_count}, равносторонний {self.equilateral}, самый большой угол {self.biggest_angle}.'
    
    def __add__(self):
        return self.area + self.perimeter

    def __eq__(self, other):
        return isinstance(other, Polygon) and super().__eq__(other) and self.angle_count == other.angle_count and self.perimeter == other.perimeter and self.area == other.area 

class Circle(Figure):
    def __init__(self, perimeter: int, area: int, color: str, radius: int, diametr: int) -> None:
        super().__init__(perimeter, area, color)
        if not all(isinstance(x, int) and x > 0 for x in (radius, diametr)) or diametr != 2 * radius:
            raise ValueError('Invalid parameters')
        
        self.radius, self.diametr = radius, diametr

    def __str__(self):
        return f'{super().__str__()}, радиус {self.radius}, диаметр {self.diametr}.'
    
    def __add__(self):
        return self.area + self.perimeter

    def __eq__(self, other):
        return isinstance(other, Circle) and super().__eq__(other) and self.radius == other.radius

class PolygonList(list):
    def __init__(self, name: str) -> None:
        super().__init__()
        self.name = name

    def append(self, p_object):
        if isinstance(p_object, Polygon):
            super().append(p_object)
        else:
            raise TypeError(f"Invalid type {type(p_object)}")

    def print_colors(self):
        for i, polygon in enumerate(self, 1):
            print(f"{i} многоугольник: {polygon.color}")

    def print_count(self):
        print(len(self))

class CircleList(list):
    def __init__(self, name: str) -> None:
        super().__init__()
        self.name = name

    def extend(self, iterable):
        super().extend(filter(lambda x: isinstance(x, Circle), iterable))

    def print_colors(self):
        for i, circle in enumerate(self, 1):
            print(f"{i} окружность: {circle.color}")

    def total_area(self):
        print(sum(circle.area for circle in self))
        