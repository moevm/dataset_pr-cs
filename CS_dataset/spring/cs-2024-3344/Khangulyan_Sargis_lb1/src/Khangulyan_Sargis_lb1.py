class Transport:
    def __init__(self, average_speed, max_speed, price, cargo, color):
        if (isinstance(average_speed, int) and isinstance(max_speed, int) 
            and isinstance(price, int) and isinstance(cargo, bool) 
            and average_speed > 0 and max_speed > 0 and price > 0
            and (color == "w" or color == "b" or color == "g")):
                self.average_speed = average_speed
                self.max_speed = max_speed
                self.price = price
                self.cargo = cargo
                self.color = color
        else: raise ValueError('Invalid value')



class Car(Transport):
    def __init__(self, average_speed, max_speed, price, cargo, color, power, wheels):
        super().__init__(average_speed, max_speed, price, cargo, color)
        if (isinstance(power, int) and isinstance(wheels, int)
            and power > 0 and 0 < wheels < 11):
                self.power = power
                self.wheels = wheels
        else: raise ValueError('Invalid value')

    def __str__(self):
        return f"Car: средняя скорость {self.average_speed}, максимальная скорость {self.max_speed}, цена {self.price}, грузовой {self.cargo}, цвет {self.color}, мощность {self.power}, количество колес {self.wheels}."
    
    def __add__(self):
        return self.average_speed + self.max_speed

    def __eq__(self, other):
        if (self.wheels == other.wheels 
            and self.average_speed == other.average_speed
            and self.max_speed == other.max_speed
            and self.power == other.power):
                return True
        return False
    


class Plane(Transport):
    def __init__(self, average_speed, max_speed, price, cargo, color, load_capacity, wingspan):
        super().__init__(average_speed, max_speed, price, cargo, color)
        if (isinstance(load_capacity, int) and isinstance(wingspan, int)
            and load_capacity > 0 and wingspan > 0):
                self.load_capacity = load_capacity
                self.wingspan = wingspan
        else: raise ValueError('Invalid value')

    def __str__(self):
        return f"Plane: средняя скорость {self.average_speed}, максимальная скорость {self.max_speed}, цена {self.price}, грузовой {self.cargo}, цвет {self.color}, грузоподъемность {self.load_capacity}, размах крыльев {self.wingspan}."
    
    def __add__(self):
        return self.average_speed + self.max_speed

    def __eq__(self, other): 
        if (self.wingspan == other.wingspan):
            return True 
        return False


class Ship(Transport):
    def __init__(self, average_speed, max_speed, price, cargo, color, length, side_height):
        super().__init__(average_speed, max_speed, price, cargo, color)
        if (isinstance(length, int) and isinstance(side_height, int)
            and length > 0 and side_height > 0):
                self.length = length
                self.side_height = side_height
        else: raise ValueError('Invalid value')

    def __str__(self):
        return f"Ship: средняя скорость {self.average_speed}, максимальная скорость {self.max_speed}, цена {self.price}, грузовой {self.cargo}, цвет {self.color}, длина {self.length}, высота борта {self.side_height}."
    
    def __add__(self):
        return self.average_speed + self.max_speed

    def __eq__(self, other):
        if (self.length == other.length and self.side_height == other.side_height):
             return True
        return False



class CarList(list):
    def __init__(self, name):
        super().__init__()
        self.name = name
           
    def append(self, p_object):
        if (isinstance(p_object, Car)):
            super().append(p_object)
        else:
            raise TypeError(f"Invalid type {type(p_object)}")
        

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
        filtered_iterable = []
        for i in iterable:
            if (isinstance(i, Plane)):
                filtered_iterable.append(i)
        super().extend(filtered_iterable)
        
    def print_colors(self):
        for i in range(len(self)):
            print(f"{i+1} самолет: {self[i].color}")
            
    def total_speed(self):
        sum = 0
        for i in range(len(self)):
            sum += self[i].average_speed
        print(sum)



class ShipList(list):
    def __init__(self, name):
        super().__init__()
        self.name = name

    def append(self, p_object):
        if (isinstance(p_object, Ship)):
            super().append(p_object)
        else:
            raise TypeError(f"Invalid type {type(p_object)}")

    def print_colors(self):
        for i in range(len(self)):
            print(f"{i+1} корабль: {self[i].color}")
            
    def print_ship(self):
        for i in range(len(self)):
            if self[i].length > 150:
                print(f'Длина корабля №{i+1} больше 150 метров')