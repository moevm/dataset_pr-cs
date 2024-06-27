class Transport:
    def __init__(self, average_speed, max_speed, price, cargo, color):
        if isinstance(average_speed, int) and average_speed>0 and isinstance(max_speed, int) and max_speed>0 and isinstance(price, int) and price>0 and isinstance(cargo,bool) and (cargo==True or cargo==False) and (color=='w' or color=='g' or color=='b'):
            self.average_speed = average_speed
            self.max_speed = max_speed
            self.price = price
            self.cargo = cargo
            self.color = color
        else:
            raise ValueError('Invalid value')
    
class Car(Transport):
    def __init__(self, average_speed, max_speed, price, cargo, color, power, wheels):
        if isinstance(average_speed, int) and average_speed>0 and isinstance(max_speed, int) and max_speed>0 and isinstance(price, int) and price>0 and (cargo==True or cargo==False) and (color=='w' or color=='g' or color=='b') and isinstance(power, int) and power>0 and isinstance(wheels, int) and wheels>0 and wheels<=10:
            super().__init__(average_speed, max_speed, price, cargo, color)
            self.power = power
            self.wheels = wheels
        else:
            raise ValueError('Invalid value')
    
    def __str__(self):
        return f'Car: средняя скорость {self.average_speed}, максимальная скорость {self.max_speed}, цена {self.price}, грузовой {self.cargo}, цвет {self.color}, мощность {self.power}, количество колес {self.wheels}.'

    def __add__(self): 
        return self.average_speed + self.max_speed

    def __eq__(self, other):
        return self.average_speed==other.average_speed and self.max_speed==other.max_speed and self.power==other.power and self.wheels==other.wheels
    
class Plane(Transport):
    def __init__(self, average_speed, max_speed, price, cargo, color, load_capacity, wingspan):
        if isinstance(average_speed, int) and average_speed>0 and isinstance(max_speed, int) and max_speed>0 and isinstance(price, int) and price>0 and (cargo==True or cargo==False) and (color=='w' or color=='g' or color=='b') and isinstance(load_capacity, int) and load_capacity>0 and isinstance(wingspan, int) and wingspan>0:
            super().__init__(average_speed, max_speed, price, cargo, color)
            self.load_capacity = load_capacity
            self.wingspan = wingspan
        else:
            raise ValueError('Invalid value')
    
    def __str__(self): 
        return f'Plane: средняя скорость {self.average_speed}, максимальная скорость {self.max_speed}, цена {self.price}, грузовой {self.cargo}, цвет {self.color}, грузоподъемность {self.load_capacity}, размах крыльев {self.wingspan}.'
    
    def __add__(self): 
        return self.average_speed + self.max_speed
    
    def __eq__(self, other):
        return self.wingspan==other.wingspan
        
class Ship(Transport):
    def __init__(self, average_speed, max_speed, price, cargo, color, length, side_height):
        if isinstance(average_speed, int) and average_speed>0 and isinstance(max_speed, int) and max_speed>0 and isinstance(price, int) and price>0 and (cargo==True or cargo==False) and (color=='w' or color=='g' or color=='b') and isinstance(length, int) and length>0 and isinstance(side_height, int) and side_height>0:
            super().__init__(average_speed, max_speed, price, cargo, color)
            self.length = length
            self.side_height = side_height
        else:
            raise ValueError('Invalid value')
    
    def __str__(self): 
        return f'Ship: средняя скорость {self.average_speed}, максимальная скорость {self.max_speed}, цена {self.price}, грузовой {self.cargo}, цвет {self.color}, длина {self.length}, высота борта {self.side_height}.'

    def __add__(self): 
        return self.average_speed + self.max_speed
    
    def __eq__(self, other): 
        return self.length==other.length and self.side_height==other.side_height
    
class CarList(list):
    def __init__(self, name):
        self.name = name
           
    def append(self, p_object): 
        if isinstance(p_object, Car):
            super().append(p_object)
        else:
            raise TypeError(f'Invalid type {type(p_object)}')

    def print_colors(self):
        i = 1
        for item in self:
            print(f'{i} автомобиль: {item.color}')
            i+=1
            
    def print_count(self):
        print(len(self))
        
class PlaneList(list):
    def __init__(self, name):
        self.name = name

    def extend(self, iterable): 
        super().extend(list(filter(lambda x: isinstance(x,Plane),iterable)))
        
    def print_colors(self): 
        i = 1
        for item in self:
            print(f'{i} самолет: {item.color}')
            i+=1
            
    def total_speed(self): 
        print(sum(item.average_speed for item in self))
        
class ShipList(list):
    def __init__(self, name):
        self.name = name
           
    def append(self, p_object): 
        if isinstance(p_object, Ship):
            super().append(p_object)
        else:
            raise TypeError(f'Invalid type {type(p_object)}')

    def print_colors(self): 
        i = 1
        for item in self:
            print(f'{i} корабль: {item.color}')
            i+=1
            
    def print_ship(self):
        i = 1
        for item in self:
            if item.length>150:
                print(f'Длина корабля №{i} больше 150 метров')
            i+=1