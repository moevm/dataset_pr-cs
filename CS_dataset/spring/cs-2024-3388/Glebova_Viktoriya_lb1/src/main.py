from collections.abc import Iterable


class Figure:
    perimeter: int
    area: int
    color: str
    
    def __init__(self, perimetr, area, color):
        if perimetr <= 0 or area <= 0 or color != 'r' and color != 'g' and color != 'b':
            raise ValueError("Invalid value")
        self.area = area
        self.perimeter = perimetr
        self.color = color


class Polygon(Figure):
    angle_count: int
    equilateral: bool
    biggest_angle: int
    
    def __init__(self, perimetr, area, color, angle_counter, is_equilateral, biggest_angle):
        super().__init__(perimetr, area, color)
        if angle_counter <= 2 or biggest_angle <= 0:
            raise ValueError("Invalid value")
        if type(is_equilateral) != bool:
            raise TypeError(f"Invalid type {type(is_equilateral)}")
        self.angle_count = angle_counter
        self.biggest_angle = biggest_angle
        self.equilateral = is_equilateral
        
    def __str__(self):
        return f"Polygon: Периметр {self.perimeter}, " \
 f"площадь {self.area}, " \
 f"цвет фигуры {self.color}, " \
 f"количество углов {self.angle_count}, " \
 f"равносторонний {self.equilateral}, " \
 f"самый большой угол {self.biggest_angle}."

    
    def __add__(self):
        return self.area + self.perimeter
    
    def __eq__(self, other):
        return self.perimeter == other.perimeter \
               and self.area == other.area \
               and self.angle_count == other.angle_count


class Circle(Figure):
    radius: int
    diametr: int
    
    def __init__(self, perimetr, area, color, radius, diametr):
        super().__init__(perimetr, area, color)
        if radius <= 0 or diametr != 2 * radius:
            raise ValueError("Invalid value")
        self.radius = radius
        self.diametr = diametr
        
    def __str__(self):
        return f"Circle: Периметр {self.perimeter}, " \
               f"площадь {self.area}, " \
               f"цвет фигуры {self.color}, " \
               f"радиус {self.radius}, " \
               f"диаметр {self.diametr}."
    
    def __add__(self):
        return self.area + self.perimeter
    
    def __eq__(self, other):
        return self.radius == other.radius


class PolygonList(list):
    name: str
    
    def __init__(self, name):
        super().__init__()
        self.name = name
        
    def append(self, p_object) -> None:
        if type(p_object) != Polygon:
            raise TypeError(f"Invalid type {type(p_object)}")
        super().append(p_object)
        
    def print_colors(self):
        for i in range(len(self)):
            print(f"{i + 1} многоугольник: {self[i].color}")
            
    def print_count(self):
        print(len(self))


class CircleList(list):
    name: str
    
    def __init__(self, name):
        super().__init__()
        self.name = name
        
    def extend(self, iterable: Iterable) -> None:
        circles_list = [i for i in iterable if type(i)==Circle]
        super().extend(circles_list)
        
    def print_colors(self):
        for i in range(len(self)):
            print(f"{i + 1} окружность: {self[i].color}")
            
    def total_area(self):
        print(sum(i.area for i in self))
