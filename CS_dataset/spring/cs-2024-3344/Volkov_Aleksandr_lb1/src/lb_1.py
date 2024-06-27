class Transport:
    def __init__(self, average_speed, max_speed, price, cargo, color):
        if not (
            isinstance(average_speed, int)
            and average_speed > 0
            and isinstance(max_speed, int)
            and max_speed > 0
            and isinstance(price, int)
            and price > 0
            and isinstance(cargo, bool)
            and color in "wgb"
        ):
            raise ValueError("Invalid value")
        self.average_speed = average_speed
        self.max_speed = max_speed
        self.price = price
        self.cargo = cargo
        self.color = color


class Car(Transport):
    def __init__(self, average_speed, max_speed, price, cargo, color, power, wheels):
        super().__init__(average_speed, max_speed, price, cargo, color)
        if not (
            isinstance(power, int)
            and power > 0
            and isinstance(wheels, int)
            and 1 <= wheels <= 10
        ):
            raise ValueError("Invalid value")
        self.power = power
        self.wheels = wheels

    def __str__(self):
        return f"Car: средняя скорость {self.average_speed}, максимальная скорость {self.max_speed}, цена {self.price}, грузовой {self.cargo}, цвет {self.color}, мощность {self.power}, количество колес {self.wheels}."

    def __add__(self):
        return self.average_speed + self.max_speed

    def __eq__(self, other):
        requirements = (
            self.wheels == other.wheels,
            self.average_speed == other.average_speed,
            self.max_speed == other.max_speed,
            self.power == other.power,
        )
        return all(requirements)


class Plane(Transport):
    def __init__(
        self, average_speed, max_speed, price, cargo, color, load_capacity, wingspan
    ):
        super().__init__(average_speed, max_speed, price, cargo, color)
        if not (
            isinstance(load_capacity, int)
            and load_capacity > 0
            and isinstance(wingspan, int)
            and wingspan > 0
        ):
            raise ValueError("Invalid value")
        self.load_capacity = load_capacity
        self.wingspan = wingspan

    def __str__(self):
        return f"Plane: средняя скорость {self.average_speed}, максимальная скорость {self.max_speed}, цена {self.price}, грузовой {self.cargo}, цвет {self.color}, грузоподъемность {self.load_capacity}, размах крыльев {self.wingspan}."

    def __add__(self):
        return self.average_speed + self.max_speed

    def __eq__(self, other):
        return self.wingspan == other.wingspan


class Ship(Transport):
    def __init__(
        self, average_speed, max_speed, price, cargo, color, length, side_height
    ):
        super().__init__(average_speed, max_speed, price, cargo, color)
        if not (
            isinstance(length, int)
            and length > 0
            and isinstance(side_height, int)
            and side_height > 0
        ):
            raise ValueError("Invalid value")
        self.length = length
        self.side_height = side_height

    def __str__(self):
        return f"Ship: средняя скорость {self.average_speed}, максимальная скорость {self.max_speed}, цена {self.price}, грузовой {self.cargo}, цвет {self.color}, длина {self.length}, высота борта {self.side_height}."

    def __add__(self):
        return self.average_speed + self.max_speed

    def __eq__(self, other):
        return self.length == other.length and self.side_height == other.side_height


class CarList(list):
    def __init__(self, name):
        super().__init__()
        self.name = name

    def append(self, p_object):
        if not isinstance(p_object, Car):
            raise TypeError(f"Invalid type {type(p_object)}")
        super().append(p_object)

    def print_colors(self):
        colors_cars = []
        for i in range(len(self)):
            colors_cars.append(f'{i+1} автомобиль: {self[i].color}')
        print('\n'.join(colors_cars))

    def print_count(self):
        print(len(self))


class PlaneList(list):
    def __init__(self, name):
        super().__init__()
        self.name = name

    def extend(self, lst):
        super().extend(filter(lambda x: isinstance(x, Plane), lst))

    def print_colors(self):
        colors_planes = []
        for i in range(len(self)):
            colors_planes.append(f'{i+1} самолет: {self[i].color}')
        print('\n'.join(colors_planes))

    def total_speed(self):
        print(sum(i.average_speed for i in self))


class ShipList(list):
    def __init__(self, name):
        super().__init__()
        self.name = name

    def append(self, p_object):
        if not isinstance(p_object, Ship):
            raise TypeError(f"Invalid type {type(p_object)}")
        super().append(p_object)

    def print_colors(self):
        colors_ships = []
        for i in range(len(self)):
            colors_ships.append(f'{i+1} корабль: {self[i].color}')
        print('\n'.join(colors_ships))

    def print_ship(self):
        long_ships = []
        for i in range(len(self)):
            if self[i].length > 150:
                long_ships.append(f'Длина корабля №{i+1} больше 150 метров')
        print('\n'.join(long_ships))
