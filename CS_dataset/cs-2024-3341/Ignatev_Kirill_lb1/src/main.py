class Character:
    def __init__(self, gender, age, height, weight):
        if (gender not in ('m', 'w')) or (not isinstance(age, int)) or (not isinstance(height, int)) or (not isinstance(weight, int)) or (age <= 0) or (height <= 0) or (weight <= 0):
            raise ValueError("Invalid value")
        self.gender = gender
        self.age = age
        self.height = height
        self.weight = weight

class Warrior(Character):
    def __init__(self, gender, age, height, weight, forces, physical_damage, armor):
        super().__init__(gender, age, height, weight)
        if (not isinstance(forces, int)) or (not isinstance(physical_damage, int)) or (not isinstance(armor, int)) or (forces <= 0) or (physical_damage <= 0) or (armor <= 0):
            raise ValueError('Invalid value')
        self.forces = forces
        self.physical_damage = physical_damage
        self.armor = armor

    def __str__(self):
        return f'Warrior: Пол {self.gender}, возраст {self.age}, рост {self.height}, вес {self.weight}, запас сил {self.forces}, физический урон {self.physical_damage}, броня {self.armor}.'

    def __eq__(self, other):
        return (int(self.forces) == int(other.forces)) and (int(self.physical_damage) == int(other.physical_damage)) and (int(self.armor) == int(other.armor))

class Magician(Character):
    def __init__(self, gender, age, height, weight, mana, magic_damage):
        super().__init__(gender, age, height, weight)
        if (not isinstance(mana, int)) or (not isinstance(magic_damage, int)) or (mana <= 0) or (magic_damage <= 0):
            raise ValueError("Invalid value")
        self.mana = mana
        self.magic_damage = magic_damage

    def __str__(self):
        return f'Magician: Пол {self.gender}, возраст {self.age}, рост {self.height}, вес {self.weight}, запас маны {self.mana}, магический урон {self.magic_damage}.'

    def __damage__(self):
        return int(self.mana) * int(self.magic_damage)

class Archer(Character):
    def __init__(self, gender, age, height, weight, forces, physical_damage, attack_range):
        super().__init__(gender, age, height, weight)
        if (not isinstance(forces, int)) or (not isinstance(physical_damage, int)) or (not isinstance(attack_range, int)) or (forces <= 0) or (physical_damage <= 0) or (attack_range <= 0):
            raise ValueError("Invalid value")
        self.forces = forces
        self.physical_damage = physical_damage
        self.attack_range = attack_range

    def __str__(self):
        return f'Archer: Пол {self.gender}, возраст {self.age}, рост {self.height}, вес {self.weight}, запас сил {self.forces}, физический урон {self.physical_damage}, дальность атаки {self.attack_range}.'

    def __eq__(self, other):
        return (int(self.forces) == int(other.forces)) and (int(self.physical_damage) == int(other.physical_damage)) and (int(self.attack_range) == int(other.attack_range))

class WarriorList(list):
    def __init__(self, name):
        super().__init__()
        self.name = name

    def append(self, p_object):
        if isinstance(p_object, Warrior):
            super().append(p_object)
        else:
            raise TypeError("Invalid type {}".format(type(p_object)))

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
        team_damage = 0
        for i in self:
            team_damage += int(i.magic_damage)
        print(team_damage)

class ArcherList(list):
    def __init__(self, name):
        super().__init__()
        self.name = name

    def append(self, p_object):
        if isinstance(p_object, Archer):
            super().append(p_object)
        else:
            raise TypeError("Invalid type {}".format(type(p_object)))

    def print_count(self):
        num = 0
        for x in self:
            if x.gender == 'm':
                num +=1
        print(num)
