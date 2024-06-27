class Edition:
    def __init__(self,name,price,age_limit,style):
        if not all([isinstance(name,str), isinstance(price,int),price > 0, isinstance(age_limit, int),age_limit > 0,style in ["c","b"]]):
            raise ValueError("Invalid value")
        self.name = name
        self.price = price
        self.age_limit = age_limit
        self.style = style
    
class Book(Edition): 
    def __init__(self, name, price, age_limit, style, author, hardcover, pages):
        super().__init__(name,price,age_limit,style)
        if not all([isinstance(author,str), isinstance(hardcover,bool),isinstance(pages,int),pages > 0]):
            raise ValueError("Invalid value")
        self.author = author
        self.hardcover = hardcover
        self.pages = pages
    def __str__(self):
        return f"Book: название {self.name}, цена {self.price}, возрастное ограничение {self.age_limit}, стиль {self.style}, автор {self.author}, твердый переплет {self.hardcover}, количество страниц {self.pages}."
    
    def __eq__(self,other):
        if all([self.name == other.name,self.author == other.author]): 
            return True
        return False

class Newspaper(Edition):
    def __init__(self, name, price, age_limit, style, online_edition, country, frequency):
        super().__init__(name, price, age_limit, style)
        if not all([isinstance(online_edition, bool), isinstance(country,str), isinstance(frequency, int), frequency > 0]):
            raise ValueError("Invalid value")
        self.online_edition = online_edition
        self.country = country
        self.frequency = frequency
    
    def __str__(self):
        return f"Newspaper: название {self.name}, цена {self.price}, возрастное ограничение {self.age_limit}, стиль {self.style}, интернет издание {self.online_edition}, страна {self.country}, периодичность {self.frequency}." 
    
    def __eq__(self, other): 
        if all([self.name == other.name, self.country == other.country]): 
            return True
        return False
    
class BookList(list):
    def __init__(self, name):
        super().__init__(self)
        self.name = name   

    def append(self, p_object): 
        if isinstance(p_object,Book):
            super().append(p_object)
        else:
            raise TypeError(f"Invalid type {type(p_object)}")
        
    def total_pages(self):
        return sum(item.pages for item in self)
        
    def print_count(self):
        print(len(self))
        
class NewspaperList(list):
    def __init__(self, name):
        super().__init__(self)
        self.name = name
           
    def extend(self, iterable):
        if all(isinstance(item,Newspaper) for item in iterable):
            super().extend(iterable)

    def print_age(self):
        min_age_limit = min(newspaper.age_limit for newspaper in self)
        print(min_age_limit)

    def print_total_price(self):
        all_price = sum(newspaper.price for newspaper in self)
        print(all_price)