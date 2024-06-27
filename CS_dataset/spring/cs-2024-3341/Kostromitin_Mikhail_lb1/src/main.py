class Character:
    try:
        def __init__(self, gender, age, height, weight):
            if gender not in ['m', 'w'] or not (type(age) == int and age > 0) or not (
                    type(height) == int and height > 0) or not (type(weight) == int and weight > 0):
                raise ValueError
            self.gender = gender
            self.age = age
            self.height = height
            self.weight = weight
    except ValueError:
        print("Invalid value")


class Warrior(Character):
    try:
        def __init__(self, gender, age, height, weight, forces, physical_damage, armor):
            super().__init__(gender, age, height, weight)
            if not (type(forces) == int and forces > 0) or not (
                    type(physical_damage) == int and physical_damage > 0) or not (type(armor) == int and armor > 0):
                raise ValueError
            self.forces = forces
            self.physical_damage = physical_damage
            self.armor = armor
    except ValueError:
        print("Invalid value")

    def __str__(self):
        return f'Warrior: Пол {self.gender}, возраст {self.age}, рост {self.height}, вес {self.weight}, запас сил {self.forces}, физический урон {self.physical_damage}, броня {self.armor}.'

    def __eq__(self, other):
        if self.physical_damage == other.physical_damage and self.forces == other.forces and self.armor == other.armor:
            return True
        return False


class Magician(Character):
    try:
        def __init__(self, gender, age, height, weight, mana, magic_damage):
            super().__init__(gender, age, height, weight)
            if not (type(mana) == int and mana > 0) or not (type(magic_damage) == int and magic_damage > 0):
                raise ValueError
            self.mana = mana
            self.magic_damage = magic_damage
    except ValueError:
        print("Invalid value")

    def __str__(self):
        return f'Magician: Пол {self.gender}, возраст {self.age}, рост {self.height}, вес {self.weight}, запас маны {self.mana}, магический урон {self.magic_damage}.'

    def __damage__(self):
        return self.mana * self.magic_damage


class Archer(Character):
    try:
        def __init__(self, gender, age, height, weight, forces, physical_damage, attack_range):
            super().__init__(gender, age, height, weight)
            if not (type(forces) == int and forces > 0) or not (
                    type(physical_damage) == int and physical_damage > 0) or not (
                    type(attack_range) == int and attack_range > 0):
                raise ValueError
            self.forces = forces
            self.physical_damage = physical_damage
            self.attack_range = attack_range
    except ValueError:
        print("Invalid values")

    def __str__(self):
        return f'Archer: Пол {self.gender}, возраст {self.age}, рост {self.height}, вес {self.weight}, запас сил {self.forces}, физический урон {self.physical_damage}, дальность атаки {self.attack_range}.'

    def __eq__(self, other):
        if self.forces == other.forces and self.physical_damage == other.physical_damage and self.attack_range == other.attack_range:
            return True
        return False


class WarriorList(list):
    def __init__(self, name):
        super().__init__()
        self.name = name

    try:
        def append(self, p_object):
            if type(p_object) == Warrior:
                self[len(self):] = [p_object]
            else:
                raise TypeError(type(p_object))
    except TypeError as Err:
        print(f'Invalid type {Err}')

    def print_count(self):
        print(len(self))


class MagicianList(list):
    def __init__(self, name):
        super().__init__()
        self.name = name

    def extend(self, iterable):
        for value in iterable:
            if type(value) == Magician:
                self[len(self):] = [value]

    def print_damage(self):
        result = 0
        for value in self:
            result += value.magic_damage
        print(result)


class ArcherList(list):
    def __init__(self, name):
        super().__init__()
        self.name = name

    try:
        def append(self, p_object):
            if type(p_object) == Archer:
                self[len(self):] = [p_object]
            else:
                raise TypeError(type(p_object))
    except TypeError as Err:
        print(f'Invalid type {Err}')

    def print_count(self):
        result = 0
        for archer in self:
            if archer.gender == 'm':
                result += 1
        print(result)