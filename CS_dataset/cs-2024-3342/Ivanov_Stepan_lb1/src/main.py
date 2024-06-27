from typing import Callable, Any


class DataDescriptor:
    def __init__(self, is_correct_val: Callable) -> None:
        self._is_correct_val = is_correct_val
    
    def __set_name__(self, owner, name) -> None:
        self._name = f"_{owner.__name__}__{name}"
    
    def __get__(self, instance, _) -> Any:
        return getattr(instance, self._name)
    
    def __set__(self, instance, value) -> None:
        if not self._is_correct_val(value):
            raise ValueError("Invalid value")

        setattr(instance, self._name, value)


class Transport:
    '''Поля объекта класс Transport:
    average_speed - cредняя скорость (в км/ч, положительное целое число)
    max_speed - максимальная скорость (в км/ч, положительное  целое число)
    price - цена (в руб., положительное целое число)
    cargo - грузовой (значениями могут быть или True, или False)
    color - цвет (значение может быть одной из строк: W (white), G(gray), B(blue)).
    При создании экземпляра класса Transport необходимо убедиться, что переданные в конструктор параметры удовлетворяют требованиям, иначе выбросить исключение ValueError с текстом 'Invalid value'.
    '''

    average_speed = DataDescriptor(
        lambda val: isinstance(val, int) and val > 0
    )

    max_speed = DataDescriptor(
        lambda val: isinstance(val, int) and val > 0
    )

    price = DataDescriptor(
        lambda val: isinstance(val, int) and val > 0
    )

    cargo = DataDescriptor(
        lambda val: isinstance(val, bool)
    )

    color = DataDescriptor(
        lambda val: val == 'w' or \
                    val == 'g' or \
                    val == 'b'
    )

    def __init__(
            self, 
            average_speed: int, 
            max_speed: int, 
            price: int, 
            cargo: bool, 
            color: str
        ) -> None:

        self.average_speed = average_speed
        self.max_speed = max_speed
        self.price = price
        self.cargo = cargo
        self.color = color

    
class Car(Transport): #Наследуется от класса Transport
    '''Поля объекта класс Car:
    average_speed - cредняя скорость (в км/ч, положительное целое число)
    max_speed - максимальная скорость (в км/ч, положительное целое число)
    price - цена (в руб., положительное целое число)
    cargo - грузовой (значениями могут быть или True, или False)
    color - цвет (значение может быть одной из строк: W (white), G(gray), B(blue)).
    power - мощность (в Вт, положительное целое число)
    wheels - количество колес (положительное целое число, не более 10)
    При создании экземпляра класса Car необходимо убедиться, что переданные в конструктор параметры удовлетворяют требованиям, иначе выбросить исключение ValueError с текстом 'Invalid value'.
    '''

    power = DataDescriptor(
        lambda val: isinstance(val, int) and val > 0
    )

    wheels = DataDescriptor(
        lambda val: isinstance(val, int) and val > 0 and val <= 10
    )
    
    def __str__(self) -> str: 
        '''Преобразование к строке вида: Car: средняя скорость <средняя скорость>, максимальная скорость <максимальная скорость>, цена <цена>, грузовой <грузовой>, цвет <цвет>, мощность <мощность>, количество колес <количество колес>.'''
        
        return f"Car: средняя скорость {self.average_speed}, максимальная скорость {self.max_speed}, цена {self.price}, грузовой {self.cargo}, цвет {self.color}, мощность {self.power}, количество колес {self.wheels}."
    
    def __add__(self) -> int:
        '''Сложение средней скорости и максимальной скорости автомобиля. Возвращает число, полученное при сложении средней и максимальной скорости.'''
        
        return self.average_speed + self.max_speed
    
    def __eq__(self, other) -> bool: 
        '''Метод возвращает True, если два объекта класса равны, и False иначе. Два объекта типа Car равны, если равны количество колес, средняя скорость, максимальная скорость и мощность.'''    
        
        return self.wheels == other.wheels and \
               self.average_speed == other.average_speed and \
               self.max_speed == other.max_speed and \
               self.power == other.power
    
    def __init__(
            self, 
            average_speed: int, 
            max_speed: int, 
            price: int, 
            cargo: bool, 
            color: str,
            power: int,
            wheels: int
        ) -> None:

        super().__init__(average_speed, max_speed, price, cargo, color)

        self.power = power
        self.wheels = wheels


