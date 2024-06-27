class Character:
    def __init__(self, gender, age, height, weight):
        if (gender != 'm' and gender != 'w') or (not (isinstance(age, int)) or age <= 0) or (
                not ((isinstance(height, int))) or height <= 0) or (not ((isinstance(weight, int))) or weight <= 0):
            raise ValueError('Invalid value')
        self.gender = gender
        self.age = age
        self.height = height
        self.weight = weight


class Warrior(Character):  # Наследуется от класса Character
    def __init__(self, gender, age, height, weight, forces, physical_damage, armor):
        if (not (isinstance(forces, int)) or forces <= 0) or (
                not (isinstance(physical_damage, int)) or physical_damage <= 0) or (
                not (isinstance(armor, int)) or armor <= 0):
            raise ValueError('Invalid value')
        super().__init__(gender, age, height, weight)
        self.forces = forces
        self.physical_damage = physical_damage
        self.armor = armor

    def __str__(self):
        s = f"Warrior: Пол {self.gender}, возраст {self.age}, рост {self.height}, вес {self.weight}, запас сил {self.forces}, физический урон {self.physical_damage}, броня {self.armor}."
        return s

    def __eq__(self, a):
        return self.forces == a.forces and self.physical_damage == a.physical_damage and self.armor == a.armor


class Magician(Character):  # Наследуется от класса Character
    def __init__(self, gender, age, height, weight, mana, magic_damage):
        if (not (isinstance(mana, int)) or mana <= 0) or (not (isinstance(magic_damage, int)) or magic_damage <= 0):
            raise ValueError('Invalid value')
        super().__init__(gender, age, height, weight)
        self.mana = mana
        self.magic_damage = magic_damage

    def __str__(self):
        return f"Magician: Пол {self.gender}, возраст {self.age}, рост {self.height}, вес {self.weight}, запас маны {self.mana}, магический урон {self.magic_damage}."

    def __damage__(self):
        return self.mana * self.magic_damage


class Archer(Character):  # Наследуется от класса Character
    def __init__(self, gender, age, height, weight, forces, physical_damage, attack_range):
        if (not (isinstance(forces, int)) or forces <= 0) or (
                not (isinstance(physical_damage, int)) or physical_damage <= 0) or (
                not (isinstance(attack_range, int)) or attack_range <= 0):
            raise ValueError('Invalid value')
        super().__init__(gender, age, height, weight)
        self.forces = forces
        self.physical_damage = physical_damage
        self.attack_range = attack_range

    def __str__(self):
        return f"Archer: Пол {self.gender}, возраст {self.age}, рост {self.height}, вес {self.weight}, запас сил {self.forces}, физический урон {self.physical_damage}, дальность атаки {self.attack_range}."

    def __eq__(self, a):
        return self.forces == a.forces and self.physical_damage == a.physical_damage and self.attack_range == a.attack_range


class WarriorList(list):
    def __init__(self, name):
        super().__init__()
        self.name = name

    def append(self, p_object):
        if not (isinstance(p_object, Warrior)):
            raise TypeError(f'Invalid type {type(p_object)}')
        else:
            super().append(p_object)

    def print_count(self):
        print(len(self))


class MagicianList(list):
    def __init__(self, name):
        super().__init__()
        self.name = name

    def extend(self, iterable):
        for i in iterable:
            if isinstance(i, Magician):
                super().append(i)
        #super().extend(item for item in iterable if isinstance(item, Magician))

    def print_damage(self):
        s = 0
        for i in self:
            s += i.magic_damage
        print(s)


class ArcherList(list):
    def __init__(self, name):
        super().__init__()
        self.name = name

    def append(self, p_object):
        if not (isinstance(p_object, Archer)):
            raise TypeError(f'Invalid type {type(p_object)}')
        else:
            super().append(p_object)

    def print_count(self):
        s = 0
        for i in self:
            if i.gender == 'm':
                s += 1
        print(s)
