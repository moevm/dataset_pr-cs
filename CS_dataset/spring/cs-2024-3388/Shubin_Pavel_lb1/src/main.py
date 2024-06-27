class Transport:

    def __init__(self, average_speed, max_speed, price, cargo, color):
        if average_speed > 0 and isinstance(average_speed, int):
            self.average_speed = average_speed
        else:
            raise (ValueError('Invalid value'))
        if max_speed > 0 and isinstance(max_speed, int):
            self.max_speed = max_speed
        else:
            raise (ValueError('Invalid value'))
        if price > 0 and isinstance(price, int):
            self.price = price
        else:
            raise (ValueError('Invalid value'))
        if isinstance(cargo, bool):
            self.cargo = cargo
        else:
            raise (ValueError('Invalid value'))
        if color in ['w', 'g', 'b']:
            self.color = color
        else:
            raise (ValueError('Invalid value'))


class Car(Transport):

    def __init__(self, average_speed, max_speed, price, cargo, color, power, wheels):
        super().__init__(average_speed, max_speed, price, cargo, color)

        if power > 0 and isinstance(power, int):
            self.power = power
        else:
            raise (ValueError('Invalid value'))

        if 0 < wheels <= 10 and isinstance(wheels, int):
            self.wheels = wheels
        else:
            raise (ValueError('Invalid value'))

    def __str__(self):
        return 'Car: средняя скорость {}, максимальная скорость {},' \
               ' цена {}, грузовой {}, цвет {}, мощность {}, количество колес {}.'.format(self.average_speed, self.max_speed, self.price, self.cargo, self.color, self.power, self.wheels)

    def __add__(self):
        return self.average_speed + self.max_speed

    def __eq__(self, other):
        res = self.average_speed == other.average_speed and self.max_speed == other.max_speed \
              and self.power == other.power and self.wheels == other.wheels
        return res


class Plane(Transport):

    def __init__(self, average_speed, max_speed, price, cargo, color, load_capacity, wingspan):
        super().__init__(average_speed, max_speed, price, cargo, color)
        if load_capacity > 0 and isinstance(load_capacity, int):
            self.load_capacity = load_capacity
        else:
            raise (ValueError('Invalid value'))
        if wingspan > 0 and isinstance(wingspan, int):
            self.wingspan = wingspan
        else:
            raise (ValueError('Invalid value'))

    def __str__(self):
        return 'Plane: средняя скорость {}, ' \
               'максимальная скорость {}, ' \
               'цена {}, грузовой {}, цвет {}, ' \
               'грузоподъемность {}, размах крыльев {}.'.format(self.average_speed, self.max_speed, self.price, self.cargo, self.color, self.load_capacity, self.wingspan)

    def __add__(self):
        return self.average_speed + self.max_speed

    def __eq__(self, other):
        res = self.wingspan == other.wingspan
        return res


class Ship(Transport):

    def __init__(self, average_speed, max_speed, price, cargo, color, length, side_height):
        super().__init__(average_speed, max_speed, price, cargo, color)
        if length > 0 and isinstance(length, int):
            self.length = length
        else:
            raise (ValueError('Invalid value'))
        if side_height > 0 and isinstance(side_height, int):
            self.side_height = side_height
        else:
            raise (ValueError('Invalid value'))

    def __str__(self):
        return 'Ship: средняя скорость {}, максимальная скорость {}, цена {}, ' \
               'грузовой {}, цвет {}, длина {}, высота борта {}.'.format(self.average_speed, self.max_speed, self.price, self.cargo, self.color, self.length, self.side_height)

    def __add__(self):
        return self.average_speed + self.max_speed

    def __eq__(self, other):
        res = (self.length == other.length) and (self.side_height == other.side_height)
        return res


class CarList(list):

    def __init__(self, name):
        super().__init__()
        self.name = name

    def append(self, p_object):
        if isinstance(p_object, Car):
            super().append(p_object)
        else:
            t = type(p_object)
            raise (TypeError('Invalid type {}'.format(t)))

    def print_colors(self):
        print('\n'.join([f'{i+1} автомобиль: {self[i].color}' for i in range(len(self))]))

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
        print('\n'.join([f'{i+1} самолет: {self[i].color}' for i in range(len(self))]))

    def total_speed(self):
        sum = 0
        for i in self:
            sum += i.average_speed
        print(sum)


class ShipList(list):

    def __init__(self, name):
        super().__init__()
        self.name = name

    def append(self, p_object):
        if isinstance(p_object, Ship):
            super().append(p_object)
        else:
            t = type(p_object)
            raise (TypeError('Invalid type {}'.format(t)))

    def print_colors(self):
        print('\n'.join([f'{i+1} корабль: {self[i].color}' for i in range(len(self))]))

    def print_ship(self):
        for i in range(len(self)):
            if self[i].length > 150:
                print(f'Длина корабля №{i+1} больше 150 метров')
