allStr = lambda *iterable: all(map(lambda x: isinstance(x, str),iterable))
allBool = lambda *iterable: all(map(lambda x: isinstance(x,bool), iterable))
allNatural = lambda *iterable: all(map(lambda x: isinstance(x,int) and (x > 0), iterable))
class Edition:
    def __init__(self, name, price, age_limit, style):
        if allStr(name) and allNatural(price, age_limit) and (style in ['c','b']):
            self.name = name
            self.price = price
            self.age_limit = age_limit
            self.style = style
        else:
            raise ValueError('Invalid value')

class Book(Edition):
    def __init__(self, name, price, age_limit, style, author,hardcover, pages):
        super().__init__(name, price, age_limit, style)
        if allStr(author) and allBool(hardcover) and allNatural(pages):
            self.author = author
            self.hardcover = hardcover
            self.pages = pages
        else:
            raise ValueError('Invalid value')
    def __str__(self):
        return f'Book: название {self.name}, цена {self.price}, возрастное ограничение {self.age_limit}, стиль {self.style}, автор {self.author}, твердый переплет {self.hardcover}, количество страниц {self.pages}.'
    def __eq__(self, other):
        return (self.name == other.name) and (self.author == other.author)
class Newspaper(Edition):
    def __init__(self, name, price, age_limit, style,online_edition, country, frequency):
        super().__init__(name, price, age_limit, style)
        if allBool(online_edition) and allStr(country) and allNatural(frequency):
            self.online_edition = online_edition
            self.country = country
            self.frequency = frequency
        else:
            raise ValueError('Invalid value')
    def __str__(self):
        return f'Newspaper: название {self.name}, цена {self.price}, возрастное ограничение {self.age_limit}, стиль {self.style}, интернет издание {self.online_edition}, страна {self.country}, периодичность {self.frequency}.'
    def __eq__(self, other):
        return (self.name == other.name) and (self.country == other.country)

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
        return sum(map(lambda book: book.pages, self))
    def print_count(self):
        print(len(self))

class NewspaperList(list):
    def __init__(self, name):
        super().__init__()
        self.name = name
    def extend(self, iterable):
        super().extend(filter(lambda x: isinstance(x, Newspaper),iterable))
    def print_age(self):
        print(min(map(lambda newspaper: newspaper.age_limit,self)))
    def print_total_price(self):
        print(sum(map(lambda newspaper: newspaper.price, self)))