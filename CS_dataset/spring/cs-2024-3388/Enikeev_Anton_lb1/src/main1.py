class Character:
    '''Базовый класс - персонаж Character'''
    def __init__(self, gender: str, age: int, height: int, weight: int):
        is_validate_gender = lambda x: isinstance(x, str) and x in ['w', 'm']
        if not is_validate_gender(gender) or not self.is_positive_integer(age)\
            or not self.is_positive_integer(height)\
                or not self.is_positive_integer(weight): raise ValueError('Invalid value')
        self.gender = gender
        self.age = age
        self.height = height
        self.weight = weight

    def is_positive_integer(self, x):
        return isinstance(x, int) and x > 0

class Warrior(Character):
    '''Воин - Warrior'''
    def __init__(self, gender: str, age: int, height: int, weight: int,\
        forces: int, physical_damage: int, armor: int):
        super().__init__(gender, age, height, weight)
        if not self.is_positive_integer(forces)\
             or not self.is_positive_integer(physical_damage)\
                or not self.is_positive_integer(armor): raise ValueError('Invalid value')
        self.forces = forces
        self.physical_damage = physical_damage
        self.armor = armor

    def __str__(self):
        return f'Warrior: Пол {self.gender}, возраст {self.age}, рост {self.height}, вес {self.weight},'\
            f' запас сил {self.forces}, физический урон {self.physical_damage}, броня {self.armor}.'

    def __eq__(self, another):
        if isinstance(another, type(self)):
            return self.forces == another.forces and self.physical_damage == another.physical_damage\
                and self.armor == another.armor

class Magician(Character):
    '''Маг - Magician'''
    def __init__(self, gender: str, age: int, height: int, weight: int,\
        mana: int, magic_damage: int):
        super().__init__(gender, age, height, weight)
        if not super().is_positive_integer(mana)\
             or not super().is_positive_integer(magic_damage): raise ValueError('Invalid value')
        self.mana = mana
        self.magic_damage = magic_damage

    def __str__(self):
        return f'Magician: Пол {self.gender}, возраст {self.age}, рост {self.height}, вес {self.weight},'\
            f' запас маны {self.mana}, магический урон {self.magic_damage}.'

    def __damage__(self):
        return self.magic_damage * self.mana

class Archer(Character):
    '''Лучник - Archer'''
    def __init__(self, gender: str, age: int, height: int, weight: int,\
        forces: int, physical_damage: int, attack_range: int):
        super().__init__(gender, age, height, weight)
        if not super().is_positive_integer(forces)\
             or not super().is_positive_integer(physical_damage)\
                or not super().is_positive_integer(attack_range): raise ValueError('Invalid value')
        self.forces = forces
        self.physical_damage = physical_damage
        self.attack_range = attack_range

    def __str__(self):
        return f'Archer: Пол {self.gender}, возраст {self.age}, рост {self.height}, вес {self.weight},'\
            f' запас сил {self.forces}, физический урон {self.physical_damage}, дальность атаки {self.attack_range}.'

    def __eq__(self, another):
        if isinstance(another, type(self)):
            return self.physical_damage == another.physical_damage and self.forces == another.forces\
                and self.attack_range == another.attack_range
        return False

class WarriorList(list):
    '''class WarriorList – список воинов - наследуется от класса list'''
    def __init__(self, name: str):
        super().__init__()
        self.name = name

    def append(self, p_object):
        if isinstance(p_object, Warrior):
            super().append(p_object)
        else:
            raise TypeError(f'Invalid type {type(p_object)}')

    def print_count(self):
        print(len(self))

class MagicianList(list):
    '''class MagicianList – список магов - наследуется от класса list'''
    def __init__(self, name: str):
        super().__init__()
        self.name = name

    def extend(self, iterable):
        super().extend(item for item in iterable if isinstance(item, Magician))
    
    def print_damage(self):
        print(sum(x.magic_damage for x in self)) 

class ArcherList(list):
    '''class ArcherList – список лучников - наследуется от класса list.'''
    def __init__(self, name: str):
        super().__init__()
        self.name = name
    
    def append(self, p_object):
        if isinstance(p_object, Archer):
            super().append(p_object)
        else:
            raise TypeError(f'Invalid type {type(p_object)}')

    def print_count(self):
        print(len([x for x in self if x.gender == 'm']))
