class Character:
    def __init__(self, gender: str, age: int, height: int, weight: int):
        if not ((gender == 'm' or gender == 'w') and age >  0 and \
            height > 0 and weight > 0):
                raise ValueError('Invalid value')
        self.gender = gender
        self.age = age
        self.height = height
        self.weight = weight
    
class Warrior(Character):
    def __init__(self, gender: str, age: int, height: int, weight: int,
                    forces: int, physical_damage: int, armor: int):
        super().__init__(gender, age, height, weight)
        if not (forces > 0 and physical_damage > 0 and \
           armor > 0):
               raise ValueError('Invalid value')
        self.forces = forces
        self.physical_damage = physical_damage
        self.armor = armor

    def __str__(self):
        return f"Warrior: Пол {self.gender}, возраст {self.age}, рост {self.height}, вес {self.weight}, запас сил {self.forces}, физический урон {self.physical_damage}, броня {self.armor}."

    def __eq__(self, other):
        return self.physical_damage == other.physical_damage and \
            self.forces == other.forces and self.armor == other.armor 

class Magician(Character):
    def __init__(self, gender: str, age: int, height: int, weight: int,
                    mana: int, magic_damage: int):
        super().__init__(gender, age, height, weight) #Наследуется от класса Character
        if not(mana > 0 and magic_damage > 0):
            raise ValueError('Invalid vlaue')
        self.mana = mana
        self.magic_damage = magic_damage

    def __str__(self):
        return f"Magician: Пол {self.gender}, возраст {self.age}, рост {self.height}, вес {self.weight}, запас маны {self.mana}, магический урон {self.magic_damage}."
    
    def __damage__(self):
        return self.mana * self.magic_damage


class Archer(Character): 
    def __init__(self, gender: str, age: int, height: int, weight: int,
                    forces: int, physical_damage: int, attack_range: int):
        super().__init__(gender, age, height, weight)
        if not (forces > 0 and physical_damage > 0 and \
           attack_range > 0):
               raise ValueError('Invalid value')
        self.forces = forces
        self.physical_damage = physical_damage
        self.attack_range = attack_range

    def __str__(self):
        return f'Archer: Пол {self.gender}, возраст {self.age}, рост {self.height}, вес {self.weight}, запас сил {self.forces}, физический урон {self.physical_damage}, дальность атаки {self.attack_range}.'
    
    def __eq__(self, other):
        return self.physical_damage == other.physical_damage and \
            self.forces == other.forces and self.attack_range == other.attack_range


class WarriorList(list):
    def __init__(self, name):
        self.name = name

    def append(self, p_object):
        if isinstance(p_object, Warrior):
            super(WarriorList, self).append(p_object)
        else:
            raise TypeError(f'Invalid type <тип_объекта {p_object}>') 

    def print_count(self):
        print(len(self))
        
class MagicianList(list):
    def __init__(self, name):
        self.name = name
     
    def extend(self, iterable):
        for i in iterable:
            if isinstance(i, self.name):
                super(MagicianList, self).append(i) 

    def print_damage(self):
        print(sum([i.magic_damage for i in self]))   
        
class ArcherList(list):
    def __init__(self, name):
        super().__init__()
        self.name = name
           
    def append(self, p_object):
        if isinstance(p_object, self.name):
            super(ArcherList, self).append(p_object)
        else:
            raise TypeError(f'Invalid type <тип_объекта {p_object}>')

    def print_count(self):
        print(len([i for i in self if i.gender == 'm']))