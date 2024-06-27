class Character:
    def __init__(self, gender, age, height, weight):
        if not (isinstance(height, int) and isinstance(weight, int) and isinstance(age, int) and
                age > 0 and height > 0 and weight > 0 and (gender == 'm' or gender == 'w')):
            raise ValueError("Invalid value")
        self.gender = gender
        self.age = age
        self.height = height
        self.weight = weight


class Warrior(Character):
    def __init__(self, gender, age, height, weight, forces, physical_damage, armor):
        super().__init__(gender, age, height, weight)
        if ((not isinstance(forces, int)) or (not isinstance(armor, int)) or (not isinstance(physical_damage, int))
                or forces <= 0 or physical_damage <= 0 or armor <= 0):
            raise ValueError("Invalid value")
        self.forces = forces
        self.physical_damage = physical_damage
        self.armor = armor

    def __str__(self):
        return (f'Warrior: Пол {self.gender}, возраст {self.age}, рост {self.height}, вес {self.weight},'
                f' запас сил {self.forces}, физический урон {self.physical_damage}, броня {self.armor}.')

    def __eq__(self, other):
        return True if (self.physical_damage == other.physical_damage and self.forces == other.forces and
                        self.armor == other.armor) else False


class Magician(Character):
    def __init__(self, gender, age, height, weight, mana, magic_damage):
        super().__init__(gender, age, height, weight)
        if (not isinstance(mana, int)) or (not isinstance(magic_damage, int)) or mana <= 0 or magic_damage <= 0:
            raise ValueError("Invalid value")
        self.mana = mana
        self.magic_damage = magic_damage

    def __str__(self):
        return (f'Magician: Пол {self.gender}, возраст {self.age}, рост {self.height}, вес {self.weight}, '
                f'запас маны {self.mana}, магический урон {self.magic_damage}.')

    def __damage__(self):
        return self.mana * self.magic_damage


class Archer(Character):
    def __init__(self, gender, age, height, weight, forces, physical_damage, attack_range):
        super().__init__(gender, age, height, weight)
        if (not isinstance(forces, int) or not isinstance(physical_damage, int) or not isinstance(attack_range, int)
                or forces <= 0 or physical_damage <= 0 or attack_range <= 0):
            raise ValueError("Invalid value")
        self.forces = forces
        self.physical_damage = physical_damage
        self.attack_range = attack_range

    def __str__(self):
        return (f'Archer: Пол {self.gender}, возраст {self.age}, рост {self.height}, вес {self.weight}, запас сил '
                f'{self.forces}, физический урон {self.physical_damage}, дальность атаки {self.attack_range}.')

    def __eq__(self, other):
        return True if (self.physical_damage == other.physical_damage and self.forces == other.forces
                        and self.attack_range == other.attack_range) else False


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
        print(len(self))


class MagicianList(list):
    def __init__(self, name):
        super().__init__()
        self.name = name

    def extend(self, iterable):
        for i in iterable:
            if isinstance(i, Magician):
                super().append(i)

    def print_damage(self):
        summarized_damage = 0
        for i in self:
            summarized_damage += i.magic_damage
        print(summarized_damage)


class ArcherList(list):
    def __init__(self, name):
        super().__init__()
        self.name = name

    def append(self, p_object):
        if isinstance(p_object, Archer):
            super().append(p_object)
        else:
            raise TypeError(f'Invalid type {type(p_object)}')

    def print_count(self):
        male_count = 0
        for i in self:
            if i.gender == 'm':
                male_count += 1
        print(male_count)
