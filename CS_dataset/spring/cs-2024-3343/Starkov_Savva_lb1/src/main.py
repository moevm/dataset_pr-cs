class Character:
    def __init__(self, gender, age, height, weight):
        if gender not in ['m', 'w']:
            raise ValueError('Invalid value')
        if not isinstance(age, int) or age <= 0:
            raise ValueError('Invalid value')
        if not isinstance(height, int) or height <= 0:
            raise ValueError('Invalid value')
        if not isinstance(weight, int) or weight <= 0:
            raise ValueError('Invalid value')

        self.gender = gender
        self.age = age
        self.height = height
        self.weight = weight

class Warrior(Character):  # Наследуется от класса Character
    def __init__(self, gender, age, height, weight, forces,physical_damage,armor):
        super().__init__(gender, age, height,weight)
        if not isinstance(forces, int) or forces <= 0:
            raise ValueError('Invalid value')
        if not isinstance(physical_damage, int) or physical_damage <= 0:
            raise ValueError('Invalid value')
        if not isinstance(armor, int) or armor <= 0:
            raise ValueError('Invalid value')
        self.physical_damage =physical_damage
        self.forces =forces
        self.armor = armor



    def __str__(self):
        return f"Warrior: Пол {self.gender}, возраст {self.age}, рост {self.height}, вес {self.weight}, запас сил {self.forces}, физический урон {self.physical_damage}, броня {self.armor}."
    def __eq__(self,other):
        if type(other) == type(self):
            if self.physical_damage == other.physical_damage and self.forces == other.forces and self.armor == other.armor:
                return True
            else:
                return False
        else: return False


class Magician(Character):
    def __init__(self, gender, age, height, weight,mana,magic_damage):
        super().__init__(gender,age,height,weight)
        if not isinstance(mana, int) or mana <= 0:
            raise ValueError('Invalid value')
        if not isinstance(magic_damage, int) or magic_damage <= 0:
            raise ValueError('Invalid value')
        self.mana = mana
        self.magic_damage = magic_damage

    def __str__(self):
        return f"Magician: Пол {self.gender}, возраст {self.age}, рост {self.height}, вес {self.weight}, запас маны {self.mana}, магический урон {self.magic_damage}."

    def __damage__(self):
        return self.mana * self.magic_damage


class Archer(Character):

    def __init__(self, gender, age, height, weight,forces,physical_damage,attack_range):
        super().__init__(gender,age,height,weight)
        if forces>0 and physical_damage>0 and attack_range > 0:
            self.forces = forces
            self.physical_damage = physical_damage
            self.attack_range = attack_range
        else:
            raise ValueError("Invalid value")

    def __str__(self):
        return f"Archer: Пол {self.gender}, возраст {self.age}, рост {self.height}, вес {self.weight}, запас сил {self.forces}, физический урон {self.physical_damage}, дальность атаки {self.attack_range}."
    def __eq__(self,other):
        if type(other)  == type(self):
            if self.physical_damage == other.physical_damage and self.attack_range == other.attack_range and self.forces == other.forces:
                return True
            else:
                return False
        else:
            return False


class WarriorList(list):
    def __init__(self,name):
        super().__init__()
        self.name = name
    def append(self,p_object):
        if isinstance(p_object,Warrior):
            super().append(p_object)
        else:
            raise TypeError(f'Invalid type {type(p_object)}')
    def print_count(self):
        count =0
        for item in self:
            count+=1
        print(count)

class MagicianList(list):
    def __init__(self, name):
        super().__init__(self)
        self.name = name
        # '''– список магов - наследуется от класса list.'''
    def extend(self, iterable):
        for item in iterable:
            if isinstance(item, Magician):
                self.append(item)
    def print_damage(self):
        count_damage = 0
        for item in self:
            count_damage+= item.magic_damage
        print(count_damage)

class ArcherList(list):
    def __init__(self,name):
        super().__init__()
        self.name = name
    def append(self, object):
        if isinstance(object,Archer):
            super().append(object)
        else:
            raise TypeError(f'Invalid type {type(object)}')
    def print_count(self):
        count = 0
        for item in self:
            if item.gender == 'm':
                count+=1
        print(count)
