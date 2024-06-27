class Transport:
    def __init__(self, average_speed: int, max_speed: int, price: int, cargo: bool, color: str):
        if not isinstance(average_speed, int) or average_speed <= 0:
            raise ValueError("Invalid value")
        if not isinstance(max_speed, int) or max_speed <= 0 :
            raise ValueError("Invalid value")
        if not isinstance(price, int) or price <= 0:
            raise ValueError("Invalid value")
        if not isinstance(cargo, bool):
            raise ValueError("Invalid value")
        if not isinstance(color, str) or color not in ('w', 'g', 'b'):
            raise ValueError("Invalid value")
        self.average_speed = average_speed
        self.max_speed = max_speed
        self.price = price
        self.cargo = cargo
        self.color = color

class Car(Transport):  # Наследуется от класса Transport
    def __init__(self, average_speed: int, max_speed: int, price: int, cargo: bool, color, power: int, wheels: int):
        if not isinstance(power, int) or power <= 0:
            raise ValueError("Invalid value")
        if not isinstance(wheels, int) or wheels <= 0:
            raise ValueError("Invalid value")
        super().__init__(average_speed, max_speed, price, cargo, color)
        self.power = power
        self.wheels = wheels

    def __str__(self):
        return f"Car: средняя скорость {self.average_speed}, максимальная скорость {self.max_speed}, цена {self.price}, грузовой {self.cargo}, цвет {self.color}, мощность {self.power}, количество колес {self.wheels}."

    def __add__(self):
        return (self.average_speed + self.max_speed)

    def __eq__(self, other):
        if not isinstance(other, Car):
            raise TypeError
        return (self.wheels == other.wheels and self.average_speed == other.average_speed and self.max_speed == other.max_speed and self.power == other.power)


class Plane(Transport):  # Наследуется от класса Transport
    def __init__(self, average_speed: int, max_speed: int, price: int, cargo: bool, color, load_capacity: int, wingspan: int):
        if not isinstance(load_capacity, int) or load_capacity <= 0:
            raise ValueError("Invalid value")
        if not isinstance(wingspan, int) or wingspan <= 0:
            raise ValueError("Invalid value")

        super().__init__(average_speed, max_speed, price, cargo, color)

        self.load_capacity = load_capacity
        self.wingspan = wingspan

    def __str__(self):
        return f"Plane: средняя скорость {self.average_speed}, максимальная скорость {self.max_speed}, цена {self.price}, грузовой {self.cargo}, цвет {self.color}, грузоподъемность {self.load_capacity}, размах крыльев {self.wingspan}."

    def __add__(self):
        return (self.average_speed + self.max_speed)

    def __eq__(self, other):
        if self is other:
            return True
        if not isinstance(other, Plane):
            raise TypeError
        return self.wingspan == other.wingspan


class Ship(Transport):  # Наследуется от класса Transport
    def __init__(self, average_speed: int, max_speed: int, price: int, cargo: bool, color, length: int, side_height: int):
        if not isinstance(length, int) or length <= 0:
            raise ValueError("Invalid value")
        if not isinstance(side_height, int) or side_height <= 0:
            raise ValueError("Invalid value")

        super().__init__(average_speed, max_speed, price, cargo, color)

        self.length = length
        self.side_height = side_height

    def __str__(self):
        return f'Ship: средняя скорость {self.average_speed}, максимальная скорость {self.max_speed}, цена {self.price}, грузовой {self.cargo}, цвет {self.color}, длина {self.length}, высота борта {self.side_height}.'

    def __add__(self):
        return (self.average_speed + self.max_speed)

    def __eq__(self, other):
        if not isinstance(other, Ship):
            raise TypeError
        if self is other:
            return True
        return self.length == other.length and self.side_height == other.side_height


class CarList(list):
    def __init__(self, name: str):
        list.__init__(self)
        self.name = name
    def append(self, p_object):
        if isinstance(p_object, Car):
            list.append(self, p_object)
        else:
            raise TypeError(f'Invalid type {type(p_object)}')

    def print_colors(self):
        j = 1
        for i in self:
            print(f"{j} автомобиль: {i.color}")
            j += 1
    def print_count(self):
        print(list.__len__(self))

class PlaneList(list):
    def __init__(self, name: str):
        list.__init__(self)
        self.name = name

    def append(self, p_object):
        if isinstance(p_object, Plane):
            list.append(self, p_object)

    def extend(self, lst):
        for i in lst:
            self.append(i)

    def print_colors(self):
        j = 1
        for i in self:
            print(f"{j} самолет: {i.color}")
            j += 1

    def total_speed(self):
        sum = 0
        for i in self:
            sum += i.average_speed
        print(sum)


class ShipList(list):
    def __init__(self, name: str):
        list.__init__(self)
        self.name = name
    def append(self, p_object):
        if isinstance(p_object, Ship):
            list.append(self, p_object)
        else:
            raise TypeError('Invalid type ', type(p_object))

    def print_colors(self):
        j = 1
        for i in self:
            print(f"{j} корабль: {i.color}")
            j += 1

    def print_ship(self):
        j = 1
        for i in self:
            if i.length > 150:
                print(f'Длина корабля №{j} больше 150 метров')
            j += 1