class Character:
    def __init__(self,gender,age,height,weight):
        if not(gender[0]=='m') and not(gender[0]=='w'):
            raise ValueError ('Invalid value')
        if not(isinstance(age,int)) or not(age>0):
            raise ValueError ('Invalid value')
        if not(isinstance(height,int)) or not(height>0):
            raise ValueError ('Invalid value')
        if not(isinstance(weight,int)) or not(weight>0):
            raise ValueError ('Invalid value')
        self.gender=gender
        self.age=age
        self.height=height
        self.weight=weight

    
class Warrior(Character):
    def __init__(self,gender,age,height,weight,forces,physical_damage,armor):
        if not(isinstance(forces,int)) or not(forces>0):
            raise ValueError ('Invalid value')
        if not(isinstance(physical_damage,int)) or not(physical_damage>0):
            raise ValueError ('Invalid value')
        if not(isinstance(armor,int)) or not(armor>0):
            raise ValueError ('Invalid value')
        super().__init__(gender,age,height,weight)
        self.forces=forces
        self.physical_damage=physical_damage
        self.armor=armor
    def __str__(self):
        return f'Warrior: Пол {self.gender}, возраст {self.age}, рост {self.height}, вес {self.weight}, запас сил {self.forces}, физический урон {self.physical_damage}, броня {self.armor}.' 
    def __eq__(self,other):
        return  (self.physical_damage==other.physical_damage) and (self.forces==other.forces) and (self.armor==other.armor)

class Magician(Character):
    def __init__(self,gender,age,height,weight,mana,magic_damage):
        if not(isinstance(mana,int)) or not(mana>0):
            raise ValueError ('Invalid value')
        if not(isinstance(magic_damage,int)) or not(magic_damage>0):
            raise ValueError ('Invalid value')
        super().__init__(gender,age,height,weight)
        self.mana=mana
        self.magic_damage=magic_damage
    def __str__(self):
        return f'Magician: Пол {self.gender}, возраст {self.age}, рост {self.height}, вес {self.weight}, запас маны {self.mana}, магический урон {self.magic_damage}.' 
    def __damage__(self):
        return self.mana* self.magic_damage


class Archer(Character):
    def __init__(self,gender,age,height,weight,forces,physical_damage,attack_range):
        if not(isinstance(forces,int)) or not(forces>0):
            raise ValueError ('Invalid value')
        if not(isinstance(physical_damage,int)) or not(physical_damage>0):
            raise ValueError ('Invalid value')
        if not(isinstance(attack_range,int)) or not(attack_range>0):
            raise ValueError ('Invalid value')
        super().__init__(gender,age,height,weight)
        self.forces=forces
        self.physical_damage=physical_damage
        self.attack_range=attack_range
    def __str__(self):
        return f'Archer: Пол {self.gender}, возраст {self.age}, рост {self.height}, вес {self.weight}, запас сил {self.forces}, физический урон {self.physical_damage}, дальность атаки {self.attack_range}.' 
    def __eq__(self,other):
        return (self.physical_damage==other.physical_damage) and (self.forces==other.forces) and (self.attack_range==other.attack_range) 
class WarriorList(list):
    def __init__(self,name):
        super().__init__()
        self.name=name
    
    def append(self,p_object): 
        if isinstance(p_object,Warrior):
            super().append(p_object)
        else:
            raise TypeError ('Invalid type {type(p_object).__name__}')

    def print_count(self): 
        print (len(self))
        
class MagicianList(list):
    def __init__(self,name):
        super().__init__()
        self.name=name
    
    def extend(self,iterable): 
        for iter in iterable:
            if isinstance(iter,Magician):
                super().append(iter)

    def print_damage(self): 
        print (sum([i.magic_damage for i in list(self)]))
        
class ArcherList(list):
    def __init__(self,name):
        super().__init__()
        self.name=name
    
    def append(self,p_object): 
        if isinstance(p_object,Archer):
            super().append(p_object)
        else:
            raise TypeError ('Invalid type {type(p_object).__name__}')

    def print_count(self): 
        print (len([i.gender for i in list(self) if i.gender[0]=='m']))

