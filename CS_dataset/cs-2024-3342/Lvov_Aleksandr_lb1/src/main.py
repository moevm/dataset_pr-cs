class Character:
    def __init__(self, gender, age, height, weight):
        if self.check_values(gender, age, height, weight):
            self.gender = gender
            self.age = age
            self.height = height
            self.weight = weight
        else:
            raise ValueError('Invalid value')

    def check_values(self, gender, age, height, weight):
        if not (isinstance(gender, str) and gender in 'mw'):
            return False
        if not (self.check_int_positive(age, height, weight)):
            return False
        return True

    def check_int_positive(self, *args):
        for num in args:
            if not (isinstance(num, int) and num > 0):
                return False
        return True


class Warrior(Character):
    def __init__(self, gender, age, height, weight, forces, physical_damage, armor):
        if self._check_values(gender, age, height, weight, forces, physical_damage, armor):
            self.gender = gender
            self.age = age
            self.height = height
            self.weight = weight
            self.forces = forces
            self.physical_damage = physical_damage
            self.armor = armor
        else:
            raise ValueError('Invalid value')

    def _check_values(self, gender, age, height, weight, forces, physical_damage, armor):
        return super().check_values(gender, age, height, weight) and super().check_int_positive(forces, physical_damage, armor)

    def __str__(self):
        return (f'Warrior: Пол {self.gender}, '
                f'возраст {self.age}, '
                f'рост {self.height}, '
                f'вес {self.weight}, '
                f'запас сил {self.forces}, '
                f'физический урон {self.physical_damage}, '
                f'броня {self.armor}.')

    def __eq__(self, other):
        return all([self.physical_damage == other.physical_damage, self.forces == other.forces, self.armor == other.armor])


class Magician(Character):
    def __init__(self, gender, age, height, weight, mana, magic_damage):
        if self._check_values(gender, age, height, weight, mana, magic_damage):
            self.gender = gender
            self.age = age
            self.height = height
            self.weight = weight
            self.mana = mana
            self.magic_damage = magic_damage
        else:
            raise ValueError('Invalid value')

    def _check_values(self, gender, age, height, weight, mana, magic_damage):
        return super().check_values(gender, age, height, weight) and super().check_int_positive(mana, magic_damage)

    def __str__(self):
        return (f'Magician: Пол {self.gender}, '
                f'возраст {self.age}, '
                f'рост {self.height}, '
                f'вес {self.weight}, '
                f'запас маны {self.mana}, '
                f'магический урон {self.magic_damage}.')

    def __damage__(self):
        return self.magic_damage * self.mana


class Archer(Character):  # Наследуется от класса Character
    def __init__(self, gender, age, height, weight, forces, physical_damage, attack_range):
        if self._check_values(gender, age, height, weight, forces, physical_damage, attack_range):
            self.gender = gender
            self.age = age
            self.height = height
            self.weight = weight
            self.forces = forces
            self.physical_damage = physical_damage
            self.attack_range = attack_range
        else:
            raise ValueError('Invalid value')

    def _check_values(self, gender, age, height, weight, forces, physical_damage, attack_range):
        return super().check_values(gender, age, height, weight) and super().check_int_positive(forces, physical_damage, attack_range)

    def __str__(self):
        return (f'Archer: Пол {self.gender}, '
                f'возраст {self.age}, '
                f'рост {self.height}, '
                f'вес {self.weight}, '
                f'запас сил {self.forces}, '
                f'физический урон {self.physical_damage}, '
                f'дальность атаки {self.attack_range}.')

    def __eq__(self, other):
        return all([self.physical_damage == other.physical_damage, self.forces == other.forces, self.attack_range == other.attack_range])


class WarriorList(list):
    def __init__(self, name):
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
    def __init__(self, name):
        super().__init__()
        self.name = name
    
    def extend(self, __iterable):
        for elem in __iterable:
            if isinstance(elem, Magician):
                super().append(elem)
                
    def print_damage(self):
        print(sum([i.magic_damage for i in self]))


class ArcherList(list):
    def __init__(self, name):
        super().__init__()
        self.name = name

    def append(self, __object):
        if isinstance(__object, Archer):
            super().append(__object)
        else:
            raise TypeError(f'Invalid type {type(__object)}')

    def print_count(self):
        print(len([i for i in self if i.gender == 'm']))


