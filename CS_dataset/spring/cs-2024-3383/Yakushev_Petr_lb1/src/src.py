class Character:
    def __init__(self,gender,age,height,weight):
        if not(isinstance(age,int)and age>0 and isinstance(height,int)and height>0 and isinstance(weight,int) and weight>0 and (gender=='w'or gender=='m')):
            raise ('Invalid value')
        self.age=age
        self.gender=gender
        self.height=height
        self.weight=weight
    
class Warrior(Character):
    def __init__(self,gender,age,height,weight,forces,physical_damage,armor):
        super().__init__(gender,age,height,weight)
        if not(isinstance(age,int)and age>0 and isinstance(height,int)and height>0 and isinstance(weight,int) and weight>0 and (gender=='w'or gender=='m')and isinstance(forces,int)and forces>0 and isinstance(armor,int)and armor>0 and isinstance(physical_damage,int)and physical_damage>0):
            raise ('Invalid value')
        self.armor=armor
        self.forces=forces
        self.physical_damage=physical_damage
    def __str__(self):
        pred = ("Warrior: Пол " + str(self.gender) + ", возраст " + str(self.age) + ", рост " + str(self.height) + ", вес " + str(self.weight) + ", запас сил " + str(self.forces) + ", физический урон " + str(self.physical_damage) + ", броня " + str(self.armor) + ".")
        return pred
    def __eq__(self,self2):
        return self.forces==self2.forces and self.armor==self2.armor and self.physical_damage==self2.physical_damage
    
class Magician(Character):
    def __init__(self,gender,age,weight,height,mana,magic_damage):
        super().__init__(gender,age,weight,height)
        if not(isinstance(age,int)and age>0 and isinstance(height,int)and height>0 and isinstance(weight,int) and weight>0 and (gender=='w'or gender=='m')and isinstance(mana,int)and mana>0 and isinstance(magic_damage,int)and magic_damage>0):
            raise ('Invalid value')
        self.mana=mana
        self.magic_damage=magic_damage
    def __str__(self):
        pred = ("Magician: Пол " + str(self.gender) + ", возраст " + str(self.age) + ", рост " + str(self.height) + ", вес " + str(self.weight) + ", запас маны " + str(self.mana) + ", магический урон " + str(self.magic_damage) +".")
        return pred
    def __damage__(self):
        return (self.mana*self.magic_damage)    

class Archer(Character):
    def __init__(self,gender,age,weight,height,forces,physical_damage,attack_range):
        super().__init__(gender,age,weight,height)
        if not(isinstance(age,int)and age>0 and isinstance(height,int)and height>0 and isinstance(weight,int) and weight>0 and (gender=='w'or gender=='m')and isinstance(forces,int)and forces>0 and isinstance(physical_damage,int)and physical_damage>0 and isinstance(attack_range,int)and attack_range>0):
            raise ('Invalid value')
        self.attack_range=attack_range
        self.forces=forces
        self.physical_damage=physical_damage
    def __str__(self):
        pred = ("Archer: Пол " + str(self.gender) + ", возраст " + str(self.age) + ", рост " + str(self.height) + ", вес " + str(self.weight) + ", запас сил " + str(self.forces) + ", физический урон " + str(self.physical_damage) + ", дальность атаки " + str(self.attack_range) + ".")
        return pred
    def __eq__(self,self2):
        return self.forces==self2.forces and self.physical_damage==self2.physical_damage and self.attack_range==self2.attack_range 

class WarriorList(list):
    def __init__(self,name):
        super().__init__()
        self.name=name
    def append (self,p_object):
        if isinstance(p_object,Warrior):
            super().append(p_object)
        else:
            raise "Invalid type <тип_объекта p_object>"
    def print_count(self): 
        print (len(self)) 
        
class MagicianList(list):
    def __init__(self,name):
        super().__init__()
        self.name=name
    def extend(self,iterable): 
        super().extend(item	for	item	in	iterable	if isinstance(item, Magician))
    def print_damage(self): 
        sum=0
        for item in self:
            sum+=item.magic_damage
        print (sum)
class ArcherList(list):
    def __init__(self,name):
        super().__init__()
        self.name=name
    def append (self,p_object):
        if isinstance(p_object,Archer):
            super().append(p_object)
        else:
            raise "Invalid type <тип_объекта p_object>"

    def print_count(self): 
        sum=0
        for item in self:
            if item.gender=='m':
                sum+=1
        print(sum)
        
