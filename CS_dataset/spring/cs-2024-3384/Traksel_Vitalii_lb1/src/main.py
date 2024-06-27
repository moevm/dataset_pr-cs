class Transport:
    def __init__(self, average_speed, max_speed, price, cargo, color):
        valid_colors = {'w', 'g', 'b'}
        if average_speed <= 0 or max_speed <= 0 or price <= 0 or color not in valid_colors or not isinstance(cargo, bool):
            raise ValueError('Invalid value')
        self.average_speed = average_speed
        self.max_speed = max_speed
        self.price = price
        self.cargo = cargo
        self.color = color

class Car(Transport):
    def __init__(self, average_speed, max_speed, price, cargo, color, power, wheels):
        super().__init__(average_speed, max_speed, price, cargo, color)
        if power <= 0 or not (1 <= wheels <= 10):
            raise ValueError('Invalid value')
        self.power = power
        self.wheels = wheels

    def __str__(self):
        return (f"Car: средняя скорость {self.average_speed}, максимальная скорость {self.max_speed}, "
                f"цена {self.price}, грузовой {self.cargo}, цвет {self.color}, мощность {self.power}, "
                f"количество колес {self.wheels}.")

    def __add__(self):
        return self.average_speed + self.max_speed

    def __eq__(self, other):
        if isinstance(other, Car):
            return (self.wheels == other.wheels and self.average_speed == other.average_speed and
                    self.max_speed == other.max_speed and self.power == other.power)
        return False

class Plane(Transport):
    def __init__(self, average_speed, max_speed, price, cargo, color, load_capacity, wingspan):
        super().__init__(average_speed, max_speed, price, cargo, color)
        if load_capacity <= 0 or wingspan <= 0:
            raise ValueError('Invalid value')
        self.load_capacity = load_capacity
        self.wingspan = wingspan

    def __str__(self):
        return (f"Plane: средняя скорость {self.average_speed}, максимальная скорость {self.max_speed}, "
                f"цена {self.price}, грузовой {self.cargo}, цвет {self.color}, грузоподъемность {self.load_capacity}, "
                f"размах крыльев {self.wingspan}.")

    def __add__(self):
        return self.average_speed + self.max_speed

    def __eq__(self, other):
        if isinstance(other, Plane):
            return self.wingspan == other.wingspan
        return False

class Ship(Transport):
    def __init__(self, average_speed, max_speed, price, cargo, color, length, side_height):
        super().__init__(average_speed, max_speed, price, cargo, color)
        if length <= 0 or side_height <= 0:
            raise ValueError('Invalid value')
        self.length = length
        self.side_height = side_height

    def __str__(self):
        return (f"Ship: средняя скорость {self.average_speed}, максимальная скорость {self.max_speed}, "
                f"цена {self.price}, грузовой {self.cargo}, цвет {self.color}, длина {self.length}, "
                f"высота борта {self.side_height}.")

    def __add__(self):
            return self.average_speed + self.max_speed

    def __eq__(self, other):
        if isinstance(other, Ship):
            return self.length == other.length and self.side_height == other.side_height
        return False

class CarList(list):
    def __init__(self, name):
        super().__init__()
        self.name = name

    def append(self, p_object):
        if not isinstance(p_object, Car):
            raise TypeError(f'Invalid type {type(p_object).__name__}')
        super().append(p_object)

    def print_colors(self):
        for idx, car in enumerate(self, start=1):
            print(f"{idx} автомобиль: {car.color}")

    def print_count(self):
        print(len(self))

class PlaneList(list):
    def __init__(self, name):
        super().__init__()
        self.name = name

    def extend(self, iterable):
        for item in iterable:
            if isinstance(item, Plane):
                super().append(item)

    def print_colors(self):
        for idx, plane in enumerate(self, start=1):
            print(f"{idx} самолет: {plane.color}")

    def total_speed(self):
        total = sum(plane.average_speed for plane in self)
        print(total)

class ShipList(list):
    def __init__(self, name):
        super().__init__()
        self.name = name

    def append(self, p_object):
        if not isinstance(p_object, Ship):
            raise TypeError(f'Invalid type {type(p_object).__name__}')
        super().append(p_object)

    def print_colors(self):
        for idx, ship in enumerate(self, start=1):
            print(f"{idx} корабль: {ship.color}")

    def print_ship(self):
        for idx, ship in enumerate(self, start=1):
            if ship.length > 150:
                print(f'Длина корабля №{idx} больше 150 метров')

