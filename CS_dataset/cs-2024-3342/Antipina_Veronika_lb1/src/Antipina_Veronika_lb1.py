class Figure:
    
    def __init__(self,perimeter,area,color):
        if (isinstance(perimeter,int) and perimeter>0 and isinstance(area,int) and area>0 and color in ['r','g','b'])==False:
            raise ValueError('Invalid value')
        else:
            self.perimeter = perimeter
            self.area = area
            self.color = color

class Polygon(Figure):
    def __init__(self,perimeter,area,color,angle_count,equilateral,biggest_angle):
        super().__init__(perimeter,area,color)
        
        if (isinstance(angle_count,int) and angle_count>2 and isinstance(equilateral,bool) and isinstance(biggest_angle,int) and biggest_angle>0)==False:
            raise ValueError("Invalid Value")
        else:
            self.angle_count = angle_count
            self.equilateral = equilateral
            self.biggest_angle = biggest_angle

    def __str__(self):
        return f"Polygon: Периметр {self.perimeter}, площадь {self.area}, цвет фигуры {self.color}, количество углов {self.angle_count}, равносторонний {self.equilateral}, самый большой угол {self.biggest_angle}."
    def __add__(self):
        return self.perimeter+self.area
    def __eq__(self,comp):
        if(self.perimeter == comp.perimeter and self.area == comp.area and self.angle_count == comp.angle_count):
            return True
        else:
            return False

class Circle(Figure):
    def __init__(self,perimeter,area,color,radius,diametr):
        super().__init__(perimeter,area,color)
        if (isinstance(radius,int) and radius>0 and isinstance(diametr,int) and diametr==2*radius)==False:
            raise ValueError("Invalid value")
        self.radius = radius
        self.diametr = diametr

    def __str__(self):
        return f"Circle: Периметр {self.perimeter}, площадь {self.area}, цвет фигуры {self.color}, радиус {self.radius}, диаметр {self.diametr}."
    def __add__(self):
        return self.area+self.perimeter
    def __eq__(self,comp):
        if self.radius == comp.radius:
            return True
        else:
            return False

class PolygonList(list):
    def __init__(self,name):
        super().__init__()
        self.name = name
    def append(self,p_object):
        if isinstance(p_object,Polygon):
            super().append(p_object)
        else:
            t = type(p_object)
            raise TypeError(f'Invalid type <{t}>')
    
    def print_colors(self):
        for i in range(1,len(self)+1):
            print(f"{i} многоугольник: {self[i-1].color}")
    
    def print_count(self):
        print(len(self))

class CircleList(list):
    def __init__(self,name):
        super().__init__()
        self.name = name
    def extend(self,iterable):
        for new in iterable:
            if isinstance(new,Circle):
                super().extend([new])

    
    def print_colors(self):
        for i in range(1,len(self)+1):
            print(f"{i} окружность: {self[i-1].color}")
    
    def total_area(self):
        s = 0
        for x in self:
            s+=x.area
        print(s)