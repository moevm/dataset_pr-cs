class Edition:
    def __init__(self, name, price, age_limit, style):
        if not isinstance(name, str): raise ValueError('Invalid value')
        if not isinstance(price, int) or price <= 0: raise ValueError('Invalid value')
        if not isinstance(age_limit, int) or age_limit <= 0: raise ValueError('Invalid value')
        if style not in ('c', 'b'): raise ValueError('Invalid value')
        self.name = name
        self.price = price
        self.age_limit = age_limit
        self.style = style
    
    
class Book(Edition):
    def __init__(self, name, price, age_limit, style, author, hardcover, pages):
        super().__init__(name, price, age_limit, style)
        if not isinstance(author, str): raise ValueError('Invalid value')
        if not isinstance(hardcover, bool): raise ValueError('Invalid value')
        if ((not isinstance(pages, int)) or (pages <= 0)): raise ValueError('Invalid value')
        self.author = author
        self.hardcover = hardcover
        self.pages = pages
    
    
    def __str__(self):
        return f'Book: название {self.name}, цена {self.price}, возрастное ограничение {self.age_limit}, стиль {self.style}, автор {self.author}, твердый переплет {self.hardcover}, количество страниц {self.pages}.'
    '''Преобразование к строке вида: Book: название <название>, цена <цена>, возрастное ограничение <возрастное ограничение>, стиль <стиль>, автор <автор>, твердый переплет <твердый переплет>, количество страниц <количество страниц>.'''
    
    def __eq__(self, item):
        return isinstance(item,Book) and (self.name == item.name and self.author == item.author)
    '''Метод возвращает True, если два объекта класса равны и False иначе. Два объекта типа Book равны, если равны их название и автор.'''

class Newspaper(Edition): #Наследуется от класса Edition
    def __init__(self, name, price, age_limit, style, online_edition, country, frequency):
        super().__init__(name, price, age_limit, style)
        if not isinstance(online_edition, bool): raise ValueError('Invalid value')
        if not isinstance(country, str): raise ValueError('Invalid value')
        if not isinstance(frequency, int) or frequency <= 0: raise ValueError('Invalid value')
        self.online_edition = online_edition
        self.country = country
        self.frequency = frequency
    
    
    def __str__(self):
        return f'Newspaper: название {self.name}, цена {self.price}, возрастное ограничение {self.age_limit}, стиль {self.style}, интернет издание {self.online_edition}, страна {self.country}, периодичность {self.frequency}.'
    '''Преобразование к строке вида: Newspaper: название <название>, цена <цена>, возрастное ограничение <возрастное ограничение>, стиль <стиль>, интернет издание <интернет издание>, страна <страна>, периодичность <периодичность>.'''
    
    def __eq__(self,other):
         return isinstance(other, Newspaper) and self.name == other.name and self.country == other.country
    '''Метод возвращает True, если два объекта класса равны и False иначе. Два объекта типа Newspaper равны, если равны их название и страна.'''
    
    
class BookList(list): #– список книг - наследуется от класса list.
    def __init__(self, name):
        super().__init__()
        self.name = name
        '''1. Вызвать конструктор базового класса.
            2. Передать в конструктор строку name и присвоить её полю name созданного объекта'''
            
    def append(self, p_object):
        if not isinstance(p_object, Book): raise TypeError(f'Invalid type {type(p_object)}')
        super().append(p_object)
        '''Переопределение метода append() списка. В случае, если p_object - книга, элемент добавляется в список, иначе выбрасывается исключение TypeError с текстом: Invalid type <тип_объекта p_object> (результат вызова функции type)'''

    def total_pages(self):
        return (sum([book.pages for book in self]))
        '''Метод возвращает сумму всех страниц всех имеющихся книг.'''
        
    def print_count(self):
        print(int(len(self)))
        '''Вывести количество книг.'''
        
class NewspaperList(list): #– список газет - наследуется от класса list.
    def __init__(self, name):
        super().__init__()
        self.name = name
        '''1. Вызвать конструктор базового класса.
           2. Передать в конструктор строку name и присвоить её полю name созданного объекта'''
           
    def extend(self,iterable):
        for item in iterable:
            if isinstance(item,Newspaper):
                super().append(item)
        '''Переопределение метода extend() списка. В случае, если элемент iterable - объект класса Newspaper, этот элемент добавляется в список, иначе не добавляется.'''

    def print_age(self):
        print(int(min(Newspaper.age_limit for Newspaper in self)))
        '''Вывести самое низкое возрастное ограничение среди всех газет.'''
        
    def print_total_price(self):
        print(int(sum(Newspaper.price for Newspaper in self)))
        '''Посчитать и вывести общую цену всех газет.'''