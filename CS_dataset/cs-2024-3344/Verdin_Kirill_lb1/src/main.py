class Character:
	def __init__(self, gender, age, height, weight):
		if gender not in ["m", "w"]:
			raise ValueError("Invalid value")
		self.gender = gender
		if not(type(age) == type(1) and age > 0):
			raise ValueError("Invalid value")
		self.age = age
		if not(type(height) == type(1) and height > 0):
			raise ValueError("Invalid value")
		self.height = height
		if not(type(weight) == type(1) and weight > 0):
			raise ValueError("Invalid value")
		self.weight = weight

    
class Warrior(Character):
    
    def __init__(self, gender, age, height, weight, forces, physical_damage, armor):
        super().__init__(gender, age, height, weight)
        if not(type(forces) == type(1) and forces > 0):
            raise ValueError("Invalid value")
        self.forces = forces
        if not(type(physical_damage) == type(1) and physical_damage > 0):
            raise ValueError("Invalid value")
        self.physical_damage = physical_damage
        if not(type(armor) == type(1) and armor > 0):
            raise ValueError("Invalid value")
        self.armor = armor
         
    def __str__(self):
        return f"Warrior: Пол {self.gender}, возраст {self.age}, рост {self.height}, вес {self.weight}, запас сил {self.forces}, физический урон {self.physical_damage}, броня {self.armor}."

    def __eq__(self, other):
        if self.physical_damage == other.physical_damage and self.forces == other.forces and self.armor == other.armor:
            return True
        return False
	
    

class Magician(Character): #Наследуется от класса Character
    def __init__(self, gender, age, height, weight, mana, magic_damage):
        super().__init__(gender, age, height, weight)
        if not(type(mana) == type(1) and mana > 0):
            raise ValueError("Invalid value")
        self.mana = mana
        if not(type(magic_damage) == type(1) and magic_damage > 0):
            raise ValueError("Invalid value")
        self.magic_damage = magic_damage
         
    def __str__(self):
        return f"Magician: Пол {self.gender}, возраст {self.age}, рост {self.height}, вес {self.weight}, запас маны {self.mana}, магический урон {self.magic_damage}."

    def __damage__(self):
         return self.magic_damage * self.mana


class Archer(Character):
    #Наследуется от класса Character
	def __init__(self, gender, age, height, weight, forces, physical_damage, attack_range):
		super().__init__(gender, age, height, weight)
		if not(type(forces) == type(1) and forces > 0):
			raise ValueError("Invalid value")
		self.forces = forces
		if not(type(physical_damage) == type(1) and physical_damage > 0):
			raise ValueError("Invalid value")
		self.physical_damage = physical_damage
		if not(type(attack_range) == type(1) and attack_range > 0):
			raise ValueError("Invalid value")
		self.attack_range = attack_range
    

	def __str__(self):
		return f"Archer: Пол {self.gender}, возраст {self.age}, рост {self.height}, вес {self.weight}, запас сил {self.forces}, физический урон {self.physical_damage}, дальность атаки {self.attack_range}."	

	def __eq__(self, other):
		if self.physical_damage == other.physical_damage and self.forces == other.forces and self.attack_range == other.attack_range:
			return True
		return False


class WarriorList(list):
	def __init__(self, name):
		super().__init__()
		self.name = name

	def append(self, p_object):
		if not isinstance(p_object, Warrior):
			raise TypeError(f"Invalid type {type(p_object)}")
		super().append(p_object)
        
	def print_count(self):
		print(len(self))

        
class MagicianList(list):
	def __init__(self, name):
		super().__init__()
		self.name = name

	def extend(self, iterable):
		for x in iterable:
			if isinstance(x, Magician): super().append(x)
        
	def print_damage(self):
		print(sum([x.magic_damage for x in self]))
   
        
class ArcherList(list):
	def __init__(self, name):
		super().__init__()
		self.name = name

	def append(self, p_object):
		if not isinstance(p_object, Archer):
			raise TypeError(f"Invalid type {type(p_object)}")
		super().append(p_object)

	def print_count(self):
		print(len([x for x in self if x.gender == "m"]))