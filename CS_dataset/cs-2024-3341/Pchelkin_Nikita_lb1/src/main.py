def positive_int_check(variables):
    if all(isinstance(var, int) and (var > 0) for var in variables):
        return True
    return False

class Transport:
    def __init__(self, average_speed, max_speed, price, cargo, color):
        if positive_int_check([average_speed, max_speed, price]) and type(cargo) == bool and any(color == x for x in ['w', 'g', 'b']):
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
        if positive_int_check([power, wheels]) and wheels <= 10:
            self.power = power
            self.wheels = wheels
        else:
            raise ValueError('Invalid value')

    def __str__(self):
        return f"Car: средняя скорость {self.average_speed}, максимальная скорость {self.max_speed}, цена {self.price}, грузовой {self.cargo}, цвет {self.color}, мощность {self.power}, количество колес {self.wheels}."

    def __add__(self):
        return self.average_speed + self.max_speed

    def __eq__(self, other):
        return self.wheels == other.wheels and self.average_speed == other.average_speed and self.max_speed == other.max_speed and self.power == other.power

class Plane(Transport):
    def __init__(self, average_speed, max_speed, price, cargo, color, load_capacity, wingspan):
        super().__init__(average_speed, max_speed, price, cargo, color)
        if positive_int_check([load_capacity, wingspan]):
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
        if positive_int_check([length, side_height]):
            self.length = length
            self.side_height = side_height
        else:
            raise ValueError('Invalid value')

    def __str__(self):
        return f"Ship: средняя скорость {self.average_speed}, максимальная скорость {self.max_speed}, цена {self.price}, грузовой {self.cargo}, цвет {self.color}, длина {self.length}, высота борта {self.side_height}."

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
        result = []
        for element in iterable:
            if isinstance(element, Plane):
                result.append(element)
        super().extend(result)

    def print_colors(self):
        for i in range(len(self)):
            print(f'{i+1} самолет: {self[i].color}')

    def total_speed(self):
        summary = 0
        for element in self:
            summary += element.average_speed
        print(summary)

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