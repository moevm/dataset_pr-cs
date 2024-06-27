class Character:
    
    def _arepositiveints(iterable):
        return all(obj > 0 and isinstance(obj, int) for obj in iterable)
    
    def __init__(self, gender, age, height, weight):
        if gender not in ('m', 'w') or not Character._arepositiveints((age, height, weight)):
            raise ValueError('Invalid value')
        self.gender = gender
        self.age = age
        self.height = height
        self.weight = weight


class Warrior(Character):
    
    def __init__(self, gender, age, height, weight, forces, physical_damage, armor):
        if (gender not in ('m', 'w') or
                not Character._arepositiveints((age, height, weight, forces, physical_damage)) or
                not isinstance(armor, (int, float)) or
                armor <= 0):
            raise ValueError('Invalid value')
        self.gender = gender
        self.age = age
        self.height = height
        self.weight = weight
        self.forces = forces
        self.physical_damage = physical_damage
        self.armor = armor

    def __str__(self):
        return f"Warrior: Пол {self.gender}, возраст {self.age}, рост {self.height}, \
вес {self.weight}, запас сил {self.forces}, физический урон {self.physical_damage}, броня {self.armor}."

    def __eq__(self, other):
        return self.forces == other.forces and self.physical_damage == other.physical_damage and self.armor == other.armor


class Magician(Character):

    def __init__(self, gender, age, height, weight, mana, magic_damage):
        if gender not in ('m', 'w') or not Character._arepositiveints((age, height, weight, mana, magic_damage)):
            raise ValueError('Invalid value')
        self.gender = gender
        self.age = age
        self.height = height
        self.weight = weight
        self.mana = mana
        self.magic_damage = magic_damage

    def __str__(self):
        return f"Magician: Пол {self.gender}, возраст {self.age}, рост {self.height}, \
вес {self.weight}, запас маны {self.mana}, магический урон {self.magic_damage}."

    def __damage__(self):
        return self.mana*self.magic_damage


class Archer(Character):
    
    def __init__(self, gender, age, height, weight, forces, physical_damage, attack_range):
        if gender not in ('m', 'w') or not Character._arepositiveints((age, height, weight, forces, physical_damage, attack_range)):
            raise ValueError('Invalid value')
        self.gender = gender
        self.age = age
        self.height = height
        self.weight = weight
        self.forces = forces
        self.physical_damage = physical_damage
        self.attack_range = attack_range

    def __str__(self):
        return f"Archer: Пол {self.gender}, возраст {self.age}, рост {self.height}, \
вес {self.weight}, запас сил {self.forces}, физический урон {self.physical_damage}, дальность атаки {self.attack_range}."

    def __eq__(self, other):
        return self.forces == other.forces and self.physical_damage == other.physical_damage and self.attack_range == other.attack_range


class WarriorList(list):
    
    def __init__(self, name):
        self.name = name
    
    def append(self, p_object):
        if isinstance(p_object, Warrior):
            list.append(self, p_object)
        else:
            raise TypeError(f"Invalid type {type(p_object)}")
    
    def print_count(self):
        print(len(self))


class MagicianList(list):
    
    def __init__(self, name):
        self.name = name

    def extend(self, iterable):
        for obj in iterable:
            if isinstance(obj, Magician):
                list.append(self, obj)
    
    def print_damage(self):
        print(sum(map(lambda m: m.magic_damage, self)))


class ArcherList(list):

    def __init__(self, name):
        self.name = name
    
    def append(self, p_object):
        if isinstance(p_object, Archer):
            list.append(self, p_object)
        else:
            raise TypeError(f"Invalid type {type(p_object)}")
    
    def print_count(self):
        print(sum(map(lambda a: a.gender == "m", self)))
