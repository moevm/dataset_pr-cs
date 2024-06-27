class Transport:
    def __init__(self, average_speed, max_speed, price, cargo, color):
        if not(isinstance(average_speed, int)) or average_speed <= 0 or not(
                isinstance(max_speed, int)) or max_speed <= 0 or not(isinstance(price, int)) or price <= 0 or not(isinstance(
                cargo, bool)) or (color not in ('w', 'g', 'b')):
            raise ValueError('InvalidValue')
        self.average_speed = average_speed
        self.max_speed = max_speed
        self.price = price
        self.cargo = cargo
        self.color = color



class Car(Transport):
    def __init__(self, average_speed, max_speed, price, cargo, color, power, wheels):
        super().__init__(average_speed, max_speed, price, cargo, color)
        if not(isinstance(power, int)) or (power <= 0) or not(isinstance(wheels, int)) or (0 >= wheels) or wheels > 10:
            raise ValueError('InvalidValue')
        self.power = power
        self.wheels = wheels

    def __str__(self):
        return f'Car: средняя скорость {self.average_speed}, максимальная скорость {self.max_speed}, цена {self.price}, грузовой {self.cargo}, цвет {self.color}, мощность {self.power}, количество колес {self.wheels}.'


    def __add__(self):
        return self.average_speed + self.max_speed

    def __eq__(self, other):
        return self.wheels == other.wheels and self.average_speed == other.average_speed and self.max_speed == other.max_speed and self.power == other.power



class Plane(Transport):  # Наследуется от класса Transport
    def __init__(self, average_speed, max_speed, price, cargo, color, load_capacity, wingspan):
        super().__init__(average_speed, max_speed, price, cargo, color)
        if not(isinstance(load_capacity, int)) or load_capacity <= 0 or not(isinstance(wingspan, int)) or wingspan <= 0:
            raise ValueError('InvalidValue')
        self.load_capacity = load_capacity
        self.wingspan = wingspan

    def __str__(self):
        return f'Plane: средняя скорость {self.average_speed}, максимальная скорость {self.max_speed}, цена {self.price}, грузовой {self.cargo}, цвет {self.color}, грузоподъемность {self.load_capacity}, размах крыльев {self.wingspan}.'

    def __add__(self):
        return self.average_speed + self.max_speed

    def __eq__(self, other):
        return self.wingspan == other.wingspan


class Ship(Transport):  # Наследуется от класса Transport
    def __init__(self, average_speed, max_speed, price, cargo, color, length, side_height):
        super().__init__(average_speed, max_speed, price, cargo, color)
        if not(isinstance(length, int)) or length <= 0 or not(isinstance(side_height, int)) or side_height <= 0:
            raise ValueError('InvalidValue')
        self.length = length
        self.side_height = side_height

    def __str__(self):
        return f'Ship: средняя скорость {self.average_speed}, максимальная скорость {self.max_speed}, цена {self.price}, грузовой {self.cargo}, цвет {self.color}, длина {self.length}, высота борта {self.side_height}.'

    def __add__(self):
        return self.average_speed + self.max_speed

    def __eq__(self, other):
        return self.side_height == other.side_height and self.length == other.length



class CarList(list):
    def __init__(self, name):
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
            print(f'{j} автомобиль: {i.color}')
            j += 1

    def print_count(self):
        print(list.__len__(self))



class PlaneList(list):
    def __init__(self, name):
        list.__init__(self)
        self.name = name

    def append(self, p_object):
        if isinstance(p_object, Plane):
            list.append(self, p_object)

    def extend(self, arr):
        for i in arr:
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
    def __init__(self, name):
        list.__init__(self)
        self.name = name
    def append(self, p_object):
        if isinstance(p_object, Ship):
            list.append(self, p_object)
        else:
            raise TypeError(f'Invalid type {type(p_object)}')

    def print_colors(self):
        j = 1
        for i in self:
            print(f'{j} корабль: {i.color}')
            j += 1
    def print_ship(self):
        j = 1
        for i in self:
            if i.length > 150:
                print(f'Длина корабля №{j} больше 150 метров')
                j += 1
