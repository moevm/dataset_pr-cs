class Transport:
    def __init__(self, average_speed, max_speed, price, cargo, color):
        if (isinstance(average_speed, int) and average_speed > 0) and (isinstance(max_speed, int) and max_speed > 0) and (isinstance(price, int) and price > 0) and (color == 'w' or color == 'g' or color == 'b') and (isinstance(cargo, bool)):
            self.average_speed = average_speed
            self.max_speed = max_speed
            self.price = price
            self.cargo = cargo
            self.color = color
        else:
            raise ValueError ('Invalid value')
        
class Car(Transport): 
    
    def __init__(self, average_speed, max_speed, price, cargo, color, power, wheels):
        
        super().__init__(average_speed, max_speed, price, cargo, color)
        if not (isinstance(power, int) and power > 0 and wheels > 0 and wheels < 11):
            raise ValueError ('Invalid value')
        self.power = power
        self.wheels = wheels
    
    def __str__(self): 
        return f"Car: средняя скорость {self.average_speed}, максимальная скорость {self.max_speed}, цена {self.price}, грузовой {self.cargo}, цвет {self.color}, мощность {self.power}, количество колес {self.wheels}."

    def __add__(self): 
        return self.average_speed + self.max_speed

    def __eq__(self, other): 
        return self.wheels == other.wheels and self.power == other.power and self.average_speed == other.average_speed and self.max_speed == other.max_speed

    
class Plane(Transport):
    
    def __init__(self, average_speed, max_speed, price, cargo, color, load_capacity, wingspan):
        super().__init__(average_speed, max_speed, price, cargo, color)
        if not (isinstance(load_capacity, int) and load_capacity > 0 and isinstance(wingspan, int) and wingspan > 0):
            raise ValueError ('Invalid value')
        self.load_capacity = load_capacity
        self.wingspan = wingspan
   
    def __str__(self): 
        return f"Plane: средняя скорость {self.average_speed}, максимальная скорость {self.max_speed}, цена {self.price}, грузовой {self.cargo}, цвет {self.color}, грузоподъемность {self.load_capacity}, размах крыльев {self.wingspan}."

    def __add__(self): 
        return self.average_speed + self.max_speed
    
    def __eq__(self, other): 
        return self.wingspan == other.wingspan
    
class Ship(Transport):
    def __init__(self, average_speed, max_speed, price, cargo, color, length, side_height):
        super().__init__(average_speed, max_speed, price, cargo, color)
        if not (isinstance(length, int) and length > 0 and isinstance(side_height, int) and side_height > 0):
            raise ValueError ('Invalid value')
        self.length = length
        self.side_height = side_height
    
    def __str__(self): 
        return f"Ship: средняя скорость {self.average_speed}, максимальная скорость {self.max_speed}, цена {self.price}, грузовой {self.cargo}, цвет {self.color}, длина {self.length}, высота борта {self.side_height}."

    def __add__(self): 
        return self.average_speed + self.max_speed    
    
    def __eq__(self, other): 
        return self.length == other.length and self.side_height == other.side_height

class CarList(list):
    
    def __init__(self, name):
        super().__init__()
        self.name = name
           
    def append(self, p_object): 
        if isinstance(p_object, Car):
            super().append(p_object)
        else:
            raise TypeError(f'Invalid type <{type(p_object)}>')

    def print_colors(self): 
        print('\n'.join([f"{idx} автомобиль: {car.color}" for idx, car in enumerate(self, start=1)]))
            
    def print_count(self): 
        print(len(self))
        
    
class PlaneList(list):
    def __init__(self, name):
        super().__init__()
        self.name = name

    def extend(self, __iterable):
        super().extend(i for i in __iterable if isinstance(i, Plane))
        
    def print_colors(self): 
        print('\n'.join([f"{idx} самолет: {plane.color}" for idx, plane in enumerate(self, start=1)]))
            
    def total_speed(self): 
        print(sum(plane.average_speed for plane in self))
        
class ShipList(list):
    def __init__(self, name):
        super().__init__()
        self.name = name

    def append(self, p_object): 
        if isinstance(p_object, Ship):
            super().append(p_object)
        else:
            raise TypeError(f'Invalid type <{type(p_object)}>')

    def print_colors(self): 
        print('\n'.join([f"{idx} корабль: {ship.color}" for idx, ship in enumerate(self, start=1)]))
            
    def print_ship(self): 
        res = [f"Длина корабля №{idx} больше 150 метров" for idx, ship in enumerate(self, start=1) if ship.length > 150]
        print('\n'.join(res))
