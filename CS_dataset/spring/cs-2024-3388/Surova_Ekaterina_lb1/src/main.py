class Transport():
    def __init__(self, average_speed, max_speed, price, cargo, color):
        if all(((color in ['w', 'g', 'b']), isinstance(average_speed, int), isinstance(price, int), isinstance(max_speed, int),
                isinstance(cargo, bool), average_speed > 0, max_speed > 0, price > 0)):
            self.average_speed = average_speed
            self.max_speed = max_speed
            self.price = price
            self.cargo = cargo
            self.color = color
        else:
            raise ValueError('Invalid value')


class Car(Transport):
    def __init__(self, average_speed, max_speed, price, cargo, color, power, wheels):
        super().__init__(average_speed, max_speed, price, cargo, color)
        if (power > 0 and isinstance(power, int)) and (0 < wheels < 11 and isinstance(wheels, int)):
            self.power = power
            self.wheels = wheels
        else:
            raise (ValueError('Invalid value'))

    def __str__(self):
        return f"Car: средняя скорость {self.average_speed}, максимальная скорость {self.max_speed}, цена {self.price}, грузовой {self.cargo}, цвет {self.color}, мощность {self.power}, количество колес {self.wheels}."

    def __add__(self):
        return self.average_speed + self.max_speed

    def __eq__(self, other):
        return self.wheels == other.wheels and self.average_speed == other.average_speed and self.max_speed == other.max_speed and self.power == other.power


class Plane(Transport):
    def __init__(self, average_speed, max_speed, price, cargo, color, load_capacity, wingspan):
        super().__init__(average_speed, max_speed, price, cargo, color)
        if all((isinstance(load_capacity, int), isinstance(wingspan, int), load_capacity > 0, wingspan > 0)):
            self.load_capacity = load_capacity
            self.wingspan = wingspan
        else:
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
        if all((isinstance(length, int), isinstance(side_height, int), length > 0, side_height > 0)):
            self.length = length
            self.side_height = side_height
        else:
            raise ValueError('Invalid value')

    def __str__(self):
        return f"Ship: средняя скорость {self.average_speed}, максимальная скорость {self.max_speed}, цена {self.price}, грузовой {self.cargo}, цвет {self.color}, длина {self.length}, высота борта {self.side_height}."

    def __add__(self):
        return self.average_speed + self.max_speed

    def __eq__(self, other):
        return self.length == other.length and self.side_height == other.side_height


class CarList(list):
    def __init__(self, name):
        super().__init__(self)
        self.name = name

    def append(self, p_object):
        if isinstance(p_object, Car):
            super().append(p_object)
        else:
            raise TypeError(f"Invalid type {type(p_object)}")

    def print_colors(self):
        for i in range(1, len(self) + 1):
            print(f'{i} автомобиль: {self[i - 1].color}')

    def print_count(self):
        print(len(self))


class PlaneList(list):
    def __init__(self, name):
        super().__init__()
        self.name = name

    def extend(self, iterable):
        for i in range(len(iterable)):
            if isinstance(iterable[i], Plane):
                super().append(iterable[i])

    def print_colors(self):
        for i in range(1, len(self) + 1):
            print(f'{i} самолет: {self[i - 1].color}')

    def total_speed(self):
        print(sum(i.average_speed for i in self))

class ShipList(list):
    def __init__(self, name):
        super().__init__()
        self.name = name

    def append(self, p_object):
        if isinstance(p_object, Ship):
            super().append(p_object)
        else:
            raise (TypeError(f'Invalid type {type(p_object)}'))

    def print_colors(self):
        for i in range(1, len(self) + 1):
            print(f'{i} корабль: {self[i - 1].color}')

    def print_ship(self):
        for i in range(1, len(self) + 1):
            if self[i - 1].length > 150:
                print(f'Длина корабля №{i} больше 150 метров')
