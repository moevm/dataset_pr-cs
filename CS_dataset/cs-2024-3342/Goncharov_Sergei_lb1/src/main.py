class Edition:
    def __init__(self, name, price, age_limit, style):
    
        if isinstance(name, str) and (isinstance(price, int) and price > 0) and (isinstance(age_limit, int) and age_limit > 0) and isinstance(style, str) and (style == 'c' or style == 'b'):
            self.name = name
            self.price = price
            self.age_limit = age_limit    
            self.style = style
        else:
            raise ValueError("Invalid value")
            
    
class Book(Edition):
    def __init__(self, name, price, age_limit, style, author, hardcover, pages):
        super().__init__(name, price, age_limit, style)
        
        if isinstance(author, str) and isinstance(hardcover, bool) and (isinstance(pages, int) and pages > 0):
            self.author = author
            self.hardcover = hardcover
            self.pages = pages
        else:
            raise ValueError("Invalid value")


    def __str__(self): 
        return f'Book: название {self.name}, цена {self.price}, возрастное ограничение {self.age_limit}, стиль {self.style}, автор {self.author}, твердый переплет {self.hardcover}, количество страниц {self.pages}.'
       
    def __eq__(self, other):
        return self.name == other.name and self.author == other.author

class Newspaper(Edition):
    
    def __init__(self, name, price, age_limit, style, online_edition, country, frequency):
        super().__init__(name, price, age_limit, style)
        if isinstance(online_edition, bool) and isinstance(country, str) and (isinstance(frequency, int) and frequency > 0):
            self.online_edition = online_edition
            self.country = country
            self.frequency = frequency
        else:
            raise ValueError("Invalid value")
    
    def __str__(self): 
        return f'Newspaper: название {self.name}, цена {self.price}, возрастное ограничение {self.age_limit}, стиль {self.style}, интернет издание {self.online_edition}, страна {self.country}, периодичность {self.frequency}.'
    
    def __eq__(self, other):
        return self.name == other.name and self.country == other.country
        
class BookList(list):
    def __init__(self, name):
        super().__init__()
        self.name = name

    def append(self, p_object):
        try:
            if isinstance(p_object, Book):
                super().append(p_object)
            else:
                raise TypeError
        except TypeError:
            raise TypeError(f'Invalid type {type(p_object)}')

    def total_pages(self):
        return sum(i.pages for i in self)

    def print_count(self):
        print(len(self))

class NewspaperList(list):
    def __init__(self, name):
        super().__init__()
        self.name = name

    def extend(self, iterable):
        super().extend([i for i in iterable if isinstance(i, Newspaper)])

    def print_age(self):
        print(min(i.age_limit for i in self))

    def print_total_price(self):
        print(sum(i.price for i in self))