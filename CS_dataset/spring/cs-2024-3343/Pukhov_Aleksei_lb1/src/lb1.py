class Transport:
    def __init__(self, average_speed, max_speed, price, cargo, color):
        self.verify_value_transport(average_speed, max_speed, price, cargo, color)
        self.average_speed = average_speed
        self.max_speed = max_speed
        self.price = price
        self.cargo = cargo
        self.color = color
    
    @classmethod
    def verify_value_transport(cls, average_speed, max_speed, price, cargo, color):
        if not isinstance(average_speed, int) or average_speed <= 0 or not isinstance(max_speed, int) or max_speed <= 0 or not isinstance(price, int) or price <= 0 or not isinstance(cargo, bool) or not color in ('w', 'g', 'b'):
            raise ValueError('Invalid value')

    
class Car(Transport):
    def __init__(self, average_speed, max_speed, price, cargo, color , power , wheels):
        super().__init__(average_speed, max_speed, price, cargo, color)
        self.verify_value_car(wheels, power)
        self.power = power
        self.wheels = wheels
    
    @classmethod
    def verify_value_car(cls, wheels, power):
        if not isinstance(power, int) or power <= 0 or not isinstance(wheels,int) or wheels <= 0 or wheels > 10:
            raise ValueError('Invalid value')

    def __str__(self):
        return f"Car: средняя скорость {self.average_speed}, максимальная скорость {self.max_speed}, цена {self.price}, грузовой {self.cargo}, цвет {self.color}, мощность {self.power}, количество колес {self.wheels}."

    def __add__(self):
        return self.average_speed + self.max_speed

    def __eq__(self, other):
        return self.wheels == other.wheels and self.average_speed == other.average_speed and self.max_speed == other.max_speed and self.power == other.power

    
class Plane(Transport):
    def __init__(self, average_speed, max_speed, price, cargo, color , load_capacity, wingspan):
        super().__init__(average_speed, max_speed, price, cargo, color)
        self.verify_value_plane(load_capacity, wingspan)
        self.load_capacity = load_capacity
        self.wingspan = wingspan
    
    @classmethod
    def verify_value_plane(cls, load_capacity, wingspan):
        if not isinstance(load_capacity, int) or load_capacity <= 0 or not isinstance(wingspan, int) or wingspan <= 0:
            raise ValueError('Invalid value')
    
    def __str__(self):
        return f"Plane: средняя скорость {self.average_speed}, максимальная скорость {self.max_speed}, цена {self.price}, грузовой {self.cargo}, цвет {self.color}, грузоподъемность {self.load_capacity}, размах крыльев {self.wingspan}."
    
    def __add__(self):
        return self.average_speed + self.max_speed
    
    def __eq__(self, other):
        return self.wingspan == other.wingspan

    
class Ship(Transport):
    def __init__(self, average_speed, max_speed, price, cargo, color , length, side_height):
        super().__init__(average_speed, max_speed, price, cargo, color)
        self.verify_value_ship(length, side_height)
        self.length = length
        self.side_height = side_height
    
    @classmethod
    def verify_value_ship(cls, length, side_height):
        if not isinstance(length, int) or length <= 0 or not isinstance(side_height, int) or side_height <= 0:
            raise ValueError('Invalid value')

    def __str__(self):
        return f"Ship: средняя скорость {self.average_speed}, максимальная скорость {self.max_speed}, цена {self.price}, грузовой {self.cargo}, цвет {self.color}, длина {self.length}, высота борта {self.side_height}."

    def __add__(self):
        return self.average_speed + self.max_speed
    
    def __eq__(self, other):
        return self.length == other.length and self.side_height == other.side_height
    
class CarList(list): #– список автомобилей - наследуется от класса list.
    def __init__(self, name):
        super().__init__()
        self.name = name

    def append(self, p_object):
        if isinstance(p_object, Car):
            super().append(p_object)
        else:
            raise TypeError(f"Invalid type {type(p_object)}")

    def print_colors(self):
        print('\n'.join([f"{i+1} автомобиль: {self[i].color}" for i in range(len(self))]))

    def print_count(self):
        print(len(self))

        
class PlaneList(list):
    def __init__(self, name):
        super().__init__()
        self.name = name

    def extend(self, iterable):
        for object in iterable:
            if isinstance(object, Plane):
                super().append(object)

    def print_colors(self):
        print('\n'.join([f"{i+1} самолет: {self[i].color}" for i in range(len(self))]))    
        
    def total_speed(self):
        print(sum([plane.average_speed for plane in self]))
        
class ShipList(list):
    def __init__(self, name):
        super().__init__()
        self.name = name
    
    def append(self, p_object):
        if isinstance(p_object, Ship):
            super().append(p_object)
        else:
            raise TypeError(f"Invalid type {type(p_object)}")
    
    def print_colors(self):
        print('\n'.join([f"{i+1} корабль: {self[i].color}" for i in range(len(self))]))

    def print_ship(self):
        for i in range(len(self)):
            if self[i].length > 150:
                print(f"Длина корабля №{i + 1} больше 150 метров")       
                