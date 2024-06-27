class Character:
    def __init__(self, gender, age, height, weight):
        if not (gender in ['w','m']): raise ValueError('Invalid value')
        for i in [age, height, weight]:
            if  not isinstance(i, int) or i <= 0:
                raise ValueError('Invalid value')
        self.gender = gender
        self.age = age
        self.height = height
        self.weight = weight


class Warrior(Character):
    def __init__(self, gender, age, height, weight, forces, physical_damage, armor):
        super().__init__(gender, age, height, weight)
        for i in [forces, physical_damage, armor]:
            if  not isinstance(i, int) or i <= 0:
                raise ValueError('Invalid value')
        self.forces = forces
        self.physical_damage = physical_damage
        self.armor = armor

    def __str__(self):
        return f"Warrior: Пол {self.gender}, возраст {self.age}, рост {self.height}, вес {self.weight}, запас сил {self.forces}, физический урон {self.physical_damage}, броня {self.armor}."

    def __eq__(self, over):
        return self.physical_damage == over.physical_damage and self.forces == over.forces and self.armor == over.armor


class Magician(Character):
    def __init__(self, gender, age, height, weight, mana, magic_damage):
        super().__init__(gender, age, height, weight)
        for i in [mana, magic_damage]:
            if  not isinstance(i, int) or i <= 0:
                raise ValueError('Invalid value')
        self.mana = mana
        self.magic_damage = magic_damage

    def __str__(self):
        return f'Magician: Пол {self.gender}, возраст {self.age}, рост {self.height}, вес {self.weight}, запас маны {self.mana}, магический урон {self.magic_damage}.'

    def __damage__(self):
        return self.magic_damage * self.mana


class Archer(Character):
    def __init__(self, gender, age, height, weight, forces, physical_damage, attack_range):
        super().__init__(gender, age, height, weight)
        for i in [forces, physical_damage, attack_range]:
            if  not isinstance(i, int) or i <= 0:
                raise ValueError('Invalid value')
        self.forces = forces
        self.physical_damage = physical_damage
        self.attack_range = attack_range

    def __str__(self):
        return f'Archer: Пол {self.gender}, возраст {self.age}, рост {self.height}, вес {self.weight}, запас сил {self.forces}, физический урон {self.physical_damage}, дальность атаки {self.attack_range}.'

    def __eq__(self, over):
        return self.physical_damage == over.physical_damage  and self.forces == over.forces and self.attack_range == over.attack_range


class WarriorList(list):
    def __init__(self, name):
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
        self.name = name

    def extend(self, iterable):
        for i in iterable:
            if isinstance(i, Magician):
                self.append(i)

    def print_damage(self):
        damage = 0
        for i in self:
            damage += i.magic_damage
        print(damage)


class ArcherList(list):
    def __init__(self,name):
        self.name = name

    def append(self, p_object):
        if isinstance(p_object, Archer):
            super().append(p_object)
        else:
            raise TypeError(f"Invalid type {type(p_object)}")

    def print_count(self):
        cnt = 0
        for i in self:
            if i.gender == 'm':
                cnt += 1
        print(cnt)
