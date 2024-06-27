class Transport:
    def __init__(self, average_speed, max_speed, price, cargo, color):
        self.validate_parameters(average_speed, max_speed, price, cargo, color)
        self.average_speed = average_speed
        self.max_speed = max_speed
        self.price = price
        self.cargo = cargo
        self.color = color

    @staticmethod
    def validate_parameters(average_speed, max_speed, price, cargo, color):
        if not (isinstance(average_speed, int) and average_speed > 0 and
                isinstance(max_speed, int) and max_speed > 0 and
                isinstance(price, int) and price > 0 and
                isinstance(cargo, bool) and
                color in ['w', 'g', 'b']):
            raise ValueError('Invalid value')


class Car(Transport):
    def __init__(self, average_speed, max_speed, price, cargo, color, power, wheels):
        super().__init__(average_speed, max_speed, price, cargo, color)
        self.validate_car_parameters(power, wheels)
        self.power = power
        self.wheels = wheels

    @staticmethod
    def validate_car_parameters(power, wheels):
        if not (isinstance(power, int) and power > 0 and
                isinstance(wheels, int) and 0 < wheels <= 10):
            raise ValueError('Invalid value')

    def __str__(self):
        return f"Car: средняя скорость {self.average_speed}, максимальная скорость {self.max_speed}, цена {self.price}, грузовой {self.cargo}, цвет {self.color}, мощность {self.power}, количество колес {self.wheels}."

    def __add__(self):
        return self.max_speed + self.average_speed

    def __eq__(self, other):
        return (
                (self.wheels == other.wheels)
                and (self.average_speed == other.average_speed)
                and (self.max_speed == other.max_speed)
                and (self.power == other.power)
        )


class Plane(Transport):
    def __init__(self, average_speed, max_speed, price, cargo, color, load_capacity, wingspan):
        super().__init__(average_speed, max_speed, price, cargo, color)
        self.validate_plane_parameters(load_capacity, wingspan)
        self.load_capacity = load_capacity
        self.wingspan = wingspan

    @staticmethod
    def validate_plane_parameters(load_capacity, wingspan):
        if not (isinstance(load_capacity, int) and load_capacity > 0 and
                isinstance(wingspan, int) and wingspan > 0):
            raise ValueError('Invalid value')

    def __str__(self):
        return f"Plane: средняя скорость {self.average_speed}, максимальная скорость {self.max_speed}, цена {self.price}, грузовой {self.cargo}, цвет {self.color}, грузоподъемность {self.load_capacity}, размах крыльев {self.wingspan}."

    def __add__(self):
        return self.max_speed + self.average_speed

    def __eq__(self, other):
        return self.wingspan == other.wingspan


class Ship(Transport):
    def __init__(self, average_speed, max_speed, price, cargo, color, length, side_height):
        super().__init__(average_speed, max_speed, price, cargo, color)
        self.validate_ship_parameters(length, side_height)
        self.length = length
        self.side_height = side_height

    @staticmethod
    def validate_ship_parameters(length, side_height):
        if not (isinstance(length, int) and length > 0 and
                isinstance(side_height, int) and side_height > 0):
            raise ValueError('Invalid value')

    def __str__(self):
        return f"Ship: средняя скорость {self.average_speed}, максимальная скорость {self.max_speed}, цена {self.price}, грузовой {self.cargo}, цвет {self.color}, длина {self.length}, высота борта {self.side_height}."

    def __add__(self):
        return self.max_speed + self.average_speed

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
            raise TypeError(f"Invalid type <тип_объекта p_object> {type(p_object)}")

    def print_colors(self):
        for i, car in enumerate(self):
            print(f"{i + 1} автомобиль: {car.color}")

    def print_count(self):
        print(len(self))


class PlaneList(list):
    def __init__(self, name):
        super().__init__()
        self.name = name

    def extend(self, iterable):
        planes_only = filter(lambda x: isinstance(x, Plane), iterable)
        super().extend(planes_only)

    def print_colors(self):
        for i, plane in enumerate(self):
            print(f"{i + 1} самолет: {plane.color}")

    def total_speed(self):
        total_speed = sum(plane.average_speed for plane in self)
        print(total_speed)


class ShipList(list):
    def __init__(self, name):
        super().__init__()
        self.name = name

    def append(self, p_object):
        if isinstance(p_object, Ship):
            super().append(p_object)
        else:
            raise TypeError(f"Invalid type <тип_объекта p_object> {type(p_object)}")

    def print_colors(self):
        for i, ship in enumerate(self):
            print(f"{i + 1} корабль: {ship.color}")

    def print_ship(self):
        for i, ship in enumerate(self):
            if ship.length > 150:
                print(f'Длина корабля №{i + 1} больше 150 метров')
