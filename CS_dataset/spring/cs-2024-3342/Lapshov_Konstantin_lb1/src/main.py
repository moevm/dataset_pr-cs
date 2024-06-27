class Transport:
    def _checkTransportValues(self, average_speed, max_speed, price, cargo, color):
        return (isinstance(average_speed, int) and average_speed > 0) and (isinstance(max_speed, int) and max_speed > 0) and (isinstance(price, int) and price > 0) and isinstance(cargo, bool) and (isinstance(color, str) and (color == "w" or color == "g" or color == "b"))

    def __init__(self, average_speed, max_speed, price, cargo, color):
        if not self._checkTransportValues(average_speed, max_speed, price, cargo, color):
            raise ValueError("Invalid value")
        else:
            self.average_speed = average_speed
            self.max_speed = max_speed
            self.price = price
            self.cargo = cargo
            self.color = color


class Car(Transport):
    def _checkCarValues(self, average_speed, max_speed, price, cargo, color, power, wheels):
        return super()._checkTransportValues(average_speed, max_speed, price, cargo, color) and (isinstance(power, int) and power > 0) and (isinstance(wheels, int) and 10 >= wheels > 0)

    def __init__(self, average_speed, max_speed, price, cargo, color, power, wheels):
        if not self._checkCarValues(average_speed, max_speed, price, cargo, color, power, wheels):
            raise ValueError("Invalid value")
        else:
            super().__init__(average_speed, max_speed, price, cargo, color)
            self.power = power
            self.wheels = wheels

    def __str__(self):
        return f'Car: средняя скорость {self.average_speed}, максимальная скорость {self.max_speed}, цена {self.price}, грузовой {self.cargo}, цвет {self.color}, мощность {self.power}, количество колес {self.wheels}.'

    def __add__(self):
        return self.average_speed + self.max_speed

    def __eq__(self, other):
        return self.wheels == other.wheels and self.average_speed == other.average_speed and self.max_speed == other.max_speed and self.power == self.power


class Plane(Transport):
    def _checkPlaneValues(self, average_speed, max_speed, price, cargo, color, load_capacity, wingspan):
        return super()._checkTransportValues(average_speed, max_speed, price, cargo, color) and (isinstance(load_capacity, int) and load_capacity > 0) and (isinstance(wingspan, int) and wingspan > 0)

    def __init__(self, average_speed, max_speed, price, cargo, color, load_capacity, wingspan):
        if not self._checkPlaneValues(average_speed, max_speed, price, cargo, color, load_capacity, wingspan):
            raise ValueError("Invalid value")
        else:
            super().__init__(average_speed, max_speed, price, cargo, color)
            self.load_capacity = load_capacity
            self.wingspan = wingspan

    def __str__(self):
        return f'Plane: средняя скорость {self.average_speed}, максимальная скорость {self.max_speed}, цена {self.price}, грузовой {self.cargo}, цвет {self.color}, грузоподъемность {self.load_capacity}, размах крыльев {self.wingspan}.'

    def __add__(self):
        return self.average_speed + self.max_speed

    def __eq__(self, other):
        return self.wingspan == other.wingspan


class Ship(Transport):
    def _checkShipValues(self, average_speed, max_speed, price, cargo, color, length, side_height):
        return super()._checkTransportValues(average_speed, max_speed, price, cargo, color) and (isinstance(length, int) and length > 0) and (isinstance(side_height, int) and side_height > 0)

    def __init__(self, average_speed, max_speed, price, cargo, color, length, side_height):
        if not self._checkShipValues(average_speed, max_speed, price, cargo, color, length, side_height):
            raise ValueError("Invalid value")
        else:
            super().__init__(average_speed, max_speed, price, cargo, color)
            self.length = length
            self.side_height = side_height

    def __str__(self):
        return f'Ship: средняя скорость {self.average_speed}, максимальная скорость {self.max_speed}, цена {self.price}, грузовой {self.cargo}, цвет {self.color}, длина {self.length}, высота борта {self.side_height}.'

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
            raise TypeError("Invalid type <тип_объекта p_object> (результат вызова функции type)")

    def print_colors(self):
        for i, item in enumerate(self):
            print(f'{i + 1} автомобиль: {item.color}')

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
        for i, item in enumerate(self):
            print(f'{i+1} самолет: {item.color}')

    def total_speed(self):
        general_avg_speed = 0
        for item in self:
            general_avg_speed += item.average_speed

        print(general_avg_speed)


class ShipList(list):
    def __init__(self, name):
        super().__init__()
        self.name = name

    def append(self, p_object):
        if isinstance(p_object, Ship):
            super().append(p_object)
        else:
            raise TypeError("Invalid type <тип_объекта p_object>")

    def print_colors(self):
        for i, item in enumerate(self):
            print(f'{i+1} корабль: {item.color}')

    def print_ship(self):
        for i, item in enumerate(self):
            if item.length > 150:
                print(f'Длина корабля №{i+1} больше 150 метров')