class Plane(Transport): #Наследуется от класса Transport
    '''Поля объекта класс Plane:
    average_speed - cредняя скорость (в км/ч, положительное целое число)
    max_speed - максимальная скорость (в км/ч, положительное целое число)
    price - цена (в руб., положительное целое число)
    cargo - грузовой (значениями могут быть или True, или False)
    color - цвет (значение может быть одной из строк: W (white), G(gray), B(blue)).
    load_capacity - грузоподъемность (в кг, положительное целое число)
    wingspan - размах крыльев (в м, положительное целое число)
    При создании экземпляра класса Plane необходимо убедиться, что переданные в конструктор параметры удовлетворяют требованиям, иначе выбросить исключение ValueError с текстом 'Invalid value'.
    '''

    load_capacity = DataDescriptor(
        lambda val: isinstance(val, int) and val > 0
    )

    wingspan = DataDescriptor(
        lambda val: isinstance(val, int) and val > 0
    )
    
    def __str__(self) -> str: 
        '''Преобразование к строке вида: Plane: средняя скорость <средняя скорость>, максимальная скорость <максимальная скорость>, цена <цена>, грузовой <грузовой>, цвет <цвет>, грузоподъемность <грузоподъемность>, размах крыльев <размах крыльев>.'''
        
        return f"Plane: средняя скорость {self.average_speed}, максимальная скорость {self.max_speed}, цена {self.price}, грузовой {self.cargo}, цвет {self.color}, грузоподъемность {self.load_capacity}, размах крыльев {self.wingspan}."

    def __add__(self) -> int: 
        '''Сложение средней скорости и максимальной скорости самолета. Возвращает число, полученное при сложении средней и максимальной скорости.'''
        
        return self.average_speed + self.max_speed
    
    def __eq__(self, other) -> bool: 
        '''Метод возвращает True, если два объекта класса равны по размерам, и False иначе. Два объекта типа Plane равны по размерам, если равны размах крыльев.'''
        
        return self.wingspan == other.wingspan
    
    def __init__(
            self, 
            average_speed: int, 
            max_speed: int, 
            price: int, 
            cargo: bool, 
            color: str,
            load_capacity: int,
            wingspan: int
        ) -> None:

        super().__init__(average_speed, max_speed, price, cargo, color)

        self.load_capacity = load_capacity
        self.wingspan = wingspan
    

class Ship(Transport): #Наследуется от класса Transport
    '''Поля объекта класс Ship:
    average_speed - cредняя скорость (в км/ч, положительное целое число)
    max_speed - максимальная скорость (в км/ч, положительное целое число)
    price - цена (в руб., положительное целое число)
    cargo - грузовой (значениями могут быть или True, или False)
    color - цвет (значение может быть одной из строк: W (white), G(gray), B(blue)).
    length - длина (в м, положительное целое число)
    side_height - высота борта (в м, положительное целое число)
    При создании экземпляра класса Ship необходимо убедиться, что переданные в конструктор параметры удовлетворяют требованиям, иначе выбросить исключение ValueError с текстом 'Invalid value'.
    '''

    length = DataDescriptor(
        lambda val: isinstance(val, int) and val > 0
    )

    side_height = DataDescriptor(
        lambda val: isinstance(val, int) and val > 0
    )
    
    def __str__(self) -> str: 
        '''Преобразование к строке вида: Ship: средняя скорость <средняя скорость>, максимальная скорость <максимальная скорость>, цена <цена>, грузовой <грузовой>, цвет <цвет>, длина <длина>, высота борта <высота борта>.'''
        
        return f"Ship: средняя скорость {self.average_speed}, максимальная скорость {self.max_speed}, цена {self.price}, грузовой {self.cargo}, цвет {self.color}, длина {self.length}, высота борта {self.side_height}."

    def __add__(self) -> int: 
        '''Сложение средней скорости и максимальной скорости корабля. Возвращает число, полученное при сложении средней и максимальной скорости.'''
        
        return self.average_speed + self.max_speed
    
    def __eq__(self, other) -> bool: 
        '''Метод возвращает True, если два объекта класса равны по размерам, и False иначе. Два объекта типа Ship равны по размерам, если равны их длина и высота борта.'''
        
        return self.length == other.length and \
               self.side_height == other.side_height
    
    def __init__(
            self, 
            average_speed: int, 
            max_speed: int, 
            price: int, 
            cargo: bool, 
            color: str,
            length: int,
            side_height: int
        ) -> None:

        super().__init__(average_speed, max_speed, price, cargo, color)

        self.length = length
        self.side_height = side_height
    

