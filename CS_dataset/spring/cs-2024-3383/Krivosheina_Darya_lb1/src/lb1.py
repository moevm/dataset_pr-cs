class Character:
    def __init__(self, gender, age, height, weight):
        if (gender == 'm' or gender == 'w') and isinstance(age, int) and age > 0 and isinstance(height, int) \
                and height > 0 and isinstance(weight, int) and weight > 0:
            self.gender = gender
            self.age = age
            self.height = height
            self.weight = weight
        else:
            raise ValueError('Invalid Value')


class Warrior(Character):
    def __init__(self, gender, age, height, weight, forces, physical_damage, armor):
        super().__init__(gender, age, height, weight)
        if isinstance(forces, int) and forces > 0 and isinstance(physical_damage, int) and physical_damage > 0 and \
                isinstance(armor, int) and armor > 0:
            self.forces = forces
            self.physical_damage = physical_damage
            self.armor = armor
        else:
            raise ValueError('Invalid Value')

    def __str__(self):
        return 'Warrior: Пол {}, возраст {}, рост {}, вес {}, запас сил {}, физический урон {}, броня {}.'.\
            format(self.gender, self.age, self.height, self.weight, self.forces, self.physical_damage, self.armor)

    def __eq__(self, other):
        if self.forces == other.forces and self.physical_damage == other.physical_damage and self.armor == other.armor:
            return True
        else:
            return False


class Magician(Character):
    def __init__(self, gender, age, height, weight, mana, magic_damage):
        super().__init__(gender, age, height, weight)
        if isinstance(mana, int) and mana > 0 and isinstance(magic_damage, int) and magic_damage > 0:
            self.mana = mana
            self.magic_damage = magic_damage
        else:
            raise ValueError('Invalid Value')

    def __str__(self):
        return 'Magician: Пол {}, возраст {}, рост {}, вес {}, запас маны {}, магический урон {}.'.\
            format(self.gender, self.age, self.height, self.weight, self.mana, self.magic_damage)

    def __damage__(self):
        return self.mana * self.magic_damage


class Archer(Character):
    def __init__(self, gender, age, height, weight, forces, physical_damage, attack_range):
        super().__init__(gender, age, height, weight)
        if isinstance(forces, int) and forces > 0 and isinstance(physical_damage, int) and physical_damage > 0 and \
            isinstance(attack_range, int) and attack_range > 0:
            self.forces = forces
            self.physical_damage = physical_damage
            self.attack_range = attack_range
        else:
            raise ValueError('Invalid Value')

    def __str__(self):
        return 'Archer: Пол {}, возраст {}, рост {}, вес {}, запас сил {}, физический урон {}, дальность атаки {}.'.\
            format(self.gender, self.age, self.height, self.weight, self.forces, self.physical_damage, self.attack_range)

    def __eq__(self, other):
        if self.forces == other.forces and self.physical_damage == other.physical_damage and \
                self.attack_range == other.attack_range:
            return True
        else:
            return False



class WarriorList(list):
    def __init__(self, name):
        super().__init__()
        self.name = name

    def append(self, p_object):
        if isinstance(p_object, Warrior):
            super().append(p_object)
        else:
            raise TypeError('Invalid Type {}'.format(type(p_object)))

    def print_count(self):
        print(len(self))


class MagicianList(list):
    def __init__(self, name):
        super().__init__()
        self.name = name

    def extend(self, iterable):
        iterable = list(filter(lambda a: isinstance(a, Magician), iterable))
        super().extend(iterable)

    def print_damage(self):
        full_damage = 0
        for i in self:
            full_damage += i.magic_damage
        print(full_damage)


class ArcherList(list):
    def __init__(self, name):
        super().__init__()
        self.name = name

    def append(self, p_object):
        if isinstance(p_object, Archer):
            super().append(p_object)
        else:
            raise TypeError('Invalid Type {}'.format(type(p_object)))

    def print_count(self):
        count = 0
        for t in self:
            if t.gender == 'm':
                count += 1
        print(count)

