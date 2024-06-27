class Transport:
    def __init__(self, average_speed, max_speed, price, cargo, color):
        if not (all(isinstance(x, int) and x>0 for x in [average_speed, max_speed, price]) and isinstance(cargo, bool) and color in ['w', 'g', 'b']):
            raise ValueError('Invalid value')
        self.average_speed = average_speed
        self.max_speed = max_speed
        self.price = price
        self.cargo = cargo
        self.color = color

class Car(Transport):
    def __init__(self, average_speed, max_speed, price, cargo, color, power, wheels):
        super().__init__(average_speed, max_speed, price, cargo, color)
        if not (all(isinstance(x,int) and x>0 for x in [power, wheels]) and wheels<=10):
            raise ValueError ('Invalid value')
        self.power = power
        self.wheels = wheels
    def __str__(self):
        return f'Car: средняя скорость {self.average_speed}, максимальная скорость {self.max_speed}, цена {self.price}, грузовой {self.cargo}, цвет {self.color}, мощность {self.power}, количество колес {self.wheels}.'
    def __add__(self):
        return self.average_speed + self.max_speed
    def __eq__(self, other):
        return isinstance(other, Car) and self.wheels == other.wheels and self.average_speed == other.average_speed and self.max_speed == other.max_speed and self.power == other.power

class Plane(Transport):
    def __init__(self, average_speed, max_speed, price, cargo, color, load_capacity, wingspan):
        super().__init__(average_speed, max_speed, price, cargo, color)
        if not(all(isinstance(x, int) and x>0 for x in [load_capacity, wingspan])):
            raise ValueError('Invalid value')
        self.load_capacity = load_capacity
        self.wingspan = wingspan
    def __str__(self):
        return f'Plane: средняя скорость {self.average_speed}, максимальная скорость {self.max_speed}, цена {self.price}, грузовой {self.cargo}, цвет {self.color}, грузоподъемность {self.load_capacity}, размах крыльев {self.wingspan}.'
    def __add__(self):
        return self.average_speed + self.max_speed
    def __eq__(self, other):
        return isinstance(other, Plane) and self.wingspan == other.wingspan

class Ship(Transport):
    def __init__(self, average_speed, max_speed, price, cargo, color, length, side_height):
        super().__init__(average_speed, max_speed, price, cargo, color)
        if not all(isinstance(x, int) and x > 0 for x in [length, side_height]):
            raise ValueError('Invalid value')
        self.length = length
        self.side_height = side_height
    def __str__(self):
        return f'Ship: средняя скорость {self.average_speed}, максимальная скорость {self.max_speed}, цена {self.price}, грузовой {self.cargo}, цвет {self.color}, длина {self.length}, высота борта {self.side_height}.'
    def __add__(self):
        return self.average_speed + self.max_speed
    def __eq__(self, other):
        return isinstance(other, Ship) and self.length == other.length and self.side_height == other.side_height

class CarList(list):
    def __init__(self, name):
        super().__init__()
        self.name = name
    def append(self, p_object):
        if isinstance(p_object, Car):
            super().append(p_object)
        else:
            raise TypeError(f'Invalid type {type(p_object)}')
    def print_colors(self):
        for i in range(len(self)):
            print(f'{i+1} автомобиль: {self[i].color}')

    def print_count(self):
        print(len(self))

class PlaneList(list):
    def __init__(self, name):
        super().__init__()
        self.name = name

    def extend(self, iterable):
        for i in iterable:
            if isinstance(i, Plane):
                super().append(i)

    def print_colors(self):
        for i in range(len(self)):
            print(f'{i+1} самолет: {self[i].color}')

    def total_speed(self):
        k=0
        for i in self:
            k+=i.average_speed
        print(k)

class ShipList(list):
    def __init__(self, name):
        super().__init__()
        self.name = name

    def append(self, p_object):
        if isinstance(p_object, Ship):
            super().append(p_object)
        else:
            raise TypeError(f'Invalid type {type(p_object)}')

    def print_colors(self):
        for i in range(len(self)):
            print(f'{i+1} корабль: {self[i].color}')

    def print_ship(self):
        for i in range(len(self)):
            if self[i].length > 150:
                print(f'Длина корабля №{i+1} больше 150 метров')
