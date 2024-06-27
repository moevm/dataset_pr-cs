class Edition:
    def __init__(self, name, price, age_limit, style):
        if type(name) != str or type(price) != int or type(age_limit) != int or price <= 0 or age_limit <= 0 or (style != 'c' and style != 'b'):
            raise ValueError('Invalid value')
        self.name = name
        self.price = price
        self.age_limit = age_limit
        self.style = style

class Book(Edition):
    def __init__(self, name, price, age_limit, style, author, hardcover, pages):
        if type(author) != str or type(hardcover) != bool or type(pages) != int or pages <= 0:
            raise ValueError('Invalid value')
        super().__init__(name, price, age_limit, style)
        self.author = author
        self.hardcover = hardcover
        self.pages = pages
    def __str__(self):
        return f'Book: название {self.name}, цена {self.price}, возрастное ограничение {self.age_limit}, стиль {self.style}, автор {self.author}, твердый переплет {self.hardcover}, количество страниц {self.pages}.'

    def __eq__(self, other):
        return (self.name == other.name) and (self.author == other.author)


class Newspaper(Edition):
    def __init__(self, name, price, age_limit, style, online_edition, country, frequency):
        if type(online_edition) != bool or type(country) != str or type(frequency) != int or frequency <= 0:
            raise ValueError('Invalid value')
        super().__init__(name, price, age_limit, style)
        self.online_edition = online_edition
        self.country = country
        self.frequency = frequency

    def __str__(self):
        return f'Newspaper: название {self.name}, цена {self.price}, возрастное ограничение {self.age_limit}, стиль {self.style}, интернет издание {self.online_edition}, страна {self.country}, периодичность {self.frequency}.'

    def __eq__(self, other):
        return (self.name == other.name) and (self.country == other.country)


class BookList(list):
    def __init__(self, name):
        super().__init__()
        self.name = name

    def append(self, p_object):
        if isinstance(p_object,Book):
            super().append(p_object)
        else:
            raise TypeError('Invalid type <тип_объекта p_object> (результат вызова функции type)')

    def total_pages(self):
        return sum([book.pages for book in list(self)])

    def print_count(self):
        print(len(list(self)))


class NewspaperList(list):
    def __init__(self, name):
        super().__init__()
        self.name = name

    def extend(self, iterable):
        for i in iterable:
            if isinstance(i, Newspaper):
                super().append(i)

    def print_age(self):
        print(min([newspaper.age_limit for newspaper in list(self)]))

    def print_total_price(self):
        print(sum([newspaper.price for newspaper in list(self)]))