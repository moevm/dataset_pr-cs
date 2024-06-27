class Character:
    def __init__(self, gender, age, height, weight):
        if not (isinstance(gender, str) and (gender == 'w' or gender == 'm') and isinstance(age, int) and age > 0 and
                isinstance(height, int) and height > 0 and isinstance(weight, int) and weight > 0):
            raise ValueError('Invalid value')
        self.gender = gender
        self.age = age
        self.height = height
        self.weight = weight


class Warrior(Character):  # Наследуется от класса Character
    def __init__(self, gender, age, height, weight, forces, physical_damage, armor):
        super().__init__(gender, age, height, weight)
        if not (isinstance(forces, int) and forces > 0 and isinstance(physical_damage, int) and physical_damage > 0 and isinstance(armor, int) and armor > 0):
            raise ValueError('Invalid value')
        self.forces = forces
        self.physical_damage = physical_damage
        self.armor = armor

    def __str__(self):
        return (f'Warrior: Пол {self.gender}, возраст {self.age}, рост {self.height}, вес {self.weight}, запас сил {self.forces}, физический урон {self.physical_damage}, броня {self.armor}.')

    def __eq__(self, obj):
        return self.forces == obj.forces and self.physical_damage == obj.physical_damage and self.armor == obj.armor


class Magician(Character):  # Наследуется от класса Character
    def __init__(self, gender, age, height, weight, mana, magic_damage):
        super().__init__(gender, age, height, weight)
        if not (isinstance(mana, int) and mana > 0 and isinstance(magic_damage, int) and magic_damage > 0):
            raise ValueError('Invalid value')
        self.mana = mana
        self.magic_damage = magic_damage

    def __str__(self):
        return (f'Magician: Пол {self.gender}, возраст {self.age}, рост {self.height}, вес {self.weight}, запас маны {self.mana}, магический урон {self.magic_damage}.')

    def __damage__(self):
        return self.magic_damage * self.mana


class Archer(Character):  # Наследуется от класса Character
    def __init__(self, gender, age, height, weight, forces, physical_damage, attack_range):
        super().__init__(gender, age, height, weight)
        if not (isinstance(forces, int) and forces > 0 and isinstance(physical_damage, int) and physical_damage > 0 and isinstance(attack_range, int) and attack_range > 0):
            raise ValueError('Invalid value')
        self.forces = forces
        self.physical_damage = physical_damage
        self.attack_range = attack_range

    def __str__(self):
        return (f'Archer: Пол {self.gender}, возраст {self.age}, рост {self.height}, вес {self.weight}, запас сил {self.forces}, физический урон {self.physical_damage}, дальность атаки {self.attack_range}.')

    def __eq__(self, obj):
        return self.forces == obj.forces and self.physical_damage == obj.physical_damage and self.attack_range == obj.attack_range


class WarriorList(list):
    def __init__(self, name):
        super().__init__()
        self.name = name

    def append(self, p_object):
        if isinstance(p_object, Warrior):
            super().append(p_object)
        else:
            raise TypeError(f'Invalid type <тип объекта {type(p_object)}>')

    def print_count(self):
        print(len(self))


class MagicianList(list):
    def __init__(self, name):
        super().__init__()
        self.name = name

    def extend(self, iterable):
        super().extend(mag for mag in iterable if isinstance(mag, Magician))

    def print_damage(self):
        print(sum(mag.magic_damage for mag in self))


class ArcherList(list):
    def __init__(self, name):
        super().__init__()
        self.name = name

    def append(self, p_object):
        if isinstance(p_object, Archer):
            super().append(p_object)
        else:
            raise TypeError(f'Invalid type <тип объекта {type(p_object)}>')

    def print_count(self):
        print(len([mag for mag in self if mag.gender == 'm']))