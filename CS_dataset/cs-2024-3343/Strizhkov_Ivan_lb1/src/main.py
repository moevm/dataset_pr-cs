class Character:
    def __init__(self, gender, age, height, weight):
        if gender not in ['m', 'w'] or not (isinstance(age, int) and age > 0) or not (isinstance(height, int) and height > 0) or not (isinstance(weight, int) and weight > 0):
            raise ValueError('Invalid value')
        self.gender = gender
        self.age = age
        self.height = height
        self.weight = weight

class Warrior(Character):
    def __init__(self, gender, age, height, weight, forces, physical_damage, armor):
        super().__init__(gender, age, height, weight)
        if not (isinstance(forces, int) and forces > 0) or not (isinstance(physical_damage, int) and physical_damage > 0) or not (isinstance(armor, int) and armor > 0):
            raise ValueError('Invalid value')
        self.forces = forces
        self.physical_damage = physical_damage
        self.armor = armor
    
    def __str__(self):
        return f"Warrior: Пол {self.gender}, возраст {self.age}, рост {self.height}, вес {self.weight}, запас сил {self.forces}, физический урон {self.physical_damage}, броня {self.armor}."
    
    def __eq__(self, other):
        if not isinstance(other, Warrior):
            return False
        return self.physical_damage == other.physical_damage and self.forces == other.forces and self.armor == other.armor
    

class Magician(Character):
    def __init__(self, gender, age, height, weight, mana, magic_damage):
        super().__init__(gender, age, height, weight)
        if not (isinstance(mana, int) and mana > 0) or not (isinstance(magic_damage, int) and magic_damage > 0):
            raise ValueError('Invalid value')
        self.mana = mana
        self.magic_damage = magic_damage

    def __str__(self):
        return f"Magician: Пол {self.gender}, возраст {self.age}, рост {self.height}, вес {self.weight}, запас маны {self.mana}, магический урон {self.magic_damage}."

    def __damage__(self):
        return self.mana * self.magic_damage


class Archer(Character):
    def __init__(self, gender, age, height, weight, forces, physical_damage, attack_range):
        super().__init__(gender, age, height, weight)
        if not (isinstance(forces, int) and forces > 0) or not (isinstance(physical_damage, int) and physical_damage > 0) or not (isinstance(attack_range, int) and attack_range > 0):
            raise ValueError('Invalid value')
        self.forces = forces
        self.physical_damage = physical_damage
        self.attack_range = attack_range
    
    def __str__(self):
        return f"Archer: Пол {self.gender}, возраст {self.age}, рост {self.height}, вес {self.weight}, запас сил {self.forces}, физический урон {self.physical_damage}, дальность атаки {self.attack_range}."
    
    def __eq__(self, other):
        if not isinstance(other, Archer):
            return False
        return self.physical_damage == other.physical_damage and self.forces == other.forces and self.attack_range == other.attack_range
    

class WarriorList(list):
    def __init__(self, name):
        super().__init__()  # Вызываем конструктор базового класса
        self.name = name
    
    def append(self, p_object):
        # Переопределение метода append()
        if not isinstance(p_object, Warrior):
            raise TypeError(f"Invalid type {type(p_object).__name__}")
        super().append(p_object)
    
    def print_count(self):
        # Используем метод count() для подсчета и вывода количества воинов
        print(f"{len(self)}")

class MagicianList(list):
    def __init__(self, name):
        super().__init__()
        self.name = name
    
    def extend(self, iterable):
        # Переопределение метода extend()
        for item in iterable:
            if isinstance(item, Magician):
                super().append(item)
    
    def print_damage(self):
        # Расчет и вывод общего урона всех магов
        total_damage = sum(magic.magic_damage for magic in self)
        print(f"{total_damage}")

class ArcherList(list):
    def __init__(self, name):
        super().__init__()
        self.name = name
    
    def append(self, p_object):
        # Переопределение метода append()
        if not isinstance(p_object, Archer):
            raise TypeError(f"Invalid type {type(p_object).__name__}")
        super().append(p_object)
    
    def print_count(self):
        # Подсчет и вывод количества лучников мужского пола
        male_archers_count = len([archer for archer in self if archer.gender == 'm'])
        print(f"{male_archers_count}")
        