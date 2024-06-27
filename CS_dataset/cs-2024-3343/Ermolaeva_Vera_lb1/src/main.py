class Transport:
    def __init__(self, average_speed, max_speed, price, cargo, color):
        if not isinstance(average_speed, int) or not isinstance(max_speed, int) or not isinstance(price, int) or not isinstance(cargo, bool):
            raise ValueError("Invalid value")
        
        if average_speed <= 0 or max_speed <= 0 or price <= 0 or color not in "wgb":
            raise ValueError("Invalid value")

        self.average_speed = average_speed
        self.max_speed = max_speed
        self.price = price
        self.cargo = cargo
        self.color = color
    
class Car(Transport):
    def __init__(self, average_speed, max_speed, price, cargo, color, power, wheels):
        super().__init__(average_speed, max_speed, price, cargo, color)

        if not isinstance(power, int) or not isinstance(wheels, int):
            raise ValueError("Invalid value")
        
        if power <= 0 or wheels <= 0 or wheels > 10:
            raise ValueError("Invalid value")

        self.power = power
        self.wheels = wheels
    
    def __str__(self): 
        return f"Car: средняя скорость {self.average_speed}, максимальная скорость {self.max_speed}, цена {self.price}, грузовой {self.cargo}, цвет {self.color}, мощность {self.power}, количество колес {self.wheels}."

    def __add__(self): 
        return self.average_speed + self.max_speed

    def __eq__(car1, car2): 
        if car1.wheels == car2.wheels and car1.average_speed == car2.average_speed and car1.max_speed == car2.max_speed and car1.power == car2.power:
            return True
        return False

class Plane(Transport):
    def __init__(self, average_speed, max_speed, price, cargo, color, load_capacity, wingspan):
        super().__init__(average_speed, max_speed, price, cargo, color)

        if not isinstance(load_capacity, int) or not isinstance(wingspan, int):
            raise ValueError("Invalid value")
        
        if load_capacity <= 0 or wingspan <= 0:
            raise ValueError("Invalid value")

        self.load_capacity = load_capacity
        self.wingspan = wingspan

    def __str__(self): 
        return f"Plane: средняя скорость {self.average_speed}, максимальная скорость {self.max_speed}, цена {self.price}, грузовой {self.cargo}, цвет {self.color}, грузоподъемность {self.load_capacity}, размах крыльев {self.wingspan}."

    def __add__(self): 
        return self.average_speed + self.max_speed
    
    def __eq__(plane1, plane2):
        return plane1.wingspan == plane2.wingspan 
    
class Ship(Transport):
    def __init__(self, average_speed, max_speed, price, cargo, color, length, side_height):
        super().__init__(average_speed, max_speed, price, cargo, color)

        if not isinstance(length, int) or not isinstance(side_height, int):
            raise ValueError("Invalid value")
        
        if length <= 0 or side_height <= 0:
            raise ValueError("Invalid value")

        self.length = length
        self.side_height = side_height

    def __str__(self): 
        return f"Ship: средняя скорость {self.average_speed}, максимальная скорость {self.max_speed}, цена {self.price}, грузовой {self.cargo}, цвет {self.color}, длина {self.length}, высота борта {self.side_height}."

    def __add__(self): 
        return self.average_speed + self.max_speed
    
    def __eq__(ship1, ship2):
        return ship1.length == ship2.length and ship1.side_height == ship2.side_height 

class CarList(list):
    def __init__(self, name):
        super().__init__()
        self.name = name

    def append(self, p_object): 
        if not isinstance(p_object, Car):
            raise TypeError(f"Invalid type {type(p_object)}")
        super().append(p_object)

    def print_colors(self): 
        for i in range(len(self)):
            print(f"{i+1} автомобиль: {self[i].color}")
            
    def print_count(self): 
        print(len(self))
        
class PlaneList(list):
    def __init__(self, name):
        super().__init__()
        self.name = name

    def extend(self, iterable):
        if len([i for i in iterable if isinstance(i, Plane)]) == len(iterable):
            super().extend(iterable)  

    def print_colors(self): 
        for i in range(len(self)):
            print(f"{i+1} самолет: {self[i].color}")
            
    def total_speed(self):
        speed = 0
        for i in self:
            speed += int(i.average_speed)
        print(speed)
        
class ShipList(list):            
    def __init__(self, name):
        super().__init__()
        self.name = name

    def append(self, p_object): 
        if not isinstance(p_object, Ship):
            raise TypeError(f"Invalid type {type(p_object)}")
        super().append(p_object)

    def print_colors(self): 
        for i in range(len(self)):
            print(f"{i+1} корабль: {self[i].color}")
            
    def print_ship(self):
        for i in range(len(self)):
            if self[i].length > 150:
                print(f"Длина корабля №{i+1} больше 150 метров")