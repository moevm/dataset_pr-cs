class Figure:
    def __init__(self, perimeter, area, color):
        if type(perimeter) != int or type(area) != int or perimeter <= 0 or area <= 0 or color not in ['r', 'b', 'g']:
            raise ValueError('Invalid value')
        self.perimeter = perimeter
        self.area = area
        self.color = color
        
class Polygon(Figure):
    def __init__(self, perimeter, area, color, angle_count, equilateral, biggest_angle):
        super().__init__(perimeter, area, color)
        if type(angle_count) != int or angle_count <= 2 or type(equilateral) != bool or type(biggest_angle) != int or biggest_angle <= 0:
            raise ValueError('Invalid value')
        self.angle_count = angle_count
        self.equilateral = equilateral
        self.biggest_angle = biggest_angle
    
    def __str__(self):
        return f"Polygon: Периметр {self.perimeter}, площадь {self.area}, цвет фигуры {self.color}, количество углов {self.angle_count}, равносторонний {self.equilateral}, самый большой угол {self.biggest_angle}."
    
    def __add__(self):
        return self.perimeter + self.area
    
    def __eq__(self, other):
        if isinstance(other, Polygon):
            return self.perimeter == other.perimeter and self.area == other.area and self.angle_count == other.angle_count
        return False
        
        
class Circle(Figure):
    def __init__(self, perimeter, area, color, radius, diametr):
        super().__init__(perimeter, area, color)
        if type(radius) != int or radius <= 0 or type(diametr) != int or diametr <= 0 or diametr != 2 * radius:
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
        return False
        
        
class PolygonList(list):
    def __init__(self, name):
        super().__init__()
        self.name = name
    
    def append(self, p_object):
        if isinstance(p_object, Polygon):
            super().append(p_object)
        else:
            raise TypeError(f"Invalid type {type(p_object)}")
    
    def print_colors(self):
        result = ""
        for i, p in enumerate(self, start=1):
            result += f"{i} многоугольник: {p.color}"
            if i==1:
                result +="\n"
        print(result)
    
    def print_count(self):
        print(len(self))
    

class CircleList(list):
    def __init__(self, name):
        super().__init__()
        self.name = name
        
    def extend(self, iterable):
        for item in iterable:
            if isinstance(item, Circle):
                super().append(item)
    
    def print_colors(self):
        result = ""
        for i, c in enumerate(self, start=1):
            result += f"{i} окружность: {c.color}"
            if i==1:
                result +="\n"
        print(result)
    
    def total_area(self):
        total_area = 0
        for c in self:
            total_area += c.area
        print(total_area)
