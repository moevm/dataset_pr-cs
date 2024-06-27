class Character:
    def __init__(self, gender, age, height, weight):
        if not(gender == 'm' or gender == 'w') or not all(isinstance(x, int) and x > 0 for x in [age, height, weight]):
            raise ValueError('Invalid value')
        self.gender = gender
        self.age = age
        self.height = height
        self.weight = weight

class Warrior(Character):
    def __init__(self, gender, age, height, weight, forces, physical_damage, armor):
        super().__init__(gender, age, height, weight)
        if not all(isinstance(x, int) and x > 0 for x in [forces, physical_damage]) or not (armor > 0 and isinstance(armor, (int, float))):
            raise ValueError('Invalid value')
        self.forces = forces
        self.physical_damage = physical_damage
        self.armor = armor

    def __str__(self):
        return (f'Warrior: Пол {self.gender}, возраст {self.age}, рост {self.height}, вес {self.weight}, '
                f'запас сил {self.forces}, физический урон {self.physical_damage}, броня {self.armor}.')

    def __eq__(self, another_warrior):
        if not isinstance(another_warrior, Warrior):
            return False
        return (super().__eq__(another_warrior) and
                self.forces == another_warrior.forces and
                self.physical_damage == another_warrior.physical_damage and
                self.armor == another_warrior.armor)

class Magician(Character):
    def __init__(self, gender, age, height, weight, mana, magic_damage):
        super().__init__(gender, age, height, weight)
        if not all(isinstance(x, int) and x > 0 for x in [mana, magic_damage]):
            raise ValueError('Invalid value')
        self.mana = mana
        self.magic_damage = magic_damage

    def __str__(self):
        return (f'Magician: Пол {self.gender}, возраст {self.age}, рост {self.height}, вес {self.weight}, '
                f'запас маны {self.mana}, магический урон {self.magic_damage}.')

    def __eq__(self, another_magician):
        if not isinstance(another_magician, Magician):
            return False
        return (super().__eq__(another_magician) and
                self.mana == another_magician.mana and
                self.magic_damage == another_magician.magic_damage)

    def __damage__(self):
        return self.mana * self.magic_damage

class Archer(Character):
    def __init__(self, gender, age, height, weight, forces, physical_damage, attack_range):
        super().__init__(gender, age, height, weight)
        if not all(isinstance(x, int) and x > 0 for x in [forces, physical_damage, attack_range]):
            raise ValueError('Invalid value')
        self.forces = forces
        self.physical_damage = physical_damage
        self.attack_range = attack_range

    def __str__(self):
        return (f'Archer: Пол {self.gender}, возраст {self.age}, рост {self.height}, вес {self.weight}, '
                f'запас сил {self.forces}, физический урон {self.physical_damage}, дальность атаки {self.attack_range}.')

    def __eq__(self, another_archer):
        if not isinstance(another_archer, Archer):
            return False
        return (super().__eq__(another_archer) and
                self.forces == another_archer.forces and
                self.physical_damage == another_archer.physical_damage and
                self.attack_range == another_archer.attack_range)

class WarriorList(list):
    def __init__(self, name):
        super().__init__()
        self.name = name

    def append(self, p_object):
        if isinstance(p_object, Warrior):
            super().append(p_object)
        else:
            raise TypeError(type(p_object))

    def print_count(self):
        print(len(self))

class MagicianList(list):
    def __init__(self, name):
        super().__init__()
        self.name = name

    def extend(self, iterable):
        for i in range(len(iterable)):
            if isinstance(iterable[i], Magician):
                super().append(iterable[i])

    def print_damage(self):
        print(sum(self[x].magic_damage for x in range(len(self))))

class ArcherList(list):
    def __init__(self, name):
        super().__init__()
        self.name = name

    def append(self, p_object):
        if isinstance(p_object, Archer):
            super().append(p_object)
        else:
            raise TypeError(type(p_object))

    def print_count(self):
        print(len(self))