class Character:
    def __init__(self, gend, ag, hght, wght):
        if (gend not in 'mw') or type(ag) != int or ag <= 0 or type(hght) != int or hght <= 0 or type(wght) != int or wght <= 0:
            raise ValueError('Invalid value')
        self.gender = gend
        self.age = ag
        self.height = hght
        self.weight = wght
    
class Warrior(Character):
    def __init__(self, gend, ag, hght, wght, forc, phs_dmg, arm):
        super().__init__(gend, ag, hght, wght)
        if type(forc) != int or forc <= 0 or type(phs_dmg) != int or phs_dmg <= 0 or type(arm) != int or arm <= 0:
            raise ValueError('Invalid value')
        self.forces = forc
        self.physical_damage = phs_dmg
        self.armor = arm

    def __str__(self):
        return f'Warrior: Пол {self.gender}, возраст {self.age}, рост {self.height}, вес {self.weight}, запас сил {self.forces}, физический урон {self.physical_damage}, броня {self.armor}.'

    def __eq__(self, dr):
        return True if (self.forces == dr.forces and self.physical_damage == dr.physical_damage and self.armor == dr.armor) else False

class Magician(Character):
    def __init__(self, gend, ag, hght, wght, mn, mgc_dmg):
        super().__init__(gend, ag, hght, wght)
        if type(mn) != int or mn <= 0 or type(mgc_dmg) != int or mgc_dmg <= 0:
            raise ValueError('Invalid value')
        self.mana = mn
        self.magic_damage = mgc_dmg
        
    def __str__(self):
        return f'Magician: Пол {self.gender}, возраст {self.age}, рост {self.height}, вес {self.weight}, запас маны {self.mana}, магический урон {self.magic_damage}.'

    def __damage__(self):
        return self.mana * self.magic_damage

class Archer(Character):
    def __init__(self, gend, ag, hght, wght, forc, phs_dmg, atk_r):
        super().__init__(gend, ag, hght, wght)
        if type(forc) != int or forc <= 0 or type(phs_dmg) != int or phs_dmg <= 0 or type(atk_r) != int or atk_r <= 0:
            raise ValueError('Invalid value')
        self.forces = forc
        self.physical_damage = phs_dmg
        self.attack_range = atk_r
    
    def  __str__(self):
        return f'Archer: Пол {self.gender}, возраст {self.age}, рост {self.height}, вес {self.weight}, запас сил {self.forces}, физический урон {self.physical_damage}, дальность атаки {self.attack_range}.'

    def __eq__(self, dr):
        return True if (self.forces == dr.forces and self.physical_damage == dr.physical_damage and self.attack_range == dr.attack_range) else False

class WarriorList(list):
    def __init__(self, name):
        super().__init__()
        self.name = name

    def append(self, p_object):
        if isinstance(p_object, Warrior):
            super().append(p_object)
        else:
            a = type(p_object)
            raise TypeError('Invalid type {a}')

    def print_count(self): 
        print(len(self))

class MagicianList(list):
    def __init__(self, name):
        super().__init__()
        self.name = name
       
    def extend(self, iterable):
        for i in iterable:
            if isinstance(i, Magician):
                super().append(i)

    def print_damage(self): 
        summ = 0
        for i in self:
            summ += i.magic_damage
        print(summ)

class ArcherList(list):
    def __init__(self, name):
        super().__init__()
        self.name = name
           
    def append(self, p_object):
        if isinstance(p_object, Archer):
            super().append(p_object)
        else:
            a = type(p_object)
            raise TypeError('Invalid type {a}')

    def print_count(self):
        c = 0
        for i in self:
            if i.gender == 'm':
                c += 1
        print(c)
