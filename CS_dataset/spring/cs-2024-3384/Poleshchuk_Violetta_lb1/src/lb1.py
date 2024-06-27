def not_suitable(number):
    return (not( isinstance(number, int) and number > 0))

class Character:
    def __init__(self, gender, age, height, weight):
        if (gender != 'm' and gender != 'w') or not_suitable(age) or not_suitable(height) or not_suitable(weight):
            raise ValueError('Invalid value')
        
        self.gender = gender
        self.age = age
        self.height = height
        self.weight = weight
            

class Warrior(Character): #Наследуется от класса Character
    def __init__(self, gender, age, height, weight, forces, physical_damage, armor):
        super().__init__(gender, age, height, weight)
        if not_suitable(forces) or not_suitable(physical_damage) or not_suitable(armor):
            raise ValueError('Invalid value')
        
        self.forces = forces
        self.physical_damage = physical_damage
        self.armor = armor
    

    def __str__(self):
        return f"Warrior: Пол {self.gender}, возраст {self.age}, рост {self.height}, вес {self.weight}, запас сил {self.forces}, физический урон {self.physical_damage}, броня {self.armor}."

    def __eq__(self, other):
        return isinstance(self, Warrior) and isinstance(other, Warrior) and self.physical_damage == other.physical_damage and self.forces == other.forces and self.armor == other.armor
    
    

class Magician(Character): #Наследуется от класса Character
    def __init__(self, gender, age, height, weight, mana, magic_damage):
        super().__init__(gender, age, height, weight)
        if not_suitable(mana) or not_suitable(magic_damage):
            raise ValueError('Invalid value')
        
        self.mana = mana 
        self.magic_damage = magic_damage
        
    def __str__(self):
        return f"Magician: Пол {self.gender}, возраст {self.age}, рост {self.height}, вес {self.weight}, запас маны {self.mana}, магический урон {self.magic_damage}."

    def __damage__(self):
        return self.mana*self.magic_damage


class Archer(Character): #Наследуется от класса Character
    def __init__(self, gender, age, height, weight, forces, physical_damage, attack_range):
        super().__init__(gender, age, height, weight)
        if not_suitable(forces) or not_suitable(physical_damage) or not_suitable(attack_range):
            raise ValueError('Invalid value')
        
        self.forces = forces
        self.physical_damage = physical_damage
        self.attack_range = attack_range

    def __str__(self):
        return f"Archer: Пол {self.gender}, возраст {self.age}, рост {self.height}, вес {self.weight}, запас сил {self.forces}, физический урон {self.physical_damage}, дальность атаки {self.attack_range}."
    
    def __eq__(self, other):
        return isinstance(self, Archer) and isinstance(other, Archer) and self.physical_damage == other.physical_damage and self.forces == other.forces and self.attack_range == other.attack_range
    

class WarriorList(list):
    def __init__(self, name):
        super().__init__()
        self.name = name

    def append(self, p_object): 
        if isinstance(p_object, Warrior):
            super().append(p_object)
        else:
            raise TypeError(f"Invalid type <{type(p_object)}>")

    def print_count(self):
        print(len(self)) 
    
        
class MagicianList(list):
    def __init__(self, name):
        super().__init__()
        self.name = name
       
    def extend(self, iterable): 
        for item in iterable:
            if isinstance(item, Magician):
                self.append(item)
            

    def print_damage(self): 
        print(sum(item.magic_damage for item in self))    
        
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
        print(sum(1 for item in self if item.gender == 'm'))