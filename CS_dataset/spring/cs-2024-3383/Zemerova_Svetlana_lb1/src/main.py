class Transport:
    def __init__(self, average_speed, max_speed, price, cargo, color):
        if (isinstance(average_speed, int) and average_speed>0):
            self.average_speed=average_speed
        else: raise ValueError('Invalid value')
        if (isinstance(max_speed, int) and max_speed>0):
            self.max_speed=max_speed
        else: raise ValueError('Invalid value')
        if (isinstance(price, int) and price>0):
            self.price=price
        else: raise ValueError('Invalid value')
        if (isinstance(cargo, bool)):
            self.cargo=cargo
        else: raise ValueError('Invalid value')
        if (color=='w' or color=='g' or color=='b'):
            self.color=color
        else: raise ValueError('Invalid value')

    def __initList__(self,name):
        self.name=name


class Car(Transport):
    def __init__(self, average_speed, max_speed, price, cargo, color, power, wheels):
        super().__init__(average_speed, max_speed, price, cargo, color)
        if (isinstance(power, int) and power>0):
            self.power=power
        else: raise ValueError('Invalid value')
        if (isinstance(wheels,int) and wheels>0 and wheels<=10):
            self.wheels=wheels
        else: raise ValueError('Invalid value')

    def __str__(self): 
        return (f'Car: средняя скорость {self.average_speed}, максимальная скорость {self.max_speed}, цена {self.price}, грузовой {self.cargo}, цвет {self.color}, мощность {self.power}, количество колес {self.wheels}.')

    def __add__(self): 
        return self.average_speed+self.max_speed

    def __eq__(self,other):
        if other.__class__==Car:
            if (self.wheels==other.wheels and self.average_speed==other.average_speed and self.max_speed==other.max_speed and self.power==other.power):
                return True
        return False   


class Plane(Transport):
    def __init__(self, average_speed, max_speed, price, cargo, color, load_capacity, wingspan):
        super().__init__(average_speed, max_speed, price, cargo, color)
        if (isinstance(load_capacity, int) and load_capacity>0):
            self.load_capacity=load_capacity
        else: raise ValueError('Invalid value')
        if (isinstance(wingspan,int) and wingspan>0):
            self.wingspan=wingspan
        else: raise ValueError('Invalid value')

    def __str__(self): 
        return f"Plane: средняя скорость {self.average_speed}, максимальная скорость {self.max_speed}, цена {self.price}, грузовой {self.cargo}, цвет {self.color}, грузоподъемность {self.load_capacity}, размах крыльев {self.wingspan}."
    
    def __add__(self): 
        return self.average_speed+self.max_speed
    
    def __eq__(self,other): 
        if other.__class__==Plane:
            if self.wingspan==other.wingspan:
                return True
        return False

  
class Ship(Transport):
    def __init__(self, average_speed, max_speed, price, cargo, color, length, side_height):
        super().__init__(average_speed, max_speed, price, cargo, color)
        if (isinstance(length, int) and length>0):
            self.length=length
        else: raise ValueError('Invalid value')
        if (isinstance(side_height,int) and side_height>0):
            self.side_height=side_height
        else: raise ValueError('Invalid value')
    
    def __str__(self):
        return f"Ship: средняя скорость {self.average_speed}, максимальная скорость {self.max_speed}, цена {self.price}, грузовой {self.cargo}, цвет {self.color}, длина {self.length}, высота борта {self.side_height}."
    
    def __add__(self): 
        return self.average_speed+self.max_speed
    
    def __eq__(self,other): 
        if other.__class__==Ship:
            if self.length==other.length and self.side_height==other.side_height:
                return True
        return False


class CarList(Transport,list):
    def __init__(self, name):
        super().__initList__(name)
           
    def append(self,p_object): 
        if p_object.__class__==Car:
            super().append(p_object)
        else:
            raise TypeError(f"Invalid type {type(p_object)}")
        
    def print_colors(self): 
        st=''
        for i in range(len(self)):
            st+=f"{i+1} автомобиль: {self[i].color}\n"
        st=st[:len(st)-1]
        print (st)
            
    def print_count(self): 
        print (len(self))

               
class PlaneList(Transport,list):
    def __init__(self, name):
        super().__initList__(name)

    def extend(self,iterable):
        for pln in iterable:
            if pln.__class__==Plane:
                super().append(pln)
        
    def print_colors(self):
        st=''
        for i in range(len(self)):
            st+=f"{i+1} самолет: {self[i].color}\n"
        st=st[:len(st)-1]
        print(st)
        
    def total_speed(self): 
        speed=0
        for i in range(len(self)):
            speed+=self[i].average_speed
        print(speed)

       
class ShipList(Transport,list):
    def __init__(self,name):
        super().__initList__(name)

    def append(self,p_object): 
        if p_object.__class__==Ship:
            super().append(p_object)
        else:
            raise TypeError(f"Invalid type {type(p_object)}")
        
    def print_colors(self): 
        st=''
        for i in range(len(self)):
            st+=f"{i+1} корабль: {self[i].color}\n"
        st=st[:len(st)-1]
        print(st)
            
    def print_ship(self):
        st=''
        for i in range(len(self)):
            if self[i].length>150:
                st+=f"Длина корабля №{i+1} больше 150 метров\n"
        st=st[:len(st)-1]
        print(st)
