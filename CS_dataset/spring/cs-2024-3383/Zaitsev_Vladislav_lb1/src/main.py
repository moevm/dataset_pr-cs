class Character:
    def __init__(self, gen, ag, heig, weigh):
        self.gender = gen
        self.age = ag
        self.height = heig
        self.weight = weigh
        if self.gender == 'm' or self.gender == 'w':
            pass
        else:
            raise ValueError("Invalid value")
        if isinstance(self.age, int) == True and isinstance(self.height, int) == True and isinstance(self.weight, int) == True:
            if self.age > 0 and self.height > 0 and self.weight > 0:
                pass
            else:
                raise ValueError("Invalid value")
        else:
            raise ValueError("Invalid value")
class Warrior(Character):
    def __init__(self, gen, ag, heig, weigh, force, damage, arm):
        super().__init__(gen, ag, heig, weigh)
        self.forces= force
        self.physical_damage = damage
        self.armor = arm
        if isinstance(self.forces, int) == True and isinstance(self.physical_damage, int) == True and isinstance(self.armor, int) == True:
            if self.armor > 0 and self.forces > 0 and self.physical_damage > 0:
                pass
            else:
                raise ValueError("Invalid value")
        else:
            raise ValueError("Invalid value")
    def __str__(self):
        return f"Warrior: Пол {self.gender}, возраст {self.age}, рост {self.height}, вес {self.weight}, запас сил {self.forces}, физический урон {self.physical_damage}, броня {self.armor}."
    def __eq__(self, obj2):
        if self.forces == obj2.forces and self.physical_damage == obj2.physical_damage and self.armor == obj2.armor:
            return True
        else:
            return False
class Magician(Character):
    def __init__(self, gen, ag, heig, weigh, man, damage):
        super().__init__(gen, ag, heig, weigh)
        self.mana = man
        self.magic_damage = damage
        if isinstance(self.mana, int) == True and isinstance(self.magic_damage, int) == True:
            if self.mana > 0 and self.magic_damage > 0:
                pass
            else:
                raise ValueError("Invalid value")
        else:
            raise ValueError("Invalid value")
    def __str__(self):
        return f"Magician: Пол {self.gender}, возраст {self.age}, рост {self.height}, вес {self.weight}, запас маны {self.mana}, магический урон {self.magic_damage}."
    def __damage__(self):
        return self.magic_damage * self.mana
class Archer(Character):
    def __init__(self, gen, ag, heig, weigh, force, damage, ran):
        super().__init__(gen, ag, heig, weigh)
        self.forces = force
        self.physical_damage = damage
        self.attack_range = ran
        if isinstance(self.forces, int) == True and isinstance(self.physical_damage, int) == True and isinstance(self.attack_range, int) == True:
            if self.attack_range > 0 and self.forces > 0 and self.physical_damage > 0:
                pass
            else:
                raise ValueError("Invalid value")
        else:
            raise ValueError("Invalid value")
    def __str__(self):
        return f"Archer: Пол {self.gender}, возраст {self.age}, рост {self.height}, вес {self.weight}, запас сил {self.forces}, физический урон {self.physical_damage}, дальность атаки {self.attack_range}."
    def __eq__(self, obj2):
        if self.forces == obj2.forces and self.physical_damage == obj2.physical_damage and self.attack_range == obj2.attack_range:
            return True
        else:
            return False
class WarriorList(list):
    def __init__(self, name):
        self.name = name
        super().__init__()
    def append(self, p_obj):
        if isinstance(p_obj, Warrior):
            super().append(p_obj)
        else:
            raise TypeError(f"Invalid type {p_obj.__class__.__name__}")
    def print_count(self):
        print(len(self))
class MagicianList(list):
    def __init__(self, name):
        self.name = name
        super().__init__()
    def extend(self, iterable):
        for i in range(0, len(iterable)):
            if isinstance(iterable[i], Magician):
                super().append(iterable[i])
            else:
                pass
    def print_damage(self):
        all_dmg = 0
        for i in range(0, len(self)):
            all_dmg += self[i].magic_damage
        print(all_dmg)
class ArcherList(list):
    def __init__(self, name):
        self.name = name
        super().__init__()
    def append(self, p_obj):
        if isinstance(p_obj, Archer):
            super().append(p_obj)
        else:
            raise TypeError(f"Invalid type {p_obj.__class__.__name__}")
    def print_count(self):
        count = 0
        for i in range(0,len(self)):
            if self[i].gender == "m":
                count += 1
        print(count)
