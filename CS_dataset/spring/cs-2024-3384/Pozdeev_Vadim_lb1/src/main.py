class Figure:
    def __init__(self, perimeter, area, color):
        if not (color == 'r' or color=='g' or color =='b') or not isinstance(perimeter, int) or not isinstance(area, int) or area <= 0 or perimeter <= 0:
            raise ValueError("Invalid value")
        self.perimeter = perimeter
        self.area = area
        self.color = color
    def __add__(self):  
        return self.perimeter + self.area

class Polygon(Figure):
    def __init__(self, perimeter, area, color, angle_count, equilateral, biggest_angle):
            Figure.__init__(self, perimeter, area, color)
            if not isinstance(angle_count, int) or angle_count < 3 or not isinstance(equilateral, bool) or not isinstance(biggest_angle, int) or biggest_angle <= 0:
                raise ValueError("Invalid value")
            self.angle_count = angle_count
            self.equilateral = equilateral
            self.biggest_angle = biggest_angle
    
    def __str__(self):
        return f'Polygon: Периметр {self.perimeter}, площадь {self.area}, цвет фигуры {self.color}, количество углов {self.angle_count}, равносторонний {self.equilateral}, самый большой угол {self.biggest_angle}.'
    
    def __eq__(self, other):
        return self.area == other.area and self.perimeter == self.perimeter and self.angle_count == other.angle_count
    
class Circle(Figure):
    def __init__(self, perimeter, area, color, radius, diametr):
        Figure.__init__(self, perimeter, area, color)
        if not isinstance(radius, int) or not isinstance(diametr, int) or radius <= 0 or diametr!=2*radius:
            raise ValueError("Invalid value")
        self.radius = radius
        self.diametr = diametr
    
    def __str__(self):
        return f'Circle: Периметр {self.perimeter}, площадь {self.area}, цвет фигуры {self.color}, радиус {self.radius}, диаметр {self.diametr}.'
    
    
    def __eq__(self, other):
        return self.radius == other.radius


class PolygonList(list):
    def __init__(self, name):
        self.name = name
                   
    def append(self, p_object):
        if not isinstance(p_object, Polygon):
            raise TypeError(f"Invalid type {type(p_object)}")
        super().append(p_object)
                    
    def print_colors(self):
        k = 1 
        for i in self:
            print(f'{k} многоугольник: {i.color}')
            k+=1
            
    def print_count(self):
        print(len(self)) 

class CircleList(list):
    def __init__(self, name):
        self.name = name
           
    def extend(self, iterable):
        for i in iterable:
            if isinstance(i, Circle):
                super().append(i)
                
    def print_colors(self): 
        k = 1 
        for i in self:
            print(f'{k} окружность: {i.color}')
            k+=1
        
    def total_area(self): 
        suma = 0
        for i in self:
            suma+=i.area
        print(suma)
