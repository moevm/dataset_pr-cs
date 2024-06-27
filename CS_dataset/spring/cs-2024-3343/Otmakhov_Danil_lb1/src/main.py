class Transport:
    def __init__(self, average_speed, max_speed, price, cargo, color):
        self.verify_speed(average_speed)
        self.verify_speed(max_speed)
        self.verify_price(price)
        self.verify_cargo(cargo)
        self.verify_color(color)

        self.average_speed = average_speed
        self.max_speed = max_speed
        self.price = price
        self.cargo = cargo
        self.color = color

    @classmethod
    def verify_speed(cls, speed):
        if not isinstance(speed, int) or speed <= 0:
            raise ValueError('Invalid value')

    @classmethod
    def verify_price(cls, price):
        if not isinstance(price, int) or price <= 0:
            raise ValueError('Invalid value')

    @classmethod
    def verify_cargo(cls, cargo):
        if not isinstance(cargo, bool):
            raise ValueError('Invalid value')

    @classmethod
    def verify_color(cls, color):
        if color not in ('w', 'g', 'b'):
            raise ValueError('Invalid value')


class Car(Transport):
    def __init__(self, average_speed, max_speed, price, cargo, color, power, wheels):
        super().__init__(average_speed, max_speed, price, cargo, color)

        self.verify_power(power)
        self.verify_wheels(wheels)

        self.power = power
        self.wheels = wheels

    @classmethod
    def verify_power(cls, power):
        if not isinstance(power, int) or power <= 0:
            raise ValueError('Invalid value')

    @classmethod
    def verify_wheels(cls, wheels):
        if not isinstance(wheels, int) or wheels <= 0 or wheels > 10:
            raise ValueError('Invalid value')

    def __str__(self):
        return f"Car: средняя скорость {self.average_speed}, максимальная скорость {self.max_speed}, цена {self.price}, грузовой {self.cargo}, цвет {self.color}, мощность {self.power}, количество колес {self.wheels}."

    def __add__(self):
        return self.average_speed + self.max_speed

    def __eq__(self, other):
        return all([self.wheels == other.wheels, self.average_speed == other.average_speed, self.max_speed == other.max_speed, self.power == other.power])


class Plane(Transport):
    def __init__(self, average_speed, max_speed, price, cargo, color, load_capacity, wingspan):
        super().__init__(average_speed, max_speed, price, cargo, color)

        self.verify_load_capacity(load_capacity)
        self.verify_wingspan(wingspan)

        self.load_capacity = load_capacity
        self.wingspan = wingspan

    @classmethod
    def verify_load_capacity(cls, load_capacity):
        if not isinstance(load_capacity, int) or load_capacity <= 0:
            raise ValueError('Invalid value')

    @classmethod
    def verify_wingspan(cls, wingspan):
        if not isinstance(wingspan, int) or wingspan <= 0:
            raise ValueError('Invalid value')

    def __str__(self):
        return f"Plane: средняя скорость {self.average_speed}, максимальная скорость {self.max_speed}, цена {self.price}, грузовой {self.cargo}, цвет {self.color}, грузоподъемность {self.load_capacity}, размах крыльев {self.wingspan}."

    def __add__(self):
        return self.average_speed + self.max_speed

    def __eq__(self, other):
        return self.wingspan == other.wingspan


class Ship(Transport):
    def __init__(self, average_speed, max_speed, price, cargo, color, length, side_height):
        super().__init__(average_speed, max_speed, price, cargo, color)

        self.verify_size(length)
        self.verify_size(side_height)

        self.length = length
        self.side_height = side_height

    @classmethod
    def verify_size(cls, size):
        if not isinstance(size, int) or size <= 0:
            raise ValueError('Invalid value')

    def __str__(self):
        return f"Ship: средняя скорость {self.average_speed}, максимальная скорость {self.max_speed}, цена {self.price}, грузовой {self.cargo}, цвет {self.color}, длина {self.length}, высота борта {self.side_height}."

    def __add__(self):
        return self.average_speed + self.max_speed

    def __eq__(self, other):
        return all([self.length == other.length, self.side_height == other.side_height])


class CarList(list):
    def __init__(self, name):
        super().__init__()
        self.name = name

    def append(self, obj):
        if isinstance(obj, Car):
            super().append(obj)
        else:
            raise TypeError(f"Invalid type {type(obj)}")

    def print_colors(self):
        print('\n'.join([f"{i + 1} автомобиль: {self[i].color}" for i in range(len(self))]))

    def print_count(self):
        print(len(self))


class PlaneList(list):
    def __init__(self, name):
        super().__init__()
        self.name = name

    def extend(self, iterable):
        for obj in iterable:
            if isinstance(obj, Plane):
                super().append(obj)

    def print_colors(self):
        print('\n'.join([f"{i + 1} самолет: {self[i].color}" for i in range(len(self))]))

    def total_speed(self):
        print(sum([plane.average_speed for plane in self]))


class ShipList(list):
    def __init__(self, name):
        super().__init__()
        self.name = name

    def append(self, obj):
        if isinstance(obj, Ship):
            super().append(obj)
        else:
            raise TypeError(f"Invalid type {type(obj)}")

    def print_colors(self):
        print('\n'.join([f"{i + 1} корабль: {self[i].color}" for i in range(len(self))]))

    def print_ship(self):
        for i in range(len(self)):
            if self[i].length > 150:
                print(f"Длина корабля №{i + 1} больше 150 метров")
