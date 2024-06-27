class Character:
    def __init__(self, gender, age, height, weight):
        if gender not in ['m', 'w'] or type(age) is not int or age <= 0 or type(
                height) is not int or height <= 0 or type(weight) is not int or weight <= 0:
            raise ValueError('Invalid value')
        else:
            self.gender = gender
            self.age = age
            self.height = height
            self.weight = weight


class Warrior(Character):

    def __init__(self, gender, age, height, weight, forces, physical_damage, armor):
        super().__init__(gender, age, height, weight)
        if type(forces) is not int or forces <= 0 or type(
                physical_damage) is not int or physical_damage <= 0 or type(armor) is not int or armor <= 0:
            raise ValueError('Invalid value')
        else:
            self.forces = forces
            self.physical_damage = physical_damage
            self.armor = armor

    def __str__(self):
        return f"Warrior: Пол {self.gender}, возраст {self.age}, рост {self.height}, вес {self.weight}, запас сил {self.forces}, физический урон {self.physical_damage}, броня {self.armor}."

    def __eq__(self, other):
        return self.forces == other.forces and self.physical_damage == other.physical_damage and self.armor == other.armor


class Magician(Character):
    def __init__(self, gender, age, height, weight, mana, magic_damage):
        super().__init__(gender, age, height, weight)
        if type(mana) is not int or mana <= 0 or type(magic_damage) is not int or magic_damage <= 0:
            raise ValueError('Invalid value')
        else:
            self.mana = mana
            self.magic_damage = magic_damage

    def __str__(self):
        return f"Magician: Пол {self.gender}, возраст {self.age}, рост {self.height}, вес {self.weight}, запас маны {self.mana}, магический урон {self.magic_damage}."

    def __damage__(self):
        return self.magic_damage * self.mana


class Archer(Character):
    def __init__(self, gender, age, height, weight, forces, physical_damage, attack_range):
        super().__init__(gender, age, height, weight)

        if type(forces) is not int or forces <= 0 or type(
                physical_damage) is not int or physical_damage <= 0 or type(attack_range) is not int or attack_range <= 0:
            raise ValueError('Invalid value')
        else:
            self.forces = forces
            self.physical_damage = physical_damage
            self.attack_range = attack_range

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
            raise TypeError(f"Invalid type {type(p_object)}")

    def print_count(self):
        count = 0
        for i in self:
            count += 1
        print(count)


class MagicianList(list):

    def __init__(self, name):
        super().__init__()
        self.name = name

    def extend(self, iterable):
        for item in iterable:
            if isinstance(item, Magician):
                super().append(item)


    def print_damage(self):
        damage = 0
        for item in self:
            damage += item.magic_damage
        print(damage)


class ArcherList(list):

    def __init__(self, name):
        super().__init__()
        self.name = name

    def append(self, p_object):
        if isinstance(p_object, Archer):
            super().append(p_object)
        else:
            raise TypeError(f"Invalid type {type(p_object)}")

    def print_count(self):
        count = 0
        for i in self:
            if i.gender == 'm':
                count += 1
        print(count)
