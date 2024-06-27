class Character:
    def __init__(self, gender, age, height, weight):
        if (gender in 'mw' and all(x > 0 for x in [age, height, weight]) and all(isinstance(x, int) for x in [age, weight, height])):
            self.gender = gender
            self.age = age
            self.height = height
            self.weight = weight
        else:
            raise ValueError('Invalid value')

class Warrior(Character):
    def __init__(self, gender, age, height, weight, forces, physical_damage, armor):
        super().__init__(gender, age, height, weight)
        if (all(x>0 for x in [forces, physical_damage, armor]) and all(isinstance(x, int) for x in [forces, physical_damage, armor])):
            self.forces = forces
            self.physical_damage = physical_damage
            self.armor = armor
        else: 
            raise ValueError('Invalid value')

    def __str__(self):
        return f"Warrior: Пол {self.gender}, возраст {self.age}, рост {self.height}, вес {self.weight}, запас сил {self.forces}, физический урон {self.physical_damage}, броня {self.armor}."
    
    def __eq__(self, other):
        return all(getattr(self, field) == getattr(other, field) for field in ['physical_damage', 'forces', 'armor'])
    

class Magician(Character):
    def __init__(self, gender, age, height, weight, mana, magic_damage):
        super().__init__(gender, age, height, weight)
        if (all(x>0 for x in [mana, magic_damage])) and all(isinstance(x, int) for x in [mana, magic_damage]):
            self.mana = mana
            self.magic_damage = magic_damage
        else:
            raise ValueError('Invalid value')

    def __str__(self):
        return f"Magician: Пол {self.gender}, возраст {self.age}, рост {self.height}, вес {self.weight}, запас маны {self.mana}, магический урон {self.magic_damage}."

    def __damage__(self):
        return self.mana * self.magic_damage


class Archer(Character):
    def __init__(self, gender, age, height, weight, forces, physical_damage, attack_range):
        super().__init__(gender, age, height, weight)
        if (all(x>0 for x in [forces, physical_damage, attack_range]) and all(isinstance(x, int) for x in [forces, physical_damage, attack_range])):
            self.forces = forces
            self.physical_damage = physical_damage
            self.attack_range = attack_range
        else:
            raise ValueError('Invalid value')
        
    def __str__(self):
        return f"Archer: Пол {self.gender}, возраст {self.age}, рост {self.height}, вес {self.weight}, запас сил {self.forces}, физический урон {self.physical_damage}, дальность атаки {self.attack_range}."

    def __eq__(self, other):
        return all(getattr(self, field) == getattr(other, field) for field in ['physical_damage', 'forces', 'attack_range'])


class WarriorList(list):
    def __init__(self, name):
        super().__init__()
        self.name = name

    def append(self, p_object): 
        if (isinstance(p_object, Warrior)):
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
        for x in iterable:
            if isinstance(x, Magician):
                super().append(x)

    def print_damage(self):
        print(sum(x.magic_damage for x in self))

class ArcherList(list):
    def __init__(self,name):
        super().__init__()
        self.name = name
        
    def append(self, p_object): 
        if (isinstance(p_object, Archer)):
            super().append(p_object)
        else:
            raise TypeError(f"Invalid type {type(p_object)}")

    def print_count(self):
        count=0
        for x in self:
            if x.gender == 'm': count+=1
        print(count)
