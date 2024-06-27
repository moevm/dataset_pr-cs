class Figure:
    
    def __init__(self, perimeter = 0, area = 0, color = ''):
        if not(isinstance(perimeter, int) and isinstance(area, int) and color in ['r', 'g', 'b'] and perimeter >0 and area > 0):
            raise ValueError('Invalid value')
        self.perimeter = perimeter
        self.area = area
        self.color = color


class Polygon(Figure):
    
    def __init__(self, perimeter = 0, area = 0, color = '', angle_count = 0, equilateral = True, biggest_angle = 0):
        super().__init__(perimeter, area, color)
        
        if not(isinstance(angle_count, int) and isinstance(equilateral, bool) and isinstance(biggest_angle, int) and angle_count > 2 and biggest_angle > 0):
            raise ValueError('Invalid value')
        self.angle_count = angle_count
        self.equilateral = equilateral
        self.biggest_angle = biggest_angle

    def __str__(self):
        return "Polygon: Периметр " + str(self.perimeter) + ", площадь " + str(self.area) + ", цвет фигуры " + self.color + ", количество углов " + str(self.angle_count) + ", равносторонний " + str(self.equilateral) + ", самый большой угол " + str(self.biggest_angle) + "."
    
    def __add__(self):
        return self.perimeter + self.area
    
    def __eq__(self, other):
        return (self.perimeter == other.perimeter and self.area == other.area and self.angle_count == other.angle_count)

    
class Circle(Figure):
    
    def __init__(self, perimeter = 0, area = 0, color = '', radius = 0, diametr = 0):
        super().__init__(perimeter, area, color)

        if not(isinstance(radius, int) and isinstance(diametr, int) and radius > 0 and diametr > 0 and diametr == radius*2):
            raise ValueError('Invalid value')
        self.radius = radius
        self.diametr = diametr
    
    def __str__(self):
        return "Circle: Периметр " + str(self.perimeter) + ", площадь " + str(self.area) + ", цвет фигуры " + self.color + ", радиус " + str(self.radius) + ", диаметр " + str(self.diametr) + "."
    
    def __add__(self): 
        return self.area + self.perimeter
    
    def __eq__(self, other):
        return (self.radius == other.radius)


class PolygonList(list):
    def __init__(self, name):
        super().__init__()
        self.name = name


    def append(self, p_object):
        if isinstance(p_object, Polygon):
            super().append(p_object)
        else:
            raise TypeError("Invalid type " + str(type(p_object)))

        
    def print_colors(self):
        for index in range(0, len(self)):
            print(str(index + 1) + " многоугольник: " + self[index].color)

            
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
        for index in range(0, len(self)):
            print(str(index + 1) + " окружность: " + self[index].color)


    def total_area(self): 
        answer = 0
        for item in self:
            answer+=item.area
        print(answer)
