class Transport:
    '''Поля объекта класс Transport:
    average_speed - cредняя скорость (в км/ч, положительное целое число)
    max_speed - максимальная скорость (в км/ч, положительное  целое число)
    price - цена (в руб., положительное целое число)
    cargo - грузовой (значениями могут быть или True, или False)
    color - цвет (значение может быть одной из строк: W (white), G(gray), B(blue)).
    При создании экземпляра класса Transport необходимо убедиться, что переданные в конструктор параметры удовлетворяют требованиям, иначе выбросить исключение ValueError с текстом 'Invalid value'.
    '''
    def __init__(self, average_speed, max_speed, price, cargo, color):
        #run all checks
        if(type(average_speed) != int or average_speed <= 0 or \
            type(max_speed) != int  or max_speed <= 0 or \
            type(price)     != int  or price     <= 0 or \
            type(cargo)     != bool or \
            type(color)     != str or color not in list('wgb')):
            raise ValueError('Invalid value')
        
        #save values
        self.average_speed = average_speed
        self.max_speed     = max_speed
        self.price         = price
        self.cargo         = cargo
        self.color         = color
    
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
    def __init__(self, *args):
        #check args
        if(len(args) != 7): raise TypeError("Missing positional argument(s)")
        power, wheels = args[5:]
        if(type(power) != int or power <= 0 or \
            type(wheels) != int or wheels <= 0 or wheels > 10):
            raise ValueError('Invalid value')
        
        #save values
        super().__init__(*args[:5])
        self.power  = args[5]
        self.wheels = args[6]
    
    def __str__(self):
        #Преобразование к строке вида: Car: средняя скорость <средняя скорость>, максимальная скорость <максимальная скорость>, цена <цена>, грузовой <грузовой>, цвет <цвет>, мощность <мощность>, количество колес <количество колес>.
        return f"Car: средняя скорость {self.average_speed}, максимальная скорость {self.max_speed}, цена {self.price}, грузовой {self.cargo}, цвет {self.color}, мощность {self.power}, количество колес {self.wheels}."

    def __add__(self): 
        #Сложение средней скорости и максимальной скорости автомобиля. Возвращает число, полученное при сложении средней и максимальной скорости.
        return self.average_speed + self.max_speed

    def __eq__(self, other): 
        #Метод возвращает True, если два объекта класса равны, и False иначе. Два объекта типа Car равны, если равны количество колес, средняя скорость, максимальная скорость и мощность.
        return all([self.wheels == other.wheels, self.average_speed == other.average_speed, self.max_speed == other.max_speed, self.power == other.power])
    
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
    def __init__(self, *args):
        #check args
        if(len(args) != 7): raise TypeError("Missing positional argument(s)")
        load_capacity, wingspan = args[5:]
        if(type(load_capacity) != int or load_capacity <= 0 or \
            type(wingspan) != int or wingspan <= 0):
            raise ValueError('Invalid value')
        
        #save values
        super().__init__(*args[:5])
        self.load_capacity  = args[5]
        self.wingspan = args[6]
    
    def __str__(self):
        '''Преобразование к строке вида: Plane: средняя скорость <средняя скорость>, максимальная скорость <максимальная скорость>, цена <цена>, грузовой <грузовой>, цвет <цвет>, грузоподъемность <грузоподъемность>, размах крыльев <размах крыльев>.'''
        return f"Plane: средняя скорость {self.average_speed}, максимальная скорость {self.max_speed}, цена {self.price}, грузовой {self.cargo}, цвет {self.color}, грузоподъемность {self.load_capacity}, размах крыльев {self.wingspan}."
    
    def __add__(self): 
        '''Сложение средней скорости и максимальной скорости самолета. Возвращает число, полученное при сложении средней и максимальной скорости.'''
        return self.average_speed + self.max_speed
    
    def __eq__(self, other): 
        '''Метод возвращает True, если два объекта класса равны по размерам, и False иначе. Два объекта типа Plane равны по размерам, если равны размах крыльев.'''
        return self.wingspan == other.wingspan
    
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
    def __init__(self, *args):
        #check args
        if(len(args) != 7): raise TypeError("Missing positional argument(s)")
        length, side_height = args[5:]
        if(type(length) != int or length <= 0 or \
            type(side_height) != int or side_height <= 0):
            raise ValueError('Invalid value')
        
        #save values
        super().__init__(*args[:5])
        self.length  = args[5]
        self.side_height = args[6]
    
    def __str__(self): 
        '''Преобразование к строке вида: Ship: средняя скорость <средняя скорость>, максимальная скорость <максимальная скорость>, цена <цена>, грузовой <грузовой>, цвет <цвет>, длина <длина>, высота борта <высота борта>.'''
        return f"Ship: средняя скорость {self.average_speed}, максимальная скорость {self.max_speed}, цена {self.price}, грузовой {self.cargo}, цвет {self.color}, длина {self.length}, высота борта {self.side_height}."

    def __add__(self): 
        '''Сложение средней скорости и максимальной скорости корабля. Возвращает число, полученное при сложении средней и максимальной скорости.'''
        return self.average_speed + self.max_speed
    
    def __eq__(self, other): 
        '''Метод возвращает True, если два объекта класса равны по размерам, и False иначе. Два объекта типа Ship равны по размерам, если равны их длина и высота борта.'''
        return self.length == other.length and self.side_height == other.side_height

