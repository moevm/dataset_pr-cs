class PositiveInt:
    @classmethod
    def verify_num(cls, num):
        if not (isinstance(num, int) and num > 0):
            raise ValueError("Invalid value")

    def __set_name__(self, owner, name):
        self.name = "_" + name

    def __get__(self, instance, owner):
        return getattr(instance, self.name)

    def __set__(self, instance, value):
        self.verify_num(value)
        setattr(instance, self.name, value)


class NotNegativeInt(PositiveInt):
    @classmethod
    def verify_num(cls, num):
        if not (isinstance(num, int) and num >= 0):
            raise ValueError("Invalid value")


class Gender:
    @classmethod
    def verify_gender(cls, gender):
        if gender not in ('m', 'w'):
            raise ValueError("Invalid value")

    def __set_name__(self, owner, name):
        self.name = "_" + name

    def __get__(self, instance, owner):
        return getattr(instance, self.name)

    def __set__(self, instance, value):
        self.verify_gender(value)
        setattr(instance, self.name, value)


class Character:
    gender = Gender()
    age = PositiveInt()
    height = PositiveInt()
    weight = PositiveInt()
    fields_to_print = {'_gender': "Пол ", '_age': "возраст ", '_height': "рост ", '_weight': "вес ",
                       '_forces': "запас сил ", '_physical_damage': "физический урон ", '_armor': "броня ",
                       '_attack_range': "дальность атаки ", '_mana': "запас маны ", '_magic_damage': "магический урон "}

    def __init__(self, gender, age, height, weight):
        self.gender = gender
        self.age = age
        self.height = height
        self.weight = weight

    def __str__(self):
        return f"{type(self).__name__}: " + f"{', '.join([self.fields_to_print[k] + str(v) for k, v in self.__dict__.items() if k in self.fields_to_print])}."


class Warrior(Character):
    forces = PositiveInt()
    physical_damage = PositiveInt()
    armor = PositiveInt()

    def __init__(self, gender, age, height, weight, forces, physical_damage, armor):
        super().__init__(gender, age, height, weight)
        self.forces = forces
        self.physical_damage = physical_damage
        self.armor = armor

    def __eq__(self, other):
        return self.forces == other.forces and self.physical_damage == other.physical_damage and self.armor == other.armor


class Magician(Character):
    mana = PositiveInt()
    magic_damage = PositiveInt()

    def __init__(self, gender, age, height, weight, mana, magic_damage):
        super().__init__(gender, age, height, weight)
        self.mana = mana
        self.magic_damage = magic_damage

    def __damage__(self):
        return self.magic_damage * self.mana


class Archer(Character):
    forces = PositiveInt()
    physical_damage = PositiveInt()
    attack_range = PositiveInt()

    def __init__(self, gender, age, height, weight, forces, physical_damage, attack_range):
        super().__init__(gender, age, height, weight)
        self.forces = forces
        self.physical_damage = physical_damage
        self.attack_range = attack_range

    def __eq__(self, other):
        return self.forces == other.forces and self.physical_damage == other.physical_damage and \
            self.attack_range == other.attack_range


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
        super().extend([item for item in iterable if isinstance(item, Magician)])

    def print_damage(self):
        print(sum([magician.magic_damage for magician in self]))


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
        print(len([archer for archer in self if archer.gender == 'm']))
