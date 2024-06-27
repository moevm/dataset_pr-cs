class Figure: 
    def __init__(self, perimeter, area, color):
        if perimeter <= 0 or area <= 0 or color not in "rgb":
            raise ValueError("Invalid value")
        self.perimeter = perimeter
        self.area = area
        self.color = color

class Polygon(Figure):
    def __init__(self, perimeter, area, color, angle_count, is_equilateral, biggest_angle):
        super().__init__(perimeter, area, color)
        if angle_count <= 2 or biggest_angle <= 0 or type(is_equilateral) != bool:
            raise ValueError("Invalid value")
        self.angle_count = angle_count
        self.equilateral = is_equilateral
        self.biggest_angle = biggest_angle

    def __str__(self):
        return f"Polygon: Периметр {self.perimeter}, площадь {self.area}, цвет фигуры {self.color}, количество углов {self.angle_count}, равносторонний {self.equilateral}, самый большой угол {self.biggest_angle}."

    def __add__(self):
        return self.area + self.perimeter

    def __eq__(self, second_figure):
        return self.perimeter == second_figure.perimeter and self.area == second_figure.area and self.angle_count == second_figure.angle_count

class Circle(Figure):
    def __init__(self, perimeter, area, color, radius, diametr):
        super().__init__(perimeter, area, color)
        if radius <= 0 or diametr != 2*radius:
            raise ValueError("Invalid value")
        self.radius = radius
        self.diametr = diametr
    
    def __str__(self):
        return f"Circle: Периметр {self.perimeter}, площадь {self.area}, цвет фигуры {self.color}, радиус {self.radius}, диаметр {self.diametr}."

    def __add__(self):
        return self.area + self.perimeter

    def __eq__(self, second_figure):
        return self.radius == second_figure.radius

class PolygonList(list):
    def __init__(self, name):
        super().__init__()
        self.name = name

    def append(self, object_p):
        if isinstance(object_p, Polygon):
            super().append(object_p)
        else:
            raise TypeError(f"Invalid type {type(object_p)}")
    
    def print_colors(self):
        for i in range(len(self)):
            print(f"{i+1} многоугольник: {self[i].color}")
    
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
        for i in range(len(self)):
            print(f"{i + 1} окружность: {self[i].color}")

    def total_area(self):
        print(sum(i.area for i in self))