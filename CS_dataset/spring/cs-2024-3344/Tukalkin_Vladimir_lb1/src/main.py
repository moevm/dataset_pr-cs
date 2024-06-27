class Character:
    def __init__(self,gender,age,height,weight):
        if (gender in ["m","w"]) and isinstance(age,int) and age>0 and height>0 and isinstance(height,int) and weight>0 and isinstance(weight,int):
            self.gender=gender #Пол (значение может быть одной из строк: 'm', 'w')
            self.age=age       #Возраст (целое положительное число)
            self.height=height #Рост (в сантиметрах, целое положительное число)
            self.weight=weight #Вес (в кг, целое положительное число)
        else: raise ValueError("Invalid value")


class Warrior(Character):
    def __init__(self,gender,age,height,weight,forces,physical_damage,armor):
        super().__init__(gender,age,height,weight)
        if isinstance(forces,int) and forces>0 and physical_damage>0 and isinstance(physical_damage,int) and isinstance(armor,int) and armor>0:
            self.forces=forces                   #Запас сил (целое положительное число)
            self.physical_damage=physical_damage #Физический урон (целое положительное число)
            self.armor=armor                     #Количество брони (неотрицательное число)
        else: raise ValueError("Invalid value")

    def __str__(self):
        return f"Warrior: Пол {self.gender}, возраст {self.age}, рост {self.height}, вес {self.weight}, запас сил {self.forces}, физический урон {self.physical_damage}, броня {self.armor}."

    def __eq__(self,other):
        if isinstance(self,Warrior) and isinstance(other,Warrior) and self.physical_damage==other.physical_damage and self.armor==other.armor and self.forces==other.forces:
            return True
        else: return False


class Magician(Character):
    def __init__(self,gender,age,height,weight,mana,magic_damage):
        super().__init__(gender,age,height,weight)
        if magic_damage>0 and isinstance(magic_damage,int) and isinstance(mana,int) and mana>0:
            self.magic_damage=magic_damage #Магический урон (целое положительное число)
            self.mana=mana                 #Запас маны (целое положительное число)
        else: raise ValueError("Invalid value")

    def __str__(self):
        return f"Magician: Пол {self.gender}, возраст {self.age}, рост {self.height}, вес {self.weight}, запас маны {self.mana}, магический урон {self.magic_damage}."

    def __damage__(self):
        return self.mana*self.magic_damage


class Archer(Character):
    def __init__(self,gender,age,height,weight,forces,physical_damage,attack_range):
        super().__init__(gender,age,height,weight)
        if isinstance(forces,int) and forces>0 and physical_damage>0 and isinstance(physical_damage,int) and isinstance(attack_range,int) and attack_range>0:
            self.forces=forces                    #Запас сил (целое положительное число)
            self.physical_damage=physical_damage  #Физический урон (целое положительное число)
            self.attack_range=attack_range        #Дальность атаки (целое положительное число)
        else: raise ValueError("Invalid value")

    def __str__(self):
        return f"Archer: Пол {self.gender}, возраст {self.age}, рост {self.height}, вес {self.weight}, запас сил {self.forces}, физический урон {self.physical_damage}, дальность атаки {self.attack_range}."

    def __eq__(self, other):
        if isinstance(self, Archer) and isinstance(other, Archer) and self.physical_damage == other.physical_damage and self.attack_range == other.attack_range and self.forces == other.forces:
            return True
        else: return False


class WarriorList(list):
    '''Конструктор:
       1. Вызвать конструктор базового класса.
       2. Передать в конструктор строку name и присвоить её полю name созданного объекта'''
    def __init__(self,name):
        super().__init__()
        self.name=name

    def append(self,p_object):
        if isinstance(p_object,Warrior): super().append(p_object)
        else: raise TypeError(f"Invalid type {type(p_object)}")

    def print_count(self):
        print(self.count(warrior1))



class MagicianList(list):
    def __init__(self,name):
        super().__init__()
        self.name=name

    def extend(self,iterable):
        for i in iterable:
            if isinstance(i,Magician):
                super().append(i)
            else: continue

    def print_damage(self):
        count=0
        for i in self:
            count+=i.magic_damage
        print(count)


class ArcherList(list):
    def __init__(self,name):
        super().__init__()
        self.name=name

    def append(self,p_object):
        if isinstance(p_object,Archer):
            super().append(p_object)
        else:
            raise TypeError(f"Invalid type {type(p_object)}")

    def print_count(self):
        count=0
        for i in self:
            if i.gender=="m":
                count+=1
        print(count)
