class Figure:
    def __init__(self, perimeter, area, color):    
        if not (isinstance(perimeter, int) and (perimeter > 0) and isinstance(area, int) and (area > 0) and color in ['r', 'b', 'g']):
            raise ValueError("Invalid value")
        self.perimeter = perimeter
        self.area = area
        self.color = color

class Polygon(Figure):
    def __init__(self, perimeter, area, color, angle_count, equilateral, biggest_angle):
        super().__init__(perimeter,area,color)
        self.angle_count = angle_count
        self.equilateral = equilateral
        self.biggest_angle = biggest_angle
        if (type(angle_count) is not int) or angle_count < 2:
            raise ValueError('Invalid value')
        if type(equilateral) is not bool:
            raise ValueError('Invalid value')
        if (type(biggest_angle) is not int) or biggest_angle <= 0:
            raise ValueError('Invalid value')

    def __str__(self):
        return f"Polygon: Периметр {self.perimeter}, площадь {self.area}, цвет фигуры {self.color}, количество углов {self.angle_count}, равносторонний {self.equilateral}, самый большой угол {self.biggest_angle}." 

    def __add__(self):
        return self.perimeter + self.area

    def __eq__(self, other):
        return self.perimeter == other.perimeter and self.area == other.area and self.angle_count == other.angle_count
    
class Circle(Figure):
    def __init__(self, perimeter, area, color, radius, diametr):
        super().__init__(perimeter,area,color)
        self.radius = radius
        self.diametr = diametr
        if (type(radius) is not int) or radius < 0:
            raise ValueError('Invalid value')
        if (type(diametr) is not int) or diametr != radius * 2:
            raise ValueError('Invalid value')

    def __str__(self):
        return f"Circle: Периметр {self.perimeter}, площадь {self.area}, цвет фигуры {self.color}, радиус {self.radius}, диаметр {self.diametr}." 

    def __add__(self):
        return self.perimeter + self.area

    def __eq__(self, other):
        return self.radius == other.radius
    
class PolygonList(list):
    def __init__(self, name):
        super().__init__(self)
        self.name = name
        
    def append(self, p_object):
        super().append(p_object)
        if type(p_object) is not Polygon:
            raise TypeError(f'Invalid type {type(p_object)}')
            
    def print_colors(self):
        for i in range(len(self)):
            print(f'{i + 1} многоугольник: {self[i].color}')
            i+=1
            
    def print_count(self):
        print(len(self))

class CircleList(list):
    def __init__(self, name):
        super().__init__(self)
        self.name = name
        
    def extend(self, iterable):
        for item in iterable:
            if type(item) is Circle:
                super().append(item)
    def print_colors(self):
        for i in range(len(self)):
            print(f'{i + 1} окружность: {self[i].color}')
            i+=1
            
    def total_area(self):
        total_area = 0
        for item in self:
            total_area += item.area
        print(total_area)
