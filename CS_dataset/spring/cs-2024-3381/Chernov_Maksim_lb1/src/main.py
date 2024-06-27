class Character:
    """Поля объекта класс Character:
    gender - пол (значение может быть одной из строк: 'm', 'w')
    age - возраст (целое положительное число)
    height - рост (в сантиметрах, целое положительное число)
    weight - вес (в кг, целое положительное число)
    При создании экземпляра класса Character необходимо убедиться, что переданные в конструктор параметры удовлетворяют требованиям, иначе выбросить исключение ValueError с текстом 'Invalid value'.
    """

    def __init__(self, gender: str, age: int, height: int, weight: int):
        if not isinstance(gender, str) or gender not in ('m', 'w'):
            raise ValueError("Invalid value")
        if not isinstance(age, int) or age <= 0:
            raise ValueError("Invalid value")
        if not isinstance(height, int) or height <= 0:
            raise ValueError("Invalid value")
        if not isinstance(weight, int) or weight <= 0:
            raise ValueError("Invalid value")
        self.gender = gender
        self.age = age
        self.height = height
        self.weight = weight


class Warrior(Character):  # Наследуется от класса Character
    """Поля объекта класс Warrior:
    gender - пол (значение может быть одной из строк: 'm', 'w')
    age - возраст (целое положительное число)
    height - рост (в сантиметрах, целое положительное число)
    weight - вес (в кг, целое положительное число)
    forces - запас сил (целое положительное число)
    physical_damage - физический урон (целое положительное число)
    armor - количество брони (целое положительное число)
    При создании экземпляра класса Warrior необходимо убедиться, что переданные в конструктор параметры удовлетворяют требованиям, иначе выбросить исключение ValueError с текстом 'Invalid value'.
    """

    def __init__(self, gender: str, age: int, height: int, weight: int, forces: int, physical_damage: int, armor: int):
        if not isinstance(forces, int) or forces <= 0:
            raise ValueError("Invalid value")
        if not isinstance(physical_damage, int) or physical_damage <= 0:
            raise ValueError("Invalid value")
        if not isinstance(armor, int) or armor <= 0:
            raise ValueError("Invalid value")
        super().__init__(gender, age, height, weight)
        self.forces = forces
        self.armor = armor
        self.physical_damage = physical_damage

    def __str__(self):
        return f"Warrior: Пол {self.gender}, возраст {self.age}, рост {self.height}, вес {self.weight}, запас сил {self.forces}, физический урон {self.physical_damage}, броня {self.armor}."

    def __eq__(self, other):
        """Метод возвращает True, если два объекта класса равны и False иначе. Два объекта типа Warrior равны, если равны их урон, запас сил и броня."""
        if self is other:
            return True
        if not isinstance(other, Warrior):
            raise TypeError
        return self.forces == other.forces and self.armor == other.armor and self.physical_damage == other.physical_damage


class Magician(Character):  # Наследуется от класса Character
    """Поля объекта класс Magician:
    gender - пол (значение может быть одной из строк: 'm', 'w')
    age - возраст (целое положительное число)
    height - рост (в сантиметрах, целое положительное число)
    weight - вес (в кг, целое положительное число)
    mana - запас маны (целое положительное число)
    magic_damage - магический урон (целое положительное число)
    При создании экземпляра класса Magician необходимо убедиться, что переданные в конструктор параметры удовлетворяют требованиям, иначе выбросить исключение ValueError с текстом 'Invalid value'.
    """

    def __init__(self, gender: str, age: int, height: int, weight: int, mana: int, magic_damage: int):
        if not isinstance(mana, int) or mana <= 0:
            raise ValueError("Invalid value")
        if not isinstance(magic_damage, int) or magic_damage <= 0:
            raise ValueError("Invalid value")
        super(Magician, self).__init__(gender, age, height, weight)
        self.mana = mana
        self.magic_damage = magic_damage

    def __str__(self):
        """Преобразование к строке вида: Magician: Пол <пол>, возраст <возраст>, рост <рост>, вес <вес>, запас маны <запас маны>, магический урон <магический урон>."""
        return f"Magician: Пол {self.gender}, возраст {self.age}, рост {self.height}, вес {self.weight}, запас маны {self.mana}, магический урон {self.magic_damage}."

    def __damage__(self):
        """Метод возвращает значение магического урона, который может нанести маг, если потратит сразу весь запас маны (умножение магического урона на запас маны)."""
        return self.magic_damage * self.mana


class Archer(Character):  # Наследуется от класса Character
    """Поля объекта класс Archer:
        gender - пол (значение может быть одной из строк: 'm', 'w')
        age - возраст (целое положительное число)
        height - рост (в сантиметрах, целое положительное число)
        weight - вес (в кг, целое положительное число)
        forces - запас сил (целое положительное число)
        physical_damage - физический урон (целое положительное число)
        attack_range - дальность атаки (целое положительное число)
        При создании экземпляра класса Archer необходимо убедиться, что переданные в конструктор параметры удовлетворяют требованиям, иначе выбросить исключение ValueError с текстом 'Invalid value'."""

    def __init__(self, gender: str, age: int, height: int, weight: int, forces: int, physical_damage: int,
                 attack_range: int):
        if not isinstance(forces, int) or forces <= 0:
            raise ValueError("Invalid value")
        if not isinstance(physical_damage, int) or physical_damage <= 0:
            raise ValueError("Invalid value")
        if not isinstance(attack_range, int) or attack_range <= 0:
            raise ValueError("Invalid value")
        super(Archer, self).__init__(gender, age, height, weight)
        self.forces = forces
        self.physical_damage = physical_damage
        self.attack_range = attack_range

    def __str__(self):
        """Преобразование к строке вида: Archer: Пол <пол>, возраст <возраст>, рост <рост>, вес <вес>, запас сил <запас сил>, физический урон <физический урон>, дальность атаки <дальность атаки>."""
        return f"Archer: Пол {self.gender}, возраст {self.age}, рост {self.height}, вес {self.weight}, запас сил {self.forces}, физический урон {self.physical_damage}, дальность атаки {self.attack_range}."

    def __eq__(self, other):
        """Метод возвращает True, если два объекта класса равны и False иначе. Два объекта типа Archer равны, если равны их урон, запас сил и дальность атаки."""
        if self is other:
            return True
        if not isinstance(other, Archer):
            raise TypeError
        return self.forces == other.forces and self.attack_range == other.attack_range and self.physical_damage == other.physical_damage


class WarriorList(list):  # список воинов - наследуется от класса list.
    def __init__(self, name: str, *args, **kwargs):
        super(WarriorList, self).__init__(*args, **kwargs)
        self.name = name

    def append(self, __object) -> None:
        if not isinstance(__object, Warrior):
            raise TypeError(f"Invalid error {type(__object)}")
        super(WarriorList, self).append(__object)

    def print_count(self):
        '''Использование метода count(). Вывести количество воинов.'''
        count = len(self)
        print(count)


class MagicianList(list):  # список магов - наследуется от класса list.
    def __init__(self, name: str, *args, **kwargs):
        super(MagicianList, self).__init__(*args, **kwargs)
        self.name = name

    def extend(self, __iterable) -> None:
        super(MagicianList, self).extend(x for x in __iterable if isinstance(x, Magician))

    def print_damage(self):
        damage = sum(hero.magic_damage for hero in self)
        print(damage)


class ArcherList(list):  # список лучников - наследуется от класса list.
    def __init__(self, name: str, *args, **kwargs):
        super(ArcherList, self).__init__(*args, **kwargs)
        self.name = name

    def append(self, __object) -> None:
        if not isinstance(__object, Archer):
            raise TypeError(f"Invalid error {type(__object)}")
        super(ArcherList, self).append(__object)

    def print_count(self):
        """Вывести количество лучников мужского пола."""
        count = sum(1 for x in self if x.gender == 'm')
        print(count)
