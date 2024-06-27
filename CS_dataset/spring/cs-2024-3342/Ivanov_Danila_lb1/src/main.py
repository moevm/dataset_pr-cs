class Character:
    def __init__(self, gender, age, height, weight):
        if gender in 'mw' and age > 0 and height > 0 and weight > 0 and isinstance(age, int) and isinstance(height, int) and isinstance(weight, int):
            self.gender = gender
            self.age = age
            self.height = height
            self.weight = weight
        else:
            raise ValueError("Invalid value")


class Warrior(Character):  # Наследуется от класса Character
    def __init__(self, gender, age, height, weight, forces, physical_damage, armor):
        super().__init__(gender, age, height, weight)
        if forces > 0 and physical_damage > 0 and armor > 0 and isinstance(forces, int) and isinstance(physical_damage, int) and isinstance(armor, int):
            self.forces = forces
            self.physical_damage = physical_damage
            self.armor = armor
        else:
            raise ValueError("Invalid value")

    def __str__(self):
        return f"Warrior: Пол {self.gender}, возраст {self.age}, рост {self.height}, вес {self.weight}, запас сил {self.forces}, физический урон {self.physical_damage}, броня {self.armor}."

    def __eq__(self, other):
        return self.forces == other.forces and self.physical_damage == other.physical_damage and self.armor == other.armor


class Magician(Character):  # Наследуется от класса Character
    def __init__(self, gender, age, height, weight, mana, magic_damage):
        super().__init__(gender, age, height, weight)
        if mana > 0 and magic_damage > 0 and isinstance(mana, int) and isinstance(magic_damage, int):
            self.mana = mana
            self.magic_damage = magic_damage
        else:
            raise ValueError("Invalid value")

    def __str__(self):
        return f"Magician: Пол {self.gender}, возраст {self.age}, рост {self.height}, вес {self.weight}, запас маны {self.mana}, магический урон {self.magic_damage}."

    def __damage__(self):
        return self.magic_damage * self.mana


class Archer(Character):  # Наследуется от класса Character
    def __init__(self, gender, age, height, weight, forces, physical_damage, attack_range):
        super().__init__(gender, age, height, weight)
        if forces > 0 and physical_damage > 0 and attack_range > 0 and isinstance(forces, int) and isinstance(
                physical_damage, int) and isinstance(attack_range, int):
            self.forces = forces
            self.physical_damage = physical_damage
            self.attack_range = attack_range
        else:
            raise ValueError("Invalid value")

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
            raise TypeError(f'Invalid type {p_object.__class__.__name__}')

    def print_count(self):
        print(len(self))


class MagicianList(list):
    def __init__(self, name):
        super().__init__()
        self.name = name

    def extend(self, p_object):
        for i in p_object:
            if isinstance(i, Magician):
                super().append(i)

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
        if isinstance(p_object, Archer):
            super().append(p_object)
        else:
            raise TypeError(f'Invalid type {p_object.__class__.__name__}')

    def print_count(self):
        s = 0
        for i in self:
            if i.gender == 'm':
                s += 1
        print(s)