class CarList(list): # – список автомобилей - наследуется от класса list.
    def __init__(self, name: str) -> None:
        '''1. Вызвать конструктор базового класса.
           2. Передать в конструктор строку name и присвоить её полю name созданного объекта'''
        
        super().__init__()

        self.name = name
           
    def append(self, p_object: Car) -> None: 
        '''Переопределение метода append() списка. В случае, если p_object - автомобиль, элемент добавляется в список, иначе выбрасывается исключение TypeError с текстом: Invalid type <тип_объекта p_object> (результат вызова функции type)'''
        
        if not isinstance(p_object, Car):
            raise TypeError(f"Invalid type {type(p_object)}")
        
        super().append(p_object)

    def print_colors(self) -> None: 
        '''Вывести цвета всех автомобилей в виде строки:
            <i> автомобиль: color[i]
            <j> автомобиль: color[j] ...'''
        
        for i, car in enumerate(self, 1):
            print(f"{i} автомобиль: {car.color}")
            
    def print_count(self) -> int: 
        '''Вывести количество автомобилей.'''

        print(len(self))
    
        
class PlaneList(list): # – список самолетов - наследуется от класса list.
    def __init__(self, name: str) -> None:
        '''1. Вызвать конструктор базового класса.
           2. Передать в конструктор строку name и присвоить её полю name созданного объекта'''
        
        super().__init__()

        self.name = name

    def extend(self, iterable) -> None: 
        '''Переопределение метода extend() списка. В случае, если элемент iterable - объект класса Plane, этот элемент добавляется в список, иначе не добавляется.'''

        for el in iterable:
            if not isinstance(el, Plane):
                continue

            self.append(el)

    def print_colors(self) -> None: 
        '''Вывести цвета всех самолетов в виде строки:
            <i> самолет: color[i]
            <j> самолет: color[j] ...'''
        
        for i, plane in enumerate(self, 1):
            print(f"{i} самолет: {plane.color}")

    def total_speed(self) -> int: 
        '''Посчитать и вывести общую среднюю скорость всех самолетов.'''

        print(sum(plane.average_speed for plane in self))


class ShipList(list): # – список кораблей - наследуется от класса list.
    def __init__(self, name: str) -> None:
        '''1. Вызвать конструктор базового класса.
           2. Передать в конструктор строку name и присвоить её полю name созданного объекта'''
        
        super().__init__()

        self.name = name

    def append(self, p_object: Ship) -> None: 
        '''Переопределение метода append() списка. В случае, если p_object - корабль, элемент добавляется в список, иначе выбрасывается исключение TypeError с текстом: Invalid type <тип_объекта p_object>'''

        if not isinstance(p_object, Ship):
            raise TypeError(f"Invalid type {type(p_object)}")
        
        super().append(p_object)
    
    def print_colors(self) -> None: 
        '''Вывести цвета всех кораблей в виде строки:
            <i> корабль: color[i]
            <j> корабль: color[j] ...'''
        
        for i, ship in enumerate(self, 1):
            print(f"{i} корабль: {ship.color}")
            
    def print_ship(self) -> None: 
        '''Вывести те корабли, чья длина больше 150 метров.'''

        for i, ship in enumerate(self, 1):
            if ship.length <= 150:
                continue

            print(f"Длина корабля №{i} больше 150 метров")
