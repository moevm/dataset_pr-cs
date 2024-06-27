class Character:
    def __init__(self, gender: str, age: int, height: int, weight: int):
        if not all((isinstance(gender, str), isinstance(age, int), isinstance(height, int), isinstance(weight, int)))or not all((gender in 'mw', age > 0, height > 0, weight > 0)):
            raise ValueError('Invalid value')
        self.gender = gender
        self.age = age
        self.height = height
        self.weight = weight


class Warrior(Character):
    def __init__(self, gender: str, age: int, height: int, weight: int, forces: int, physical_damage: int, armor: int):
        if not all((isinstance(physical_damage, int), isinstance(forces, int), isinstance(armor, int))) or not all((physical_damage > 0, forces > 0, armor > 0)):
            raise ValueError('Invalid value')
        super().__init__(gender, age, height, weight)
        self.forces = forces
        self.physical_damage = physical_damage
        self.armor = armor

    def __str__(self):
        return f'Warrior: Пол {self.gender}, возраст {self.age}, рост {self.height}, вес {self.weight}, запас сил {self.forces}, физический урон {self.physical_damage}, броня {self.armor}.'

    def __eq__(self, other):
        return (self.forces == other.forces) and (self.physical_damage == other.physical_damage) and (self.armor == other.armor)


class Magician(Character):
    def __init__(self, gender: str, age: int, height: int, weight: int, mana: int, magic_damage: int):
        if not all((isinstance(magic_damage, int), isinstance(mana, int))) or not all((magic_damage > 0, mana > 0)):
            raise ValueError('Invalid value')
        super().__init__(gender, age, height, weight)
        self.mana = mana
        self.magic_damage = magic_damage

    def __str__(self):
        return f'Magician: Пол {self.gender}, возраст {self.age}, рост {self.height}, вес {self.weight}, запас маны {self.mana}, магический урон {self.magic_damage}.'

    def __damage__(self):
        return self.mana * self.magic_damage


class Archer(Character):
    def __init__(self, gender:str, age:int, height:int, weight:int, forces:int, physical_damage:int, attack_range:int):
        if not all((isinstance(physical_damage, int), isinstance(forces, int), isinstance(attack_range, int))) or not all((physical_damage > 0, forces > 0, attack_range > 0)):
            raise ValueError('Invalid value')
        super().__init__(gender, age, height, weight)
        self.forces = forces
        self.physical_damage = physical_damage
        self.attack_range = attack_range

    def __str__(self):
        return f'Archer: Пол {self.gender}, возраст {self.age}, рост {self.height}, вес {self.weight}, запас сил {self.forces}, физический урон {self.physical_damage}, дальность атаки {self.attack_range}.'

    def __eq__(self, other):
        return (self.forces == other.forces) and (self.physical_damage == other.physical_damage) and (self.attack_range == other.attack_range)


class WarriorList(list):
    def __init__(self, name: str = '-'):
        super().__init__()
        self.name = name

    def append(self, __object):
        if isinstance(__object, Warrior):
            super().append(__object)
        else:
            raise TypeError(f'Invalid type {type(__object)}')

    def print_count(self):
        print(len(self))


class MagicianList(list):
    def __init__(self, name: str = '-'):
        super().__init__()
        self.name = name

    def extend(self, __iterable):
        super().extend(filter(lambda x: isinstance(x, Magician), __iterable))

    def print_damage(self):
        print(sum(map(lambda x: x.magic_damage, self)))


class ArcherList(list):
    def __init__(self, name: str = '-'):
        super().__init__()
        self.name = name

    def append(self, __object):
        if isinstance(__object, Archer):
            super().append(__object)
        else:
            raise TypeError(f'Invalid type {type(__object)}')

    def print_count(self):
        print(len(list(filter(lambda x: x.gender == 'm', self))))
