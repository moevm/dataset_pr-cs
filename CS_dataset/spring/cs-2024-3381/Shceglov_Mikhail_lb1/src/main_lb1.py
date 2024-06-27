class Edition:
    def __init__(self, name, price, age_limit, style):
        if not all([isinstance(name, str), isinstance(price, int) and price > 0, isinstance(age_limit, int) and age_limit > 0, isinstance(style, str) and style in ('c', 'b')]):
            raise ValueError('Invalid value')
        else:
            self.name = name
            self.price = price
            self.age_limit = age_limit
            self.style = style

class Book(Edition):
    def __init__(self, name, price, age_limit, style, author, hardcover, pages):
        if not all([isinstance(author, str), isinstance(hardcover, bool), isinstance(pages, int) and pages > 0]):
            raise ValueError('Invalid value')
        else:
            super().__init__(name, price, age_limit, style)
            self.author = author
            self.hardcover = hardcover
            self.pages = pages

    def __str__(self):
        return f'Book: название {self.name}, цена {self.price}, возрастное ограничение {self.age_limit}, стиль {self.style}, автор {self.author}, твердый переплет {self.hardcover}, количество страниц {self.pages}.'

    def __eq__(self, other):
        if self.name == other.name and self.author == other.author:
            return True
        return False

class Newspaper(Edition):
    def __init__(self, name, price, age_limit, style, online_edition, country, frequency):
        if not all([isinstance(online_edition, bool), isinstance(country, str), isinstance(frequency, int) and frequency > 0]):
            raise ValueError('Invalid value')
        else:
            super().__init__(name, price, age_limit, style) 
            self.online_edition = online_edition
            self.country = country
            self.frequency = frequency

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
        if not isinstance(p_object, Book):
            raise TypeError(f'Invalid type {type(p_object)}')
        else:
            super().append(p_object)

    def total_pages(self):
        return sum(book.pages for book in self)

    def print_count(self):
        print(len(self))

class NewspaperList(list):
    def __init__(self, name):
        super().__init__()
        self.name = name

    def extend(self, iterable):
        for item in iterable:
            if isinstance(item, Newspaper):
                super().append(item)

    def print_age(self):
        print(min(newspaper.age_limit for newspaper in self))

    def print_total_price(self):
        print(sum(newspaper.price for newspaper in self))