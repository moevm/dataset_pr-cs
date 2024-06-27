class Character:
    def __init__(self, gender, age, height, weight):
        if (gender in ['m', 'w'] and all(isinstance(parameter, int) for parameter in [age, height, weight])
                and all(parameter > 0 for parameter in [age, height, weight])):
            self.gender = gender
            self.age = age
            self.height = height
            self.weight = weight
        else:
            raise ValueError('Invalid value')


class Warrior(Character):
    def __init__(self, gender, age, height, weight, forces, physical_damage, armor):
        if (all(isinstance(parameter, int) for parameter in [forces, physical_damage, armor])
                and all(parameter > 0 for parameter in [forces, physical_damage, armor])):
            super().__init__(gender, age, height, weight)
            self.forces = forces
            self.physical_damage = physical_damage
            self.armor = armor
        else:
            raise ValueError('Invalid value')

    def __str__(self):
        return f'Warrior: Пол {self.gender}, возраст {self.age}, рост {self.height}, вес {self.weight}, запас сил {self.forces}, физический урон {self.physical_damage}, броня {self.armor}.'

    def __eq__(self, other):
        if isinstance(other, Warrior):
            return self.physical_damage == other.physical_damage \
                and self.forces == other.forces \
                and self.armor == other.armor
        else:
            return False


class Magician(Character):
    def __init__(self, gender, age, height, weight, mana, magic_damage):
        if (all(isinstance(parameter, int) for parameter in [mana, magic_damage])
                and all(parameter > 0 for parameter in [mana, magic_damage])):
            super().__init__(gender, age, height, weight)
            self.mana = mana
            self.magic_damage = magic_damage
        else:
            raise ValueError('Invalid value')

    def __str__(self):
        return f'Magician: Пол {self.gender}, возраст {self.age}, рост {self.height}, вес {self.weight}, запас маны {self.mana}, магический урон {self.magic_damage}.'

    def __damage__(self):
        return self.magic_damage * self.mana


class Archer(Character):
    def __init__(self, gender, age, height, weight, forces, physical_damage, attack_range):
        if (all(isinstance(parameter, int) for parameter in [forces, physical_damage, attack_range])
                and all(parameter > 0 for parameter in [forces, physical_damage, attack_range])):
            super().__init__(gender, age, height, weight)
            self.forces = forces
            self.physical_damage = physical_damage
            self.attack_range = attack_range
        else:
            raise ValueError('Invalid value')

    def __str__(self):
        return f'Archer: Пол {self.gender}, возраст {self.age}, рост {self.height}, вес {self.weight}, запас сил {self.forces}, физический урон {self.physical_damage}, дальность атаки {self.attack_range}.'

    def __eq__(self, other):
        if isinstance(other, Archer):
            return self.physical_damage == other.physical_damage \
                and self.forces == other.forces \
                and self.attack_range == other.attack_range
        else:
            return False


class WarriorList(list):
    def __init__(self, name):
        super().__init__(self)
        self.name = str(name)

    def append(self, war):
        if isinstance(war, Warrior):
            self += [war]
        else:
            raise TypeError(f'Invalid type {type(war)}')


    def print_count(self):
        print(self.__len__())


class MagicianList(list):
    def __init__(self, name):
        super().__init__(self)
        self.name = str(name)

    def extend(self, mags):
        temp = []
        for mag in mags:
            if isinstance(mag, Magician):
                temp.append(mag)
        super().extend(temp)

    def print_damage(self):
        print(sum([mag.magic_damage for mag in self]))


class ArcherList(list):
    def __init__(self, name):
        super().__init__(self)
        self.name = str(name)

    def append(self, arch):
        if isinstance(arch, Archer):
            self += [arch]
        else:
            raise TypeError(f'Invalid type {type(arch)}')

    def print_count(self):
        print(len([arch for arch in self if arch.gender == 'm']))
