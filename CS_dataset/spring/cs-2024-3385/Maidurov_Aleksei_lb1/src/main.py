class Character:

    def __init__(self, gender, age, height, weight):
        if not (gender == 'w' or gender == 'm'):
            raise ValueError("Invalid value")
        if not all(map(lambda x: isinstance(x, int) and x > 0, [age, height, weight])):
            raise ValueError("Invalid value")
        self.gender = gender
        self.age = age
        self.height = height
        self.weight = weight


class Warrior(Character):

    def __init__(self, gender, age, height, weight, forces, physical_damage, armor):
        super().__init__(gender, age, height, weight)
        if not all(map(lambda x: isinstance(x, int) and x > 0, [forces, physical_damage, armor])):
            raise ValueError("Invalid value")
        self.forces = forces
        self.physical_damage = physical_damage
        self.armor = armor

    def __str__(self):
        return f"Warrior: Пол {self.gender}, возраст {self.age}, рост {self.height}, вес {self.weight}, запас сил {self.forces}, физический урон {self.physical_damage}, броня {self.armor}."

    def __eq__(self, other):
        return all(
            [self.forces == other.forces, self.physical_damage == other.physical_damage, self.armor == other.armor])


class Magician(Character):

    def __init__(self, gender, age, height, weight, mana, magic_damage):
        super().__init__(gender, age, height, weight)
        if not all(map(lambda x: isinstance(x, int) and x > 0, [mana, magic_damage])):
            raise ValueError("Invalid value")
        self.mana = mana
        self.magic_damage = magic_damage

    def __str__(self):
        return f"Magician: Пол {self.gender}, возраст {self.age}, рост {self.height}, вес {self.weight}, запас маны {self.mana}, магический урон {self.magic_damage}."

    def __damage__(self):
        return self.mana * self.magic_damage


class Archer(Character):

    def __init__(self, gender, age, height, weight, forces, physical_damage, attack_range):
        super().__init__(gender, age, height, weight)
        if not all(map(lambda x: isinstance(x, int) and x > 0, [forces, physical_damage, attack_range])):
            raise ValueError("Invalid value")
        self.forces = forces
        self.physical_damage = physical_damage
        self.attack_range = attack_range

    def __str__(self):
        return f"Archer: Пол {self.gender}, возраст {self.age}, рост {self.height}, вес {self.weight}, запас сил {self.forces}, физический урон {self.physical_damage}, дальность атаки {self.attack_range}."

    def __eq__(self, other):
        return all([self.forces == other.forces, self.physical_damage == other.physical_damage,
                    self.attack_range == other.attack_range])


class WarriorList(list):

    def __init__(self, name):
        super().__init__()
        self.name = name

    def append(self, __object):
        if not isinstance(__object, Warrior):
            raise TypeError(f"Invalid type {type(__object)}")
        super().append(__object)

    def print_count(self):
        print(len(self))


class MagicianList(list):

    def __init__(self, name):
        super().__init__()
        self.name = name

    def extend(self, __iterable):
        __iterable = filter(lambda x: isinstance(x, Magician), __iterable)
        super().extend(__iterable)

    def print_damage(self):
        print(sum([item.magic_damage for item in self]))


class ArcherList(list):

    def __init__(self, name):
        super().__init__()
        self.name = name

    def append(self, __object):
        if not isinstance(__object, Archer):
            raise TypeError(f"Invalid type {type(__object)}")
        super().append(__object)

    def print_count(self):
        print(len([item for item in self if item.gender == 'm']))
