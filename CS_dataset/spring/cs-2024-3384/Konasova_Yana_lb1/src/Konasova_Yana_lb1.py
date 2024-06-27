class Transport:
    def __init__(self, average_speed, max_speed, price, cargo, color):

        if not isinstance(average_speed, int) or average_speed <= 0:
            raise ValueError("Invalid value")
        else:
            self.average_speed=average_speed
        if not isinstance(max_speed, int) or max_speed <= 0:
            raise ValueError("Invalid value")
        else:
            self.max_speed=max_speed
        if not isinstance(price, int) or price <= 0:
            raise ValueError("Invalid value")
        else:
            self.price=price
        if not isinstance(cargo, bool) or cargo < 0:
            raise ValueError("Invalid value")
        else:
            self.cargo=cargo
        if color not in ['w', 'g', 'b']:
            raise ValueError("Invalid value")
        else:
            self.color = color
    
class Car(Transport):
    def __init__(self, average_speed, max_speed, price, cargo, color, power, wheels):
        super().__init__(average_speed, max_speed, price, cargo, color)
        if not isinstance(power, int) or power <= 0:
            raise ValueError("Invalid value")
        else:
            self.power=power
        if not isinstance(wheels, int) or wheels <= 0 or wheels>10:
            raise ValueError("Invalid value")
        else:
            self.wheels=wheels
    def __str__(self):
        return "Car: средняя скорость " + str(self.average_speed) + ", максимальная скорость "+str(self.max_speed)+ ", цена " + str(self.price)+ ", грузовой "+ str(self.cargo) + ", цвет " +str(self.color) + ", мощность "+str(self.power)+ ", количество колес " + str(self.wheels)+"."
    def __add__(self):
        return self.average_speed+self.max_speed
    def __eq__(self, other):
        if (self.wheels==other.wheels)and (self.average_speed==other.average_speed) and (self.max_speed==other.max_speed) and (self.power==other.power):
            return True
        return False

class Plane(Transport):
    def __init__(self, average_speed, max_speed, price, cargo, color, load_capacity, wingspan):
        super().__init__(average_speed, max_speed, price, cargo, color)
        if not isinstance(load_capacity, int) or load_capacity<= 0:
            raise ValueError("Invalid value")
        else:
            self.load_capacity=load_capacity
        if not isinstance(wingspan, int) or wingspan <= 0 :
            raise ValueError("Invalid value")
        else:
            self.wingspan=wingspan

    def __str__(self):
        return "Plane: средняя скорость " + str(self.average_speed) + ", максимальная скорость " + str(self.max_speed) + ", цена " + str(self.price) + ", грузовой " + str(self.cargo) + ", цвет " + str(self.color) + ", грузоподъемность " + str(self.load_capacity) + ", размах крыльев " + str(self.wingspan) + "."

    def __add__(self):
        return self.average_speed+self.max_speed
    def __eq__(self, other):
        if (self.wingspan==other.wingspan):
            return True
        return False
 
 
class Ship(Transport):
    def __init__(self, average_speed, max_speed, price, cargo, color, length, side_height):
        super().__init__(average_speed, max_speed, price, cargo, color)
        if not isinstance(length, int) or length <= 0:
            raise ValueError("Invalid value")
        else:
            self.length = length
        if not isinstance(side_height, int) or side_height <= 0 :
            raise ValueError("Invalid value")
        else:
            self.side_height = side_height

    def __str__(self):
        return "Ship: средняя скорость " + str(self.average_speed) + ", максимальная скорость " + str(self.max_speed) + ", цена " + str(self.price) + ", грузовой " + str(self.cargo) + ", цвет " + str(self.color) + ", длина " + str(self.length) + ", высота борта " + str(
            self.side_height) + "."
    def __add__(self):
        return self.average_speed+self.max_speed
    def __eq__(self, other):
        if (self.length==other.length) and(self.side_height==other.side_height):
            return True
        return False
 
class CarList(list):
    def __init__(self, name):
        super().__init__()
        self.name=name
    def append(self, p_object):
        if (isinstance(p_object, Car)):
            super().append(p_object)
        else:
            raise TypeError("Invalid type"+ type(p_object))

    def print_colors(self):
        for i in range (len(self)):
            print(str(i+1)+" автомобиль: "+ str(self[i].color))
    def print_count(self):
        print(len(self))
        
class PlaneList(list):
    def __init__(self, name):
        super().__init__()
        self.name=name

    def extend(self,iterable):
        for i in iterable:
            if (isinstance(i, Plane)):
                super().append(i)
    def print_colors(self):
        for i in range(len(self)):
            print(str(i+1)+' самолет: '+ str(self[i].color))
    def total_speed(self):
        k=0
        for i in range(len(self)):
            k+=self[i].average_speed
        print(k)
        
class ShipList(list):
    def __init__(self, name):
        super().__init__()
        self.name=name
    def append(self, p_object):
        if (isinstance(p_object, Ship)):
            super().append(p_object)
        else:
            raise TypeError("Invalid type" + type(p_object))
    def print_colors(self):
        for i in range(len(self)):
            print(str(i+1)+' корабль: '+ str(self[i].color))
    def print_ship(self):
        for i in range(len(self)):
            if self[i].length>150:
                print("Длина корабля №" + str(i+1)+ " больше 150 метров")


