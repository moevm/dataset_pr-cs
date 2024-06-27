class Character:
    def __init__(self, gender: str, age: int, height: int, weight: int):
        if not ((gender == 'm' or gender == 'w') and age >  0 and \
            height > 0 and weight > 0):
                raise ValueError('Invalid value')
        self.gender = gender
        self.age = age
        self.height = height
        self.weight = weight
    '''Поля объекта класс Character:
    gender - пол (значение может быть одной из строк: 'm', 'w')
    age - возраст (целое положительное число)
    height - рост (в сантиметрах, целое положительное число)
    weight - вес (в кг, целое положительное число)
    При создании экземпляра класса Character необходимо убедиться, что переданные в конструктор параметры удовлетворяют требованиям, иначе выбросить исключение ValueError с текстом 'Invalid value'.
    '''
    
class Warrior(Character):
    def __init__(self, gender: str, age: int, height: int, weight: int,
                    forces: int, physical_damage: int, armor: int):
        super().__init__(gender, age, height, weight)
        if not (forces > 0 and physical_damage > 0 and \
           armor > 0):
               raise ValueError('Invalid value')
        self.forces = forces
        self.physical_damage = physical_damage
        self.armor = armor
    '''Поля объекта класс Warrior:
    gender - пол (значение может быть одной из строк: 'm', 'w')
    age - возраст (целое положительное число)
    height - рост (в сантиметрах, целое положительное число)
    weight - вес (в кг, целое положительное число)
    forces - запас сил (целое положительное число)
    physical_damage - физический урон (целое положительное число)
    armor - количество брони (целое положительное число)
    При создании экземпляра класса Warrior необходимо убедиться, что переданные в конструктор параметры удовлетворяют требованиям, иначе выбросить исключение ValueError с текстом 'Invalid value'.
    '''

    def __str__(self):
        return f"Warrior: Пол {self.gender}, возраст {self.age}, рост {self.height}, вес {self.weight}, запас сил {self.forces}, физический урон {self.physical_damage}, броня {self.armor}."
    '''Преобразование к строке вида: Warrior: Пол <пол>, возраст <возраст>, рост <рост>, вес <вес>, запас сил <запас сил>, физический урон <физический урон>, броня <количество брони>.'''

    def __eq__(self, other):
        return self.physical_damage == other.physical_damage and \
            self.forces == other.forces and self.armor == other.armor
    '''Метод возвращает True, если два объекта класса равны и False иначе. Два объекта типа Warrior равны, если равны их урон, запас сил и броня.'''
    

class Magician(Character):
    def __init__(self, gender: str, age: int, height: int, weight: int,
                    mana: int, magic_damage: int):
        super().__init__(gender, age, height, weight) #Наследуется от класса Character
        if not(mana > 0 and magic_damage > 0):
            raise ValueError('Invalid vlaue')
        self.mana = mana
        self.magic_damage = magic_damage
    '''Поля объекта класс Magician:
    gender - пол (значение может быть одной из строк: 'm', 'w')
    age - возраст (целое положительное число)
    height - рост (в сантиметрах, целое положительное число)
    weight - вес (в кг, целое положительное число)
    mana - запас маны (целое положительное число)
    magic_damage - магический урон (целое положительное число)
    При создании экземпляра класса Magician необходимо убедиться, что переданные в конструктор параметры удовлетворяют требованиям, иначе выбросить исключение ValueError с текстом 'Invalid value'.
    '''
    def __str__(self):
        return f"Magician: Пол {self.gender}, возраст {self.age}, рост {self.height}, вес {self.weight}, запас маны {self.mana}, магический урон {self.magic_damage}."
    '''Преобразование к строке вида: Magician: Пол <пол>, возраст <возраст>, рост <рост>, вес <вес>, запас маны <запас маны>, магический урон <магический урон>.'''

    def __damage__(self):
        return self.mana * self.magic_damage
    '''Метод возвращает значение магического урона, который может нанести маг, если потратит сразу весь запас маны (умножение магического урона на запас маны).'''    


class Archer(Character): #Наследуется от класса Character
    def __init__(self, gender: str, age: int, height: int, weight: int,
                    forces: int, physical_damage: int, attack_range: int):
        super().__init__(gender, age, height, weight)
        if not (forces > 0 and physical_damage > 0 and \
           attack_range > 0):
               raise ValueError('Invalid value')
        self.forces = forces
        self.physical_damage = physical_damage
        self.attack_range = attack_range

    def __str__(self):
        return f'Archer: Пол {self.gender}, возраст {self.age}, рост {self.height}, вес {self.weight}, запас сил {self.forces}, физический урон {self.physical_damage}, дальность атаки {self.attack_range}.'
    
    def __eq__(self, other):
        return self.physical_damage == other.physical_damage and \
            self.forces == other.forces and self.attack_range == other.attack_range


class WarriorList(list):
    def __init__(self, name):
        self.name = name
        '''1. Вызвать конструктор базового класса. 
           2. Передать в конструктор строку name и присвоить её полю name созданного объекта'''

    def append(self, p_object):
        if isinstance(p_object, Warrior):
            super(WarriorList, self).append(p_object)
        else:
            raise TypeError(f'Invalid type <тип_объекта {p_object}>') 
        '''Переопределение метода append() списка. В случае, если p_object - Warrior, элемент добавляется в список, иначе выбрасывается исключение TypeError с текстом:  Invalid type <тип_объекта p_object>'''

    def print_count(self):
        print(len(self))
        '''Использование метода count(). Вывести количество воинов.''' 
        
class MagicianList(list):
    def __init__(self, name):
        self.name = name
        '''1. Вызвать конструктор базового класса. 
           2. Передать в конструктор строку name и присвоить её полю name созданного объекта'''
       
    def extend(self, iterable):
        for i in iterable:
            if isinstance(i, self.name):
                super(MagicianList, self).append(i) 
        '''Переопределение метода extend() списка. В случае, если элемент iterable - объект класса Magician, этот элемент добавляется в список, иначе не добавляется.'''

    def print_damage(self):
        print(sum([i.magic_damage for i in self]))
        '''Вывести общий урон всех магов.'''     
        
class ArcherList(list):
    def __init__(self, name):
        super().__init__()
        self.name = name
        '''1. Вызвать конструктор базового класса. 
           2. Передать в конструктор строку name и присвоить её полю name созданного объекта'''
           
    def append(self, p_object):
        if isinstance(p_object, self.name):
            super(ArcherList, self).append(p_object)
        else:
            raise TypeError(f'Invalid type <тип_объекта {p_object}>')
        '''Переопределение метода append() списка. В случае, если p_object - Archer, элемент добавляется в список, иначе выбрасывается исключение TypeError с текстом:  Invalid type <тип_объекта p_object>'''

    def print_count(self):
        print(len([i for i in self if i.gender == 'm']))
        '''Вывести количество лучников мужского пола.'''
