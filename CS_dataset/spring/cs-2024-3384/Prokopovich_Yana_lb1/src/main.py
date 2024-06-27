class Transport:
    def __init__(self, average_speed, max_speed, price, cargo, color):
        if (average_speed > 0) and (int(average_speed) == average_speed):
            self.average_speed = average_speed
        else:
            raise ValueError("Invalid value")
        if (max_speed > 0) and (int(max_speed) == max_speed):
            self.max_speed = max_speed
        else:
            raise ValueError("Invalid value")
        if (price > 0) and (int(price) == price):
            self.price = price
        else:
            raise ValueError("Invalid value")
        if isinstance(cargo, bool):
            self.cargo = cargo
        else:
            raise ValueError("Invalid value")
        if color == 'w' or color == 'g' or color == 'b':
            self.color = color
        else:
            raise ValueError("Invalid value")


class Car(Transport):
    def __init__(self,  average_speed, max_speed, price, cargo, color, power, wheels):
        super().__init__(average_speed, max_speed, price, cargo, color)
        if (power > 0 and (int(power) == power)) and (0 < wheels <= 10 and (int(wheels) == wheels)):
            self.power = power
            self.wheels = wheels
        else:
            raise ValueError("Invalid value")

    def __str__(self):
        return f"Car: средняя скорость {self.average_speed}, максимальная скорость {self.max_speed}, цена {self.price}, грузовой {self.cargo}, цвет {self.color}, мощность {self.power}, количество колес {self.wheels}."

    def __add__(self):
        return self.average_speed + self.max_speed

    def __eq__(self, other):
        if (self.wheels == other.wheels) and (self.average_speed == other.average_speed) and (self.average_speed == other.average_speed) and (self.max_speed == other.max_speed) and (self.power == other.power):
            return True
        return False


class Plane(Transport):
    def __init__(self, average_speed, max_speed, price, cargo, color, load_capacity, wingspan):
        super().__init__(average_speed, max_speed, price, cargo, color)
        if (load_capacity > 0 and (int(load_capacity) == load_capacity)) and (wingspan > 0 and (int(wingspan) == wingspan)):
            self.load_capacity = load_capacity
            self.wingspan = wingspan
        else:
            raise ValueError("Invalid value")

    def __str__(self):
        return f"Plane: средняя скорость {self.average_speed}, максимальная скорость {self.max_speed}, цена {self.price}, грузовой {self.cargo}, цвет {self.color}, грузоподъемность {self.load_capacity}, размах крыльев {self.wingspan}."

    def __add__(self):
        return self.average_speed + self.max_speed

    def __eq__(self, other):
        if self.wingspan == other.wingspan:
            return True
        return False


class Ship(Transport):
    def __init__(self, average_speed, max_speed, price, cargo, color, length, side_height):
        super().__init__(average_speed, max_speed, price, cargo, color)
        if (length > 0 and (int(length) == length)) and (side_height > 0 and (int(side_height) == side_height)):
            self.length = length
            self.side_height = side_height
        else:
            raise ValueError("Invalid value")

    def __str__(self):
        return f"Ship: средняя скорость {self.average_speed}, максимальная скорость {self.max_speed}, цена {self.price}, грузовой {self.cargo}, цвет {self.color}, длина {self.length}, высота борта {self.side_height}."

    def __add__(self):
        return self.average_speed + self.max_speed

    def __eq__(self, other):
        if (self.length == other.length) and (self.side_height == other.side_height):
            return True
        return False


class CarList(list):
    def __init__(self, name):
        super().__init__()
        self.name = name

    def append(self, p_object):
        if isinstance(p_object, Car):
            super().append(p_object)
        else:
            raise TypeError(f"Invalid type {type(p_object)}")

    def print_colors(self):
        for i, car in enumerate(self):
            print(f"{i+1} автомобиль: {car.color}")

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
        for i, plane in enumerate(self):
            print(f"{i+1} самолет: {plane.color}")

    def total_speed(self):
        speed = 0
        for plane in self:
            speed += plane.average_speed
        print(speed)


class ShipList(list):
    def __init__(self, name):
        super().__init__()
        self.name = name

    def append(self, p_object):
        if isinstance(p_object, Ship):
            super().append(p_object)
        else:
            raise TypeError(f"Invalid type {type(p_object)}")

    def print_colors(self):
        for i, ship in enumerate(self):
            print(f"{i+1} корабль: {ship.color}")

    def print_ship(self):
        for i, ship in enumerate(self):
            if ship.length > 150:
                print(f"Длина корабля №{i+1} больше 150 метров")