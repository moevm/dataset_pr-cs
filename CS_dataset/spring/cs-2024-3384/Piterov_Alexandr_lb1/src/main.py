class Edition:
    
    def __init__(self, name, price, age_limit, style):
        self.name = name
        self.price = price
        self.age_limit = age_limit
        self.style = style
        
        if \
            not isinstance(name,      str) or \
            not isinstance(price,     int) or price     <= 0 or \
            not isinstance(age_limit, int) or age_limit <= 0 or \
            not isinstance(style,     str) or style not in 'cb':
            raise ValueError('Invalid value')
    
    
class Book(Edition):
    
    def __init__(self, name, price, age_limit, style, author, hardcover, pages):
        
        self.author = author
        self.hardcover = hardcover
        self.pages = pages
        
        super().__init__(name, price, age_limit, style)
        
        if \
            not isinstance(author,    str)  or \
            not isinstance(hardcover, bool) or \
            not isinstance(pages,     int)  or pages <= 0:
            raise ValueError('Invalid value')
    
    
    def __str__(self): 
        return f'Book: название {self.name}, цена {self.price}, возрастное ограничение {self.age_limit}, стиль {self.style}, автор {self.author}, твердый переплет {self.hardcover}, количество страниц {self.pages}.'
    
    
    def __eq__(self, other): 
        if self.name == other.name and self.author == other.author:
            return True
        return False


class Newspaper(Edition):
    
    def __init__(self, name, price, age_limit, style, online_edition, country, frequency):
        
        self.online_edition = online_edition
        self.country = country
        self.frequency = frequency
        
        super().__init__(name, price, age_limit, style)
        
        if \
            not isinstance(online_edition, bool) or \
            not isinstance(country,        str)  or \
            not isinstance(frequency,      int)  or frequency <= 0:
            raise ValueError('Invalid value')
        
    
    def __str__(self): 
        return f'Newspaper: название {self.name}, цена {self.price}, возрастное ограничение {self.age_limit}, стиль {self.style}, интернет издание {self.online_edition}, страна {self.country}, периодичность {self.frequency}.'
        
        
    def __eq__(self, other): 
        if self.name == other.name and self.country == other.country:
            return True
        return False
    
    
class BookList(list):
    def __init__(self, name):
        super().__init__()
        
        self.name = name
        
            
    def append(self, p_object): 
        if isinstance(p_object, Book):
            super().append(p_object)
        else:
            raise TypeError(f'Invalid type {type(p_object)}')


    def total_pages(self): 
        return sum([b.pages for b in self])
        
        
    def print_count(self): 
        print(len(self))
        
        
class NewspaperList(list):

    def __init__(self, name):
        super().__init__()
        
        self.name = name
        
           
    def extend(self, iterable): 
        for i in iterable:
            if isinstance(i, Newspaper):
                super().append(i)


    def print_age(self): 
        m = min([n.age_limit for n in self])
        print(m)
        
        
    def print_total_price(self): 
        s = sum([n.price for n in self])
        print(s)
    

