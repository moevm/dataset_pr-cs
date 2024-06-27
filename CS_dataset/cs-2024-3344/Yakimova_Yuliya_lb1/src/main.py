class Character:
    def __init__(self, gender, age, height, weight):
        if ((gender in ["m", "w"]) and (type(age) == type(1)) and (age > 0) and (type(height) == type(1)) and (height > 0) and (type(weight) == type(1)) and (weight > 0)):
            self.gender = gender 
            self.age = age
            self.height = height
            self.weight = weight
        else: raise ValueError("Invalid value")
    
class Warrior(Character):
    def __init__(self, gender, age, height, weight, forces, physical_damage, armor):
        super().__init__(gender, age, height, weight)
        if ((type(forces) == type(1)) and (forces > 0) and (type(physical_damage) == type(1)) and (physical_damage > 0) and (type(armor) == type(1)) and (armor > 0)):
            self.forces = forces
            self.physical_damage = physical_damage
            self.armor = armor
        else: raise ValueError("Invalid value")

    def __str__(self):
        return f"Warrior: Пол {self.gender}, возраст {self.age}, рост {self.height}, вес {self.weight}, запас сил {self.forces}, физический урон {self.physical_damage}, броня {self.armor}."

    def __eq__(self, other):
        if (self.physical_damage == other.physical_damage and self.forces == other.forces and self.armor == other.armor):
            return True
        return False

class Magician(Character):
    def __init__(self, gender, age, height, weight, mana, magic_damage):
        super().__init__(gender, age, height, weight)
        if ((type(mana) == type(1)) and (mana > 0) and (type(magic_damage) == type(1)) and (magic_damage > 0)):
            self.mana = mana
            self.magic_damage = magic_damage
        else: raise ValueError("Invalid value")
        
    def __str__(self):
        return f"Magician: Пол {self.gender}, возраст {self.age}, рост {self.height}, вес {self.weight}, запас маны {self.mana}, магический урон {self.magic_damage}."

    def __damage__(self):
        return self.magic_damage * self.mana

class Archer(Character):
    def __init__(self, gender, age, height, weight, forces, physical_damage, attack_range):
        super().__init__(gender, age, height, weight)
        if (isinstance(forces,int) and forces > 0 and physical_damage > 0 and isinstance(physical_damage,int) and isinstance(attack_range,int) and attack_range > 0):
            self.forces=forces
            self.physical_damage=physical_damage
            self.attack_range=attack_range
        else: raise ValueError("Invalid value")

    def __str__(self):
        return f"Archer: Пол {self.gender}, возраст {self.age}, рост {self.height}, вес {self.weight}, запас сил {self.forces}, физический урон {self.physical_damage}, дальность атаки {self.attack_range}."

    def __eq__(self, other):
        if isinstance(self, Archer) and isinstance(other, Archer) and self.physical_damage == other.physical_damage and self.attack_range == other.attack_range and self.forces == other.forces:
            return True
        else: return False


class WarriorList(list):
    def __init__(self,name):
        super().__init__()
        self.name=name

    def append(self, p_object): 
        if isinstance(p_object, Warrior):
            super().append(p_object)
        else: raise TypeError(f"Invalid type {type(p_object)}")

    def print_count(self):
        print(len(self))
 
class MagicianList(list):
    def __init__(self,name):
        super().__init__()
        self.name=name

    def extend(self, iterable): 
        for i in iterable:
            if isinstance(i, Magician):
                super().append(i)

    def print_damage(self): 
        counter = 0
        for i in self:
            counter += i.magic_damage
        print(counter)     
        
class ArcherList(list):
    def __init__(self,name):
        super().__init__()
        self.name=name
       
    def append(self, p_object): 
        if isinstance(p_object, Archer):
            super().append(p_object)
        else: raise TypeError(f"Invalid type {type(p_object)}")

    def print_count(self): 
        counter = 0
        for i in self:
            if i.gender == "m": counter+=1
        print(counter)  