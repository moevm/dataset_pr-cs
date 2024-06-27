def check_int(num):
    if num > 0 and type(num) == int:
        return True
    return False


class Character:
    try:
        def __init__(self, gender, age, height, weight):
            if (gender == 'm' or gender == 'w') and check_int(age) and check_int(height) and check_int(weight):
                self.gender = gender
                self.age = age
                self.height = height
                self.weight = weight
            else:
                raise ValueError('Invalid value')

    except ValueError as e:
        print(e)


class Warrior(Character):
    try:
        def __init__(self, gender, age, height, weight, forces, physical_damage, armor):
            if (gender == 'm' or gender == 'w') and check_int(age) and check_int(height) and check_int(weight) \
                    and check_int(forces) and check_int(physical_damage) and check_int(armor):
                super().__init__(gender, age, height, weight)
                self.forces = forces
                self.physical_damage = physical_damage
                self.armor = armor
            else:
                raise ValueError('Invalid value')
    except ValueError as e:
        print(e)

    def __str__(self):
        return f"Warrior: Пол {self.gender}, возраст {self.age}, рост {self.height}, вес {self.weight}, запас сил {self.forces}, физический урон {self.physical_damage}, броня {self.armor}."

    def __eq__(self, second):
        if (self.forces == second.forces) and (self.physical_damage == second.physical_damage) and (
                self.armor == second.armor):
            return True
        return False


class Magician(Character):
    try:
        def __init__(self, gender, age, height, weight, mana, magic_damage):
            if (gender == 'm' or gender == 'w') and check_int(age) and check_int(height) and check_int(weight) \
                    and (check_int(mana)) and check_int(magic_damage):
                super().__init__(gender, age, height, weight)
                self.mana = mana
                self.magic_damage = magic_damage
            else:
                raise ValueError('Invalid value')
    except ValueError as e:
        print(e)

    def __str__(self):
        return f"Magician: Пол {self.gender}, возраст {self.age}, рост {self.height}, вес {self.weight}, запас маны {self.mana}, магический урон {self.magic_damage}."

    def __damage__(self):
        return self.mana * self.magic_damage


class Archer(Character):
    try:
        def __init__(self, gender, age, height, weight, forces, physical_damage, attack_range):
            if (gender == 'm' or gender == 'w') and check_int(age) and check_int(height) and check_int(weight) \
                    and (check_int(attack_range)) and check_int(physical_damage) and check_int(forces):
                super().__init__(gender, age, height, weight)
                self.forces = forces
                self.physical_damage = physical_damage
                self.attack_range = attack_range
            else:
                raise ValueError('Invalid value')
    except ValueError as e:
        print(e)

    def __str__(self):
        return f"Archer: Пол {self.gender}, возраст {self.age}, рост {self.height}, вес {self.weight}, запас сил {self.forces}, физический урон {self.physical_damage}, дальность атаки {self.attack_range}."

    def __eq__(self, second):
        if (self.forces == second.forces) and (self.physical_damage == second.physical_damage) and \
                (self.attack_range == second.attack_range):
            return True
        return False


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
        print(len(self))


class MagicianList(list):
    def __init__(self, name):
        super().__init__()
        self.name = name

    def extend(self, iterable):
        for el in iterable:
            if isinstance(el, Magician):
                super().append(el)

    def print_damage(self):
        damage = 0
        for el in self:
            damage += el.magic_damage
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
        total = 0
        for el in self:
            if el.gender == 'm':
                total += 1
        print(total)