class Character:
    def __init__(self, gender, age, height, weight):
        if (gender in ['m', 'w'] and all ((isinstance(x, int) and x>0) for x in [age, height, weight])):
            self.gender = gender
            self.age = age
            self.height = height
            self.weight = weight
        else: raise ValueError("Invalid value")
    
class Warrior(Character):
    def __init__(self, gender, age, height, weight, forces, physical_damage, armor):
        if (gender in ['m', 'w'] and all ((isinstance(x, int) and x>0) for x in [age, height, weight, forces, physical_damage, armor])):
            self.gender = gender
            self.age = age
            self.height = height
            self.weight = weight
            self.forces = forces
            self.physical_damage = physical_damage
            self.armor = armor
        else: raise ValueError("Invalid value")

    def __str__(self):
        return f"Warrior: Пол {self.gender}, возраст {self.age}, рост {self.height}, вес {self.weight}, запас сил {self.forces}, физический урон {self.physical_damage}, броня {self.armor}."

    def __eq__(self, other):
        return self.physical_damage == other.physical_damage and self.forces == other.forces and self.armor == other.armor

class Magician(Character):
    def __init__(self, gender, age, height, weight, mana, magic_damage):
        if (gender in ['m', 'w'] and all ((isinstance(x, int) and x>0) for x in [age, height, weight, mana, magic_damage])):
            self.gender = gender
            self.age = age
            self.height = height
            self.weight = weight
            self.mana = mana
            self.magic_damage = magic_damage
        else: raise ValueError("Invalid value")
    
    def __str__(self):
        return f"Magician: Пол {self.gender}, возраст {self.age}, рост {self.height}, вес {self.weight}, запас маны {self.mana}, магический урон {self.magic_damage}."
    
    def __damage__(self):
        return self.mana*self.magic_damage

class Archer(Character):
    def __init__(self, gender, age, height, weight, forces, physical_damage, attack_range):
        if (gender in ['m', 'w'] and all ((isinstance(x, int) and x>0) for x in [age, height, weight, forces, physical_damage, attack_range])):
            self.gender = gender
            self.age = age
            self.height = height
            self.weight = weight
            self.forces = forces
            self.physical_damage = physical_damage
            self.attack_range = attack_range
        else: raise ValueError("Invalid value")
    
    def __str__(self):
        return f"Archer: Пол {self.gender}, возраст {self.age}, рост {self.height}, вес {self.weight}, запас сил {self.forces}, физический урон {self.physical_damage}, дальность атаки {self.attack_range}."
        
    def __eq__(self, other):
        return self.physical_damage == other.physical_damage and self.forces == other.forces and self.attack_range == other.attack_range

class WarriorList(list):
    def __init__(self, name):
        super().__init__()
        self.name=name
        
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
        self.name=name
           
    def extend(self, iterable):
        magican_list = [element for element in iterable if isinstance(element, Magician)]
        super().extend(magican_list)
        
    def print_damage(self): 
        all_damage = 0
        for element in self:
            all_damage+=element.magic_damage
        print(all_damage)
            
class ArcherList(list):
    def __init__(self, name):
        super().__init__()
        self.name=name   
               
    def append(self, p_object): 
        if isinstance(p_object, Archer):
            super().append(p_object)
        else:
            raise TypeError(f"Invalid type {type(p_object)}")
        
    def print_count(self): 
        count_men = 0
        for element in self:
            if element.gender == 'm':
                count_men+=1
        print(count_men)