class CarList(list):
    def __init__(self, name):
        '''1. Вызвать конструктор базового класса.
           2. Передать в конструктор строку name и присвоить её полю name созданного объекта'''
        super().__init__()
        self.name = name
    
    def append(self, p_object): 
        '''Переопределение метода append() списка. В случае, если p_object - автомобиль, элемент добавляется в список, иначе выбрасывается исключение TypeError с текстом: Invalid type <тип_объекта p_object> (результат вызова функции type)'''
        if(type(p_object) == Car): super().append(p_object)
        else: raise TypeError(f"Invalid type {type(p_object)}")

    def print_colors(self):
        '''Вывести цвета всех автомобилей в виде строки:
            <i> автомобиль: color[i]
            <j> автомобиль: color[j] ...'''
        for i, car in enumerate(self):
            print(f"{i+1} автомобиль: {car.color}")
            
    def print_count(self): 
        '''Вывести количество автомобилей.'''
        print(len(self))

class PlaneList(list):
    def __init__(self, name):
        '''1. Вызвать конструктор базового класса.
           2. Передать в конструктор строку name и присвоить её полю name созданного объекта'''
        super().__init__()
        self.name = name

    def extend(self, iterable): 
        '''Переопределение метода extend() списка. В случае, если элемент iterable - объект класса Plane, этот элемент добавляется в список, иначе не добавляется.'''
        super().extend(filter(lambda x: type(x) == Plane, iterable))
        
    def print_colors(self): 
        '''Вывести цвета всех самолетов в виде строки:
            <i> самолет: color[i]
            <j> самолет: color[j] ...'''
        for i, plane in enumerate(self):
            print(f"{i+1} самолет: {plane.color}")
            
    def total_speed(self): 
        '''Посчитать и вывести общую среднюю скорость всех самолетов.'''
        print(sum([i.average_speed for i in self]))
        
class ShipList(list):
    def __init__(self, name):
        '''1. Вызвать конструктор базового класса.
           2. Передать в конструктор строку name и присвоить её полю name созданного объекта'''
        super().__init__()
        self.name = name

    def append(self, p_object): 
        '''Переопределение метода append() списка. В случае, если p_object - корабль, элемент добавляется в список, иначе выбрасывается исключение TypeError с текстом: Invalid type <тип_объекта p_object>'''
        if(type(p_object) == Ship): super().append(p_object)
        else: raise TypeError(f"Invalid type {type(p_object)}")

    def print_colors(self): 
        '''Вывести цвета всех кораблей в виде строки:
            <i> корабль: color[i]
            <j> корабль: color[j] ...'''
        for i, ship in enumerate(self):
            print(f"{i+1} корабль: {ship.color}")
            
    def print_ship(self): 
        '''Вывести те корабли, чья длина больше 150 метров.'''
        print("\n".join(filter(lambda x: x != None, [f"Длина корабля №{i+1} больше 150 метров" if ship.length > 150 else None for i,ship in enumerate(self)])))
