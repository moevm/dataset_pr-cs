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
        if color == 'w' or color == 'g' or color == 'b':
            self.color = color
        else:
            raise (ValueError('Invalid value'))


class Car(Transport):  # Наследуется от класса Transport
    def __init__(self, average_speed, max_speed, price, cargo, color, power, wheels):
        super().__init__(average_speed, max_speed, price, cargo, color)
        if power > 0 and isinstance(power, int):
            self.power = power
        else:
            raise (ValueError('Invalid value'))
        if wheels > 0 and isinstance(wheels, int):
            self.wheels = wheels
        else:
            raise (ValueError('Invalid value'))

    def __str__(self):
        return f"Car: средняя скорость {self.average_speed}, максимальная скорость {self.max_speed}, цена {self.price}, грузовой {self.cargo}, цвет {self.color}, мощность {self.power}, количество колес {self.wheels}."

    def __add__(self):
        return self.max_speed + self.average_speed

    def __eq__(self, other):
        if not isinstance(other, Car):
            raise ValueError("Invalid value")
        return (self.wheels == other.wheels) and (self.average_speed == other.average_speed) and (self.max_speed == other.max_speed) and (self.power == other.power)


class Plane(Transport):  # Наследуется от класса Transport
    def __init__(self, average_speed, max_speed, price, cargo, color, load_capacity, wingspan ):
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
        return f"Plane: средняя скорость {self.average_speed}, максимальная скорость {self.max_speed}, цена {self.price}, грузовой {self.cargo}, цвет {self.color}, грузоподъемность {self.load_capacity}, размах крыльев {self.wingspan}."

    def __add__(self):
        return self.average_speed + self.max_speed

    def __eq__(self, other):
        if not isinstance(other, Plane):
            raise ValueError("Invalid value")
        return self.wingspan == other.wingspan


class Ship(Transport):  # Наследуется от класса Transport
    def __init__(self, average_speed, max_speed, price, cargo, color, length, side_height ):
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
        return f"Ship: средняя скорость {self.average_speed}, максимальная скорость {self.max_speed}, цена {self.price}, грузовой {self.cargo}, цвет {self.color}, длина {self.length}, высота борта {self.side_height}."

    def __add__(self):
        return self.max_speed + self.average_speed

    def __eq__(self, other):
        if not isinstance(other, Ship):
            raise ValueError("Invalid value")
        return self.length == other.length and self.side_height == other.side_height


class CarList(list):
    def __init__(self, name):
        super().__init__(self)
        self.name = name

    def append(self, __object):
        if not isinstance(__object, Car):
            raise TypeError(f"Invalid type {type(__object)}")
        super().append(__object)

    def print_colors(self):
        for i in range(len(self)):
            print(f"{i+1} автомобиль: {self[i].color}")

    def print_count(self):
        print(len(self))


class PlaneList(list):
    def __init__(self, name):
        super().__init__()
        self.name = name

    def extend(self, iterable):
        for elem in iterable:
            if isinstance(elem, Plane):
                super().append(elem)

    def print_colors(self):
        for i in range(len(self)):
            print(f"{i+1} самолет: {self[i].color}")

    def total_speed(self):
        sum = 0
        for elem in self:
            sum += elem.average_speed
        print(sum)


class ShipList(list):
    def __init__(self, name):
        super().__init__()
        self.name = name

    def append(self, p_object):
        if not isinstance(p_object, Ship):
            raise TypeError(f"Invalid type {type(p_object)}")
        super().append(p_object)

    def print_colors(self):
        for i in range(len(self)):
            print(f"{i+1} корабль: {self[i].color}")

    def print_ship(self):
        for i in range(len(self)):
            if self[i].length > 150:
                print(f"Длина корабля №{i+1} больше 150 метров")
