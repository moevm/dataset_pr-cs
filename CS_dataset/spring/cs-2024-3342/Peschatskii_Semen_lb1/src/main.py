class Character:
    def __init__(self, gender, age, height, weight):
        if (gender in ["m", "w"]) and isinstance(age, int) and age > 0 and height > 0 and isinstance(height,
                                                                                                     int) and weight > 0 and isinstance(
                weight, int):
            self.gender = gender  # Пол (значение может быть одной из строк: 'm', 'w')
            self.age = age  # Возраст (целое положительное число)
            self.height = height  # Рост (в сантиметрах, целое положительное число)
            self.weight = weight  # Вес (в кг, целое положительное число)
        else:
            raise ValueError("Invalid value")


class Warrior(Character):  # Наследуется от класса Character
    def __init__(self, gender, age, height, weight, forces, physical_damage, armor):
        Character.__init__(self, gender, age, height, weight)
        if isinstance(forces, int) and isinstance(physical_damage, int) and isinstance(armor, int) and forces > 0 and physical_damage > 0 and armor > 0:
            self.forces = forces
            self.physical_damage = physical_damage
            self.armor = armor
        else:
            raise ValueError("Invalid value")

    def __str__(self):
        return f"Warrior: Пол {self.gender}, возраст {self.age}, рост {self.height}, вес {self.weight}, запас сил {self.forces}, физический урон {self.physical_damage}, броня {self.armor}."

    def __eq__(self, other):
        if self.physical_damage == other.physical_damage and self.forces == other.forces and self.armor == other.armor:
            return True
        else:
            return False


class Magician(Character):  # Наследуется от класса Character
    def __init__(self, gender, age, height, weight, mana, magic_damage):
        Character.__init__(self, gender, age, height, weight)
        if isinstance(mana, int) and isinstance(magic_damage, int) and mana > 0 and magic_damage > 0:
            self.mana = mana
            self.magic_damage = magic_damage
        else:
            raise ValueError("Invalid value")

    def __str__(self):
        return f"Magician: Пол {self.gender}, возраст {self.age}, рост {self.height}, вес {self.weight}, запас маны {self.mana}, магический урон {self.magic_damage}."

    def __damage__(self):
        return self.mana * self.magic_damage


class Archer(Character):  # Наследуется от класса Character
    def __init__(self, gender, age, height, weight, forces, physical_damage, attack_range):
        Character.__init__(self, gender, age, height, weight)
        if isinstance(forces, int) and isinstance(physical_damage, int) and isinstance(attack_range,int) and forces > 0 and physical_damage > 0 and attack_range > 0:
            self.forces = forces
            self.physical_damage = physical_damage
            self.attack_range = attack_range
        else:
            raise ValueError("Invalid value")

    def __str__(self):
        return f"Archer: Пол {self.gender}, возраст {self.age}, рост {self.height}, вес {self.weight}, запас сил {self.forces}, физический урон {self.physical_damage}, дальность атаки {self.attack_range}."

    def __eq__(self, other):
        if self.physical_damage == other.physical_damage and self.forces == other.forces and self.attack_range == other.attack_range:
            return True
        else:
            return False  # Наследуется от класса Character


class WarriorList(list):
    def __init__(self, name):
        super().__init__()
        self.name = name

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
        self.name = name

    def extend(self, iterable):
        for i in iterable:
            if isinstance(i, Magician):
                super().append(i)
            else:
                continue

    def print_damage(self):
        damage = 0
        for i in self:
            damage = i.magic_damage + damage
        print(damage)


class ArcherList(list):
    def __init__(self, name):
        super().__init__()
        self.name = name

    def append(self, p_object):
        if isinstance(p_object, Archer):
            super().append(p_object)
        else:
            raise TypeError(f"Invalid type {type(p_object)}")

    def print_count(self):
        amount = 0
        for i in self:
            if i.gender == "m":
                amount = amount + 1
        print(amount)