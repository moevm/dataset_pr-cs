class Character:
    def __init__(self, gender, age, height, weight):
        if all((gender in ['w', 'm'], isinstance(age, int), isinstance(height, int), isinstance(weight, int),
                age > 0 and height > 0, weight > 0)):
            self.gender = gender
            self.age = age
            self.height = height
            self.weight = weight
        else:
            raise ValueError('Invalid value')


class Warrior(Character):
    def __init__(self, gender, age, height, weight, forces, physical_damage, armor):
        super().__init__(gender, age, height, weight)
        if all((isinstance(forces, int) and isinstance(physical_damage, int), isinstance(armor, int), forces > 0,
                physical_damage > 0, armor > 0)):
            self.forces = forces
            self.physical_damage = physical_damage
            self.armor = armor
        else:
            raise ValueError('Invalid value')

    def __str__(self):
        return f"Warrior: Пол {self.gender}, возраст {self.age}, рост {self.height}, вес {self.weight}, запас сил {self.forces}, физический урон {self.physical_damage}, броня {self.armor}."

    def __eq__(self, other):
        return self.forces == other.forces and self.physical_damage == other.physical_damage and self.armor == other.armor

class Magician(Character):
    def __init__(self, gender, age, height, weight, mana, magic_damage):
        super().__init__(gender, age, height, weight)
        if all((isinstance(magic_damage, int) and isinstance(mana, int), mana > 0, magic_damage > 0)):
            self.mana = mana
            self.magic_damage = magic_damage
        else:
            raise ValueError('Invalid value')

    def __str__(self):
        return f"Magician: Пол {self.gender}, возраст {self.age}, рост {self.height}, вес {self.weight}, запас маны {self.mana}, магический урон {self.magic_damage}."

    def __damage__(self):
        return self.magic_damage * self.mana


class Archer(Character):
    def __init__(self, gender, age, height, weight, forces, physical_damage, attack_range):
        super().__init__(gender, age, height, weight)
        if all((isinstance(physical_damage, int), isinstance(forces, int), isinstance(attack_range, int), forces > 0,
                physical_damage > 0, attack_range > 0)):
            self.forces = forces
            self.physical_damage = physical_damage
            self.attack_range = attack_range
        else:
            raise ValueError('Invalid value')

    def __str__(self):
        return f"Archer: Пол {self.gender}, возраст {self.age}, рост {self.height}, вес {self.weight}, запас сил {self.forces}, физический урон {self.physical_damage}, дальность атаки {self.attack_range}."

    def __eq__(self, other):
        return self.forces == other.forces and self.physical_damage == other.physical_damage and self.attack_range == other.attack_range


class WarriorList(list):
    def __init__(self, name):
        super().__init__()
        self.name = name

    def append(self, p_object):
        if isinstance(p_object, Warrior):
            super().append(p_object)
        else:
            raise TypeError(f'Invalid type {type(p_object)}')

    def print_count(self):
        print(len(list(filter(lambda x: isinstance(x, Warrior), self))))


class MagicianList(list):

    def __init__(self, name):
        super().__init__()
        self.name = name

    def extend(self, iterable):
        if isinstance(iterable, list):
            for item in iterable:
                if isinstance(item, Magician):
                    super().append(item)
        else:
             raise TypeError(f'Invalid type {type(iterable)}')

    def print_damage(self):
        print(sum(list(map(lambda x: x.magic_damage, self))))


class ArcherList(list):

    def __init__(self, name):
        super().__init__()
        self.name = name

    def append(self, p_object):
        if isinstance(p_object, Archer):
            super().append(p_object)
        else:
            raise TypeError(f'Invalid type{type(p_object)}')

    def print_count(self):
        print(len(list(filter(lambda x: isinstance(x, Archer) and x.gender == 'm', self))))
