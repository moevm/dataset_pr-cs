class PositiveNumber:
    @staticmethod
    def check_number(number):
        if not (isinstance(number, int) and number > 0):
            raise ValueError('Invalid value')

    def __set_name__(self, owner, name):
        self.name = '_' + name

    def __get__(self, instance, owner):
        return getattr(instance, self.name)

    def __set__(self, instance, value):
        self.check_number(value)
        setattr(instance, self.name, value)


class StringValue:
    @staticmethod
    def check_string(string):
        if not (isinstance(string, str) and string in 'mw'):
            raise ValueError('Invalid value')

    def __set_name__(self, owner, name):
        self.name = '_' + name

    def __get__(self, instance, owner):
        return getattr(instance, self.name)

    def __set__(self, instance, value):
        self.check_string(value)
        setattr(instance, self.name, value)


class Character:
    gender = StringValue()
    age = PositiveNumber()
    height = PositiveNumber()
    weight = PositiveNumber()

    def __init__(self, gender, age, height, weight):
        self.gender = gender
        self.age = age
        self.height = height
        self.weight = weight


class Warrior(Character):
    forces = PositiveNumber()
    physical_damage = PositiveNumber()
    armor = PositiveNumber()

    def __init__(self, gender, age, height, weight, forces, physical_damage, armor):
        super().__init__(gender, age, height, weight)
        self.forces = forces
        self.physical_damage = physical_damage
        self.armor = armor

    def __str__(self):
        return (f'Warrior: Пол {self.gender}, возраст {self.age}, рост {self.height}, вес {self.weight}, запас сил '
                f'{self.forces}, физический урон {self.physical_damage}, броня {self.armor}.')

    def __eq__(self, other):
        return self.physical_damage == other.physical_damage and self.forces == other.forces and self.armor == other.armor


class Magician(Character):
    mana = PositiveNumber()
    magic_damage = PositiveNumber()

    def __init__(self, gender, age, height, weight, mana, magic_damage):
        super().__init__(gender, age, height, weight)
        self.mana = mana
        self.magic_damage = magic_damage

    def __str__(self):
        return (f'Magician: Пол {self.gender}, возраст {self.age}, рост {self.height}, вес {self.weight}, запас маны '
                f'{self.mana}, '
                f'магический урон {self.magic_damage}.')

    def __damage__(self):
        return self.magic_damage * self.mana


class Archer(Character):
    forces = PositiveNumber()
    physical_damage = PositiveNumber()
    attack_range = PositiveNumber()

    def __init__(self, gender, age, height, weight, forces, physical_damage, attack_range):
        super().__init__(gender, age, height, weight)
        self.forces = forces
        self.physical_damage = physical_damage
        self.attack_range = attack_range

    def __str__(self):
        return (
            f'Archer: Пол {self.gender}, возраст {self.age}, рост {self.height}, вес {self.weight}, запас сил {self.forces}, '
            f'физический урон {self.physical_damage}, дальность атаки {self.attack_range}.')

    def __eq__(self, other):
        return (self.physical_damage == other.physical_damage and self.forces == other.forces and self.attack_range
                == other.attack_range)


class WarriorList(list):
    def __init__(self, name):
        super().__init__(self)
        self.name = name

    def append(self, p_object):
        if isinstance(p_object, Warrior):
            super().append(p_object)
        else:
            raise TypeError(f'Invalid type {type(p_object)}')

    def print_count(self):
        print(len(self))


class MagicianList(list):
    def __init__(self, name):
        super().__init__(self)
        self.name = name

    def extend(self, iterable):
        if all(isinstance(i, Magician) for i in iterable):
            super().extend(iterable)

    def print_damage(self):
        damage = 0
        for i in range(len(self)):
            damage += self[i].magic_damage
        print(damage)


class ArcherList(list):
    def __init__(self, name):
        super().__init__(self)
        self.name = name

    def append(self, p_object):
        if isinstance(p_object, Archer):
            super().append(p_object)
        else:
            raise TypeError(f'Invalid type {type(p_object)}')

    def print_count(self):
        count = 0
        for i in range(len(self)):
            if (self[i].gender == 'm'):
                count += 1
        print(count)
