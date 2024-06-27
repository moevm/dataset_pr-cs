class Edition:
    @staticmethod
    def __validate_values(name, price, age_limit, style):
        return isinstance(name, str) and isinstance(price, int) and (price > 0) and isinstance(age_limit, int) and (age_limit > 0) and (style in ['c','b'])

    def __init__(self, name, price, age_limit, style):
        if not self.__validate_values(name, price, age_limit, style):
            raise ValueError('Invalid value')
        self.name = name
        self.price = price
        self.age_limit = age_limit
        self.style = style


class Book(Edition):
    @staticmethod
    def __validate_values(author, hardcover, pages):
        return isinstance(author, str) and isinstance(hardcover, bool) and isinstance(pages, int) and (pages > 0)

    def __init__(self, name, price, age_limit, style, author, hardcover, pages):
        super().__init__(name, price, age_limit, style)
        if not self.__validate_values(author, hardcover, pages):
            raise ValueError('Invalid value')
        self.author = author
        self.hardcover = hardcover
        self.pages = pages

    def __str__(self):
        return f'Book: название {self.name}, цена {self.price}, возрастное ограничение {self.age_limit}, стиль {self.style}, автор {self.author}, твердый переплет {self.hardcover}, количество страниц {self.pages}.'

    def __eq__(self, other):
        return isinstance(other, Book) and (self.name == other.name) and (self.author == other.author)


class Newspaper(Edition):
    @staticmethod
    def __validate_values(online_edition, country, frequency):
        return isinstance(online_edition, bool) and isinstance(country, str) and isinstance(frequency, int) and (frequency > 0)

    def __init__(self, name, price, age_limit, style, online_edition, country, frequency):
        super().__init__(name, price, age_limit, style)
        if not self.__validate_values(online_edition, country, frequency):
            raise ValueError('Invalid value')
        self.online_edition = online_edition
        self.country = country
        self.frequency = frequency

    def __str__(self):
        return f'Newspaper: название {self.name}, цена {self.price}, возрастное ограничение {self.age_limit}, стиль {self.style}, интернет издание {self.online_edition}, страна {self.country}, периодичность {self.frequency}.'

    def __eq__(self, other):
        return isinstance(other, Newspaper) and (self.name == other.name) and (self.country == other.country)


class BookList(list):
    def __init__(self, name):
        super().__init__()
        self.name = name

    def append(self, p_object):
        if not isinstance(p_object, Book):
            raise TypeError(f'Invalid type {type(p_object)}')
        super().append(p_object)

    def total_pages(self):
        return sum([book.pages for book in self])

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
        min_age_limit = min([newspaper.age_limit for newspaper in self])
        print(min_age_limit)

    def print_total_price(self):
        total_price = sum(newspaper.price for newspaper in self)
        print(total_price)