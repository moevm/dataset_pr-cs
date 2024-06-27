class Transport():
    def __init__(self, average_speed, max_speed, price, cargo, color):
        if isinstance(average_speed, int) and average_speed > 0:
            self.average_speed = average_speed
        else:
            raise (ValueError("Invalid value"))
        if isinstance(max_speed, int) and max_speed > 0:
            self.max_speed = max_speed
        else:
            raise (ValueError("Invalid value"))
        if isinstance(price, int) and price > 0:
            self.price = price
        else:
            raise (ValueError("Invalid value"))
        if isinstance(cargo, bool):
            self.cargo = cargo
        else:
            raise (ValueError("Invalid value"))
        if color in ['w', 'g', 'b']:
            self.color = color
        else:
            raise (ValueError("Invalid value"))


class Car(Transport):
    def __init__(self, average_speed, max_speed, price, cargo, color, power, wheels):
        super().__init__(average_speed, max_speed, price, cargo, color)
        if isinstance(wheels, int) and (0 < wheels <= 10):
            self.wheels = wheels
        else:
            raise (ValueError("Invalid value"))
        if isinstance(power, int) and power > 0:
            self.power = power
        else:
            raise (ValueError("Invalid value"))

    def __str__(self):
        s = 'Car: '
        return s + f'средняя скорость {self.average_speed}, максимальная скорость {self.max_speed},' \
                   f' цена {self.price}, грузовой {self.cargo}, цвет {self.color}, мощность {self.power},' \
                   f' количество колес {self.wheels}.'

    def __add__(self):
        return self.average_speed + self.max_speed

    def __eq__(self, other):
        return self.wheels == other.wheels and self.average_speed == other.average_speed and self.max_speed == other.max_speed and self.power == other.power


class Plane(Transport):
    def __init__(self, average_speed, max_speed, price, cargo, color, load_capacity, wingspan):
        if isinstance(load_capacity, int) and load_capacity > 0:
            self.load_capacity = load_capacity
        else:
            raise (ValueError("Invalid value"))
        if isinstance(wingspan, int) and wingspan > 0:
            self.wingspan = wingspan
        else:
            raise (ValueError("Invalid value"))
        super().__init__(average_speed, max_speed, price, cargo, color)

    def __str__(self):
        s = 'Plane: '
        return s + f'средняя скорость {self.average_speed}, максимальная скорость {self.max_speed},' \
                   f' цена {self.price}, грузовой {self.cargo}, цвет {self.color}, грузоподъемность {self.load_capacity},' \
                   f' размах крыльев {self.wingspan}.'

    def __add__(self):
        return self.average_speed + self.max_speed

    def __eq__(self, other):
        return self.wingspan == other.wingspan


class Ship(Transport):
    def __init__(self, average_speed, max_speed, price, cargo, color, length, side_height):
        if isinstance(length, int) and length > 0:
            self.length = length
        else:
            raise (ValueError("Invalid value"))
        if isinstance(side_height, int) and side_height > 0:
            self.side_height = side_height
        else:
            raise (ValueError("Invalid value"))
        super().__init__(average_speed, max_speed, price, cargo, color)

    def __str__(self):
        s = 'Ship: '
        return s + f'средняя скорость {self.average_speed}, максимальная скорость {self.max_speed},' \
                   f' цена {self.price}, грузовой {self.cargo}, цвет {self.color}, длина {self.length},' \
                   f' высота борта {self.side_height}.'

    def __add__(self):
        return self.average_speed + self.max_speed

    def __eq__(self, other):
        return self.side_height == other.side_height and self.length == other.length


class CarList(list):
    def __init__(self, name):
        super().__init__()
        self.name = name

    def append(self, p_object):
        if isinstance(p_object, Car):
            super().append(p_object)
        else:
            raise (TypeError(f'Invalid type {type(p_object)}'))

    def print_colors(self):
        print('\n'.join([f'{i + 1} автомобиль: {self[i].color}' for i in range(len(self))]))

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
        print('\n'.join([f'{i + 1} самолет: {self[i].color}' for i in range(len(self))]))

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
        print('\n'.join([f'{i + 1} корабль: {self[i].color}' for i in range(len(self))]))

    def print_ship(self):
        print('\n'.join([f'Длина корабля №{i + 1} больше 150 метров' for i in range(len(self))]))
