class Character:
    def __init__(self, gender, age, height, weight):
        if (gender == 'm' or gender == 'w') and isinstance(age, int) and age > 0 and isinstance(age, int) and height > 0 and isinstance(age, int) and weight > 0:
            self.gender = gender
            self.age = age
            self.height = height
            self.weight = weight
        else:
            raise ValueError('Invalid value')


class Warrior(Character):
    def __init__(self, gender, age, height, weight, forces, physical_damage, armor):
        super().__init__(gender, age, height, weight)
        if isinstance(forces, int) and isinstance(physical_damage, int) and isinstance(armor,int) and forces > 0 and physical_damage > 0 and armor > 0:
            self.forces = forces
            self.physical_damage = physical_damage
            self.armor = armor
        else:
            raise ValueError('Invalid value')

    def __str__(self):
        return f'Warrior: Пол {self.gender}, возраст {self.age}, рост {self.height}, вес {self.weight}, запас сил {self.forces}, физический урон {self.physical_damage}, броня {self.armor}.'

    def __eq__(self, object):
        return self.armor == object.armor and self.forces == object.forces and self.physical_damage == object.physical_damage


class Magician(Character):
    def __init__(self, gender, age, height, weight, mana, magic_damage):
        super().__init__(gender, age, height, weight)
        if isinstance(mana, int) and isinstance(magic_damage, int) and mana > 0 and magic_damage > 0:
            self.mana = mana
            self.magic_damage = magic_damage
        else:
            raise ValueError('Invalid value')

    def __str__(self):
        return f'Magician: Пол {self.gender}, возраст {self.age}, рост {self.height}, вес {self.weight}, запас маны {self.mana}, магический урон {self.magic_damage}.'

    def __damage__(self):
        return self.mana * self.magic_damage


class Archer(Character):
    def __init__(self, gender, age, height, weight, forces, physical_damage, attack_range):
        super().__init__(gender, age, height, weight)
        if isinstance(forces, int) and isinstance(physical_damage, int) and isinstance(attack_range, int) and forces > 0 and physical_damage > 0 and attack_range > 0:
            self.forces = forces
            self.physical_damage = physical_damage
            self.attack_range = attack_range
        else:
            raise ValueError('Invalid value')

    def __str__(self):
        return f'Archer: Пол {self.gender}, возраст {self.age}, рост {self.height}, вес {self.weight}, запас сил {self.forces}, физический урон {self.physical_damage}, дальность атаки {self.attack_range}.'

    def __eq__(self, object):
        return self.attack_range == object.attack_range and self.forces == object.forces and self.physical_damage == object.physical_damage


class WarriorList(list):
    def __init__(self, name):
        super().__init__(self)
        self.name = name

    def append(self, p_object):
        if (isinstance(p_object, Warrior)):
            super().append(p_object)
        else:
            raise TypeError(f'Invalid type {type(p_object)}')

    def print_count(self):
        print(len(self))


class MagicianList(list):
    def __init__(self, name):
        super().__init__(self)
        self.name = name

    def extend(self, iterable):
        for item in iterable:
            if (isinstance(item, Magician)):
                super().append(item)
            

    def print_damage(self):
        count = 0
        for item in self: count += item.magic_damage
        print(count)


class ArcherList(list):
    def __init__(self, name):
        super().__init__(self)
        self.name = name

    def append(self, p_object):
        if (isinstance(p_object, Archer)):
            super().append(p_object)
        else:
            raise TypeError(f'Invalid type {type(p_object)}')

    def print_count(self):
        count = 0
        for item in self:
            if item.gender == 'm':
                count += 1
        print(count)
