class Transport:
    def __init__(self, average_speed, max_speed, price, cargo, color):
        if (average_speed > 0 and max_speed > 0 and price > 0
                and isinstance(cargo, bool)
                and (color == 'w' or color == 'g' or color == 'b')):

            self.average_speed = average_speed
            self.max_speed = max_speed
            self.price = price
            self.cargo = cargo
            self.color = color

        else:
            raise ValueError("Invalid value")

    def __add__(self):
        return self.average_speed + self.max_speed


class Car(Transport):
    def __init__(self, average_speed, max_speed, price, cargo, color, power, wheels):
        super().__init__(average_speed, max_speed, price, cargo, color)
        if power > 0 and 0 < wheels <= 10:
            self.power = power
            self.wheels = wheels
        else:
            raise ValueError("Invalid value")

    def __str__(self):
        string = (f"Car: средняя скорость {self.average_speed}, максимальная скорость {self.max_speed}, "
                  f"цена {self.price}, грузовой {self.cargo}, цвет {self.color}, "
                  f"мощность {self.power}, количество колес {self.wheels}.")

        return string

    def __eq__(self, other):
        if self.wheels == other.wheels and self.average_speed == other.average_speed and self.max_speed == other.max_speed:
            return True
        else:
            return False


class Plane(Transport):
    def __init__(self, average_speed, max_speed, price, cargo, color, load_capacity, wingspan):
        super().__init__(average_speed, max_speed, price, cargo, color)

        if load_capacity > 0 and wingspan > 0:
            self.load_capacity = load_capacity
            self.wingspan = wingspan
        else:
            raise ValueError("Invalid value")

    def __str__(self):
        string = (f"Plane: средняя скорость {self.average_speed}, максимальная скорость {self.max_speed}, "
                  f"цена {self.price}, грузовой {self.cargo}, цвет {self.color}, "
                  f"грузоподъемность {self.load_capacity}, размах крыльев {self.wingspan}.")
        return string

    def __eq__(self, other):
        if self.wingspan == other.wingspan:
            return True
        else:
            return False


class Ship(Transport):
    def __init__(self, average_speed, max_speed, price, cargo, color, length, side_height):
        super().__init__(average_speed, max_speed, price, cargo, color)
        if length > 0 and side_height > 0:
            self.length = length
            self.side_height = side_height
        else:
            raise ValueError("Invalid value")

    def __str__(self):
        string = (f"Ship: средняя скорость {self.average_speed}, максимальная скорость {self.max_speed}, "
                  f"цена {self.price}, грузовой {self.cargo}, цвет {self.color}, "
                  f"длина {self.length}, высота борта {self.side_height}.")
        return string

    def __eq__(self, other):
        if self.length == other.length and self.side_height == other.side_height:
            return True
        else:
            return False


class CarList(list):
    def __init__(self, name):
        super().__init__()
        self.name = name

    def append(self, obj):
        if isinstance(obj, Car):
            super().append(obj)
        else:
            raise TypeError(f"Invalid type {type(obj)}")

    def print_colors(self):
        for i, car in enumerate(self):
            print(f"{i + 1} автомобиль: {car.color}")

    def print_count(self):
        count = 0
        for car in self:
            count += 1
        print(count)
        


class PlaneList(list):
    def __init__(self, name):
        super().__init__()
        self.name = name

    def extend(self, obj):
        obj = list(filter(lambda x: isinstance(x, Plane), obj))
        super().extend(obj)

    def print_colors(self):
        for i, plane in enumerate(self):
            print(f"{i + 1} самолет: {plane.color}")

    def total_speed(self):
        all_speed = 0
        for plane in self:
            all_speed += plane.average_speed
        print(all_speed)


class ShipList(list):
    def __init__(self, name):
        super().__init__()
        self.name = name

    def append(self, obj):
        if isinstance(obj, Ship):
            super().append(obj)
        else:
            raise TypeError(f"Invalid type {type(obj)}")

    def print_colors(self):
        for i, ship in enumerate(self):
            print(f"{i + 1} корабль: {ship.color}")

    def print_ship(self):
        for i, ship in enumerate(self):
            if ship.length > 150:
                print(f"Длина корабля №{i + 1} больше 150 метров")

