class Transport:
    def __init__(self, average_speed, max_speed, price, cargo, color):
        if average_speed > 0 and max_speed > 0 and price > 0 and\
            (type(cargo) == bool) and color in ['w', 'g', 'b']:
            self.average_speed = average_speed
            self.max_speed = max_speed
            self.price = price
            self.cargo = cargo
            self.color = color
        else:
            raise ValueError


class Car(Transport):
    def __init__(self, average_speed, max_speed, price, cargo, color, power, wheels):
        super().__init__(average_speed, max_speed, price, cargo, color)
        if power > 0 and wheels > 0:
            self.power = power
            self.wheels = wheels
        else:
            raise ValueError
    def __str__(self):
        return f'Car: средняя скорость {self.average_speed}, максимальная скорость {self.max_speed}, цена {self.price}, грузовой {self.cargo}, цвет {self.color}, мощность {self.power}, количество колес {self.wheels}.'
    def __add__(self):
        return self.average_speed + self.max_speed
    def __eq__(self, other):
        if isinstance(self, Car) and isinstance(other, Car):
            return self.wheels == other.wheels and self.average_speed == other.average_speed and\
                self.max_speed == other.max_speed and self.power == other.power
        return ValueError


class Plane(Transport):
    def __init__(self, average_speed, max_speed, price, cargo, color, load_capacity, wingspan):
        super().__init__(average_speed, max_speed, price, cargo, color)
        if load_capacity > 0 and wingspan > 0:
            self.load_capacity = load_capacity
            self.wingspan = wingspan
        else:
            raise ValueError
    def __str__(self):
        return f'Plane: средняя скорость {self.average_speed}, максимальная скорость {self.max_speed}, цена {self.price}, грузовой {self.cargo}, цвет {self.color}, грузоподъемность {self.load_capacity}, размах крыльев {self.wingspan}.'
    def __add__(self):
        return self.average_speed + self.max_speed
    def __eq__(self, other):
        if isinstance(self, Plane) and isinstance(other, Plane):
            return self.wingspan == other.wingspan
        return ValueError


class Ship(Transport):
    def __init__(self, average_speed, max_speed, price, cargo, color, length, side_height):
        super().__init__(average_speed, max_speed, price, cargo, color)
        if length > 0 and side_height > 0:
            self.length = length
            self.side_height = side_height
        else:
            raise ValueError
    def __str__(self):
        return f'Ship: средняя скорость {self.average_speed}, максимальная скорость {self.max_speed}, цена {self.price}, грузовой {self.cargo}, цвет {self.color}, длина {self.length}, высота борта {self.side_height}.'
    def __add__(self):
        return self.average_speed + self.max_speed
    def __eq__(self, other):
        if isinstance(self, Ship) and isinstance(other, Ship):
            return self.length == other.length and self.side_height == other.side_height
        return ValueError


class CarList(list):
    def __init__(self, name):
        super().__init__()
        self.name = name
    def append(self, p_object):
        if isinstance(p_object, Car):
            super().append(p_object)
        else:
            raise TypeError(type(p_object))
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
        if type(iterable) == list or type(iterable) == tuple:
            for i in iterable:
                if isinstance(i, Plane):
                    super().append(i)
        else:
            raise TypeError(type(iterable))

    def print_colors(self):
        for i in range(len(self)):
            print(f'{i+1} самолет: {self[i].color}')
    def total_speed(self):
        average_speed = 0
        for i in self:
            average_speed += i.average_speed
        print(average_speed)


class ShipList(list):
    def __init__(self, name):
        super().__init__()
        self.name = name
    def append(self, p_object):
        if isinstance(p_object, Ship):
            super().append(p_object)
        else:
            raise TypeError(type(p_object))
    def print_colors(self):
        for i in range(len(self)):
            print(f'{i+1} корабль: {self[i].color}')
    def print_ship(self):
        for i in range(len(self)):
            if self[i].length > 150:
                print(f'Длина корабля №{i+1} больше 150 метров')