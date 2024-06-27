class Figure:
    def __init__(self, perimeter, area, color):
        if not (isinstance(perimeter, int)) or not (isinstance(area, int)) or (perimeter <= 0) or (area <= 0) or (color not in ['r', 'g', 'b']):
            raise ValueError('Invalid value')
        else:
            self.perimeter = perimeter
            self.area = area
            self.color = color


class Polygon(Figure):
    def __init__(self, perimeter, area, color, angle_count, equilateral, biggest_angle):
        super().__init__(perimeter, area, color)
        if (angle_count <= 2) or not (isinstance(equilateral, bool)) or not (isinstance(biggest_angle, int)) or not (isinstance(angle_count, int)) or (biggest_angle <= 0):
            raise ValueError('Invalid value')
        else:
            self.angle_count = angle_count
            self.equilateral = equilateral
            self.biggest_angle = biggest_angle

    def __str__(self):
        return "Polygon: Периметр {0}, площадь {1}, цвет фигуры {2}, количество углов {3}, равносторонний {4}, самый большой угол {5}.".format(self.perimeter, self.area, self.color, self.angle_count, self.equilateral, self.biggest_angle)

    def __add__(self):
        return self.area + self.perimeter

    def __eq__(self, other): 
        return (self.area == other.area) and (self.perimeter == other.perimeter) and (self.angle_count == other.angle_count)
        
        
class Circle(Figure): 
    def __init__(self, perimeter, area, color, radius, diametr):
        super().__init__(perimeter, area, color)
        if not (isinstance(radius, int)) or (radius <= 0) or not (isinstance(diametr, int)) or (diametr <= 0) or (diametr != 2 * radius):
            raise ValueError('Invalid value')
        else:
            self.radius = radius
            self.diametr = diametr
            
    def __str__(self):
        return "Circle: Периметр {0}, площадь {1}, цвет фигуры {2}, радиус {3}, диаметр {4}.".format(self.perimeter, self.area, self.color, self.radius, self.diametr)
    
    def __add__(self): 
        return self.area + self.perimeter
    
    def __eq__(self, other):
        return self.radius == other.radius
    
    
class PolygonList(list):
    def __init__(self, name):
        super().__init__()
        self.name = name
           
    def append(self, p_object): 
        if isinstance(p_object, Polygon):
            super().append(p_object)
        else:
            raise TypeError('Invalid type ' + type(p_object).__name__())
            
    def print_colors(self): 
        for i, polygon in enumerate(self, start=1):
            print(str(i) + ' многоугольник: ' + polygon.color)
            
    def print_count(self): 
        print(len(self))


class CircleList(list):
    def __init__(self, name):
        super().__init__()
        self.name = name
    
    def extend(self, iterable):
        if all(isinstance(x, Circle) for x in iterable):
            super().extend(iterable)
    
    def print_colors(self):
        for i, circle in enumerate(self, start=1):
            print(str(i) + ' окружность: ' + circle.color)
        
    def total_area(self):
        print(sum([x.area for x in self]))