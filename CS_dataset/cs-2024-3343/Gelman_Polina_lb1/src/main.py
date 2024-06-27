class Edition:
    def __init__(self, name, price, age_limit, style):
        if not isinstance(name, str) or not isinstance(price, int) or \
                not isinstance(age_limit, int) or not isinstance(style, str):
            raise ValueError('Invalid value')

        if price <= 0 or age_limit <= 0 or style not in ['c', 'b']:
            raise ValueError('Invalid value')

        self.name = name
        self.price = price
        self.age_limit = age_limit
        self.style = style


class Book(Edition):
    def __init__(self, name, price, age_limit, style, author, hardcover, pages):
        super().__init__(name, price, age_limit, style)
        if not isinstance(author, str) or not isinstance(hardcover, bool) or not isinstance(pages, int):
            raise ValueError('Invalid value')
        if pages <= 0:
            raise ValueError('Invalid value')
        self.author = author
        self.hardcover = hardcover
        self.pages = pages

    def __str__(self):
        return (f"Book: название {self.name}, цена {self.price}, возрастное ограничение {self.age_limit}, стиль {self.style}, автор {self.author}, твердый переплет {self.hardcover}, количество страниц {self.pages}.")
    def __eq__(self, other):
        return self.name == other.name and self.author == other.author


class Newspaper(Edition):
    def __init__(self, name, price, age_limit, style, online_edition, country, frequency):
        super().__init__(name, price, age_limit, style)
        if not isinstance(online_edition, bool) or not isinstance(country, str) or not isinstance(frequency, int):
            raise ValueError('Invalid value')
        if frequency <= 0:
            raise ValueError('Invalid value')
        self.online_edition = online_edition
        self.country = country
        self.frequency = frequency

    def __str__(self):
        return (f"Newspaper: название {self.name}, цена {self.price}, возрастное ограничение {self.age_limit}, стиль {self.style}, интернет издание {self.online_edition}, страна {self.country}, периодичность {self.frequency}.")

    def __eq__(self, other):
        return self.name == other.name and self.country == other.country
    #


class BookList(list):
    def __init__(self, name):
        super().__init__()
        self.name = name

    def append(self, p_object):
        if isinstance(p_object, Book):
            super().append(p_object)
        else:
            raise TypeError(f"Invalid type {type(p_object)}")

    def total_pages(self):
        total = 0
        for book in self:
            total += book.pages
        return total

    def print_count(self):
        print(len(self))


class NewspaperList(list):
    def __init__(self, name):
        super().__init__()
        self.name = name

    def extend(self,iterable):
        for i in iterable:
            if isinstance(i, Newspaper):
                super().append(i)

    def print_age(self):
        ages = [newspaper.age_limit for newspaper in self]
        if ages:
            min_age = min(ages)
        print(min_age)

    def print_total_price(self):
        cost = 0
        for newspaper in self:
            cost += newspaper.price
        print(cost)
