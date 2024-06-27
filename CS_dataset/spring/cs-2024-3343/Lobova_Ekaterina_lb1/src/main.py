class Transport:
    def __init__(self, average_speed, max_speed, price, cargo, color):
        if any((type(x) is not int) for x in [average_speed, max_speed, price])\
                or (type(cargo) is not bool) or (type(color) is not str):
            raise ValueError("Invalid value")
        if average_speed <= 0 or max_speed <= 0 or price <= 0 or not(color == 'w' or color == 'g' or color == 'b'):
            raise ValueError("Invalid value")
        self.average_speed = average_speed
        self.max_speed = max_speed
        self.price = price
        self.cargo = cargo
        self.color = color
    pass

class Car(Transport):
    def __init__(self, average_speed, max_speed, price, cargo, color, power, wheels):
        super().__init__(average_speed, max_speed, price, cargo, color)
        if (type(power) is not int) or (type(wheels) is not int):
            raise ValueError("Invalid value")
        if power <= 0 or not(0 < wheels <= 10):
            raise ValueError("Invalid value")
        self.power = power
        self.wheels = wheels

    def __str__(self):
        return f"Car: средняя скорость {self.average_speed}, максимальная скорость {self.max_speed}, цена {self.price}, грузовой {self.cargo}, цвет {self.color}, мощность {self.power}, количество колес {self.wheels}."

    def __add__(self):
        return self.average_speed + self.max_speed

    def __eq__(self, other):
        return self.wheels == other.wheels and self.average_speed == other.average_speed and self.max_speed == other.max_speed and self.power == other.power
    pass

class Plane(Transport):
    def __init__(self, average_speed, max_speed, price, cargo, color, load_capacity, wingspan):
        super().__init__(average_speed, max_speed, price, cargo, color)
        if (type(load_capacity) is not int) or (type(wingspan) is not int):
            raise ValueError("Invalid value")
        if load_capacity <= 0 or wingspan <= 0:
            raise ValueError("Invalid value")
        self.load_capacity = load_capacity
        self.wingspan = wingspan

    def __str__(self):
        return f"Plane: средняя скорость {self.average_speed}, максимальная скорость {self.max_speed}, цена {self.price}, грузовой {self.cargo}, цвет {self.color}, грузоподъемность {self.load_capacity}, размах крыльев {self.wingspan}."

    def __add__(self):
        return self.average_speed + self.max_speed

    def __eq__(self, other):
        return self.wingspan == other.wingspan
    pass

class Ship(Transport):
    def __init__(self, average_speed, max_speed, price, cargo, color, length, side_height):
        super().__init__(average_speed, max_speed, price, cargo, color)
        if (type(length) is not int) or (type(side_height) is not int):
            raise ValueError("Invalid value")
        if length <= 0 or side_height <= 0:
            raise ValueError("Invalid value")
        self.length = length
        self.side_height = side_height

    def __str__(self):
        return f"Ship: средняя скорость {self.average_speed}, максимальная скорость {self.max_speed}, цена {self.price}, грузовой {self.cargo}, цвет {self.color}, длина {self.length}, высота борта {self.side_height}."

    def __add__(self):
        return self.average_speed + self.max_speed

    def __eq__(self, other):
        return self.length == other.length and self.side_height == other.side_height
    pass

class CarList(list):
    def __init__(self, name):
        super().__init__()
        self.name = name

    def append(self, p_object):
        if isinstance(p_object, Car):
            super().append(p_object)
        else:
            raise TypeError("Invalid type {type(p_object)}")

    def print_colors(self):
        s = ""
        for i in range(len(self)):
            s += f"{i+1} автомобиль: {self[i].color}\n"
        print(s[:-1])

    def print_count(self):
        print(len(self))
    pass

class PlaneList(list):
    def __init__(self, name):
        super().__init__()
        self.name = name

    def extend(self, iterable):
        for i in range(len(iterable)):
            if isinstance(iterable[i], Plane):
                super().append(iterable[i])

    def print_colors(self):
        s = ""
        for i in range(len(self)):
            s += f"{i+1} самолет: {self[i].color}\n"
        print(s[:-1])

    def total_speed(self):
        print(sum(self[i].average_speed for i in range(len(self))))
    pass

class ShipList(list):
    def __init__(self, name):
        super().__init__()
        self.name = name

    def append(self, p_object):
        if isinstance(p_object, Ship):
            super().append(p_object)
        else:
            raise TypeError("Invalid type {type(p_object)}")

    def print_colors(self):
        s = ""
        for i in range(len(self)):
            s += f"{i+1} корабль: {self[i].color}\n"
        print(s[:-1])

    def print_ship(self):
        s = ""
        for i in range(len(self)):
            if self[i].length > 150:
                s += f"Длина корабля №{i+1} больше 150 метров\n"
        print(s[:-1])
    pass
