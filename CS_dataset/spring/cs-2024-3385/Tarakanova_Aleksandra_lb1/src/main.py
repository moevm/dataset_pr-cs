class Edition:
    def __init__(self, name, price, age_limit, style):
        if not (isinstance(name, str) and isinstance(price, int) and price > 0 and
                (style == 'c' or style == 'b') and isinstance(age_limit, int) and age_limit > 0):
            raise ValueError('Invalid value')

        self.name = name
        self.price = price
        self.age_limit = age_limit
        self.style = style


class Book(Edition):
    def __init__(self, name, price, age_limit, style, author, hardcover, pages):
        super().__init__(name, price, age_limit, style)
        if not (isinstance(author, str) and isinstance(hardcover, bool) and isinstance(pages, int) and pages > 0):
            raise ValueError('Invalid value')

        self.author = author
        self.hardcover = hardcover
        self.pages = pages

    def __str__(self):
        return f'Book: название {self.name}, ' \
               f'цена {self.price}, ' \
               f'возрастное ограничение {self.age_limit}, ' \
               f'стиль {self.style}, ' \
               f'автор {self.author}, ' \
               f'твердый переплет {self.hardcover}, ' \
               f'количество страниц {self.pages}.'

    def __eq__(self, other):
        return self.author == other.author and self.name == other.name

class Newspaper(Edition):
    def __init__(self, name, price, age_limit, style, online_edition, country, frequency):
        super().__init__(name, price, age_limit, style)
        if not (isinstance(online_edition, bool) and isinstance(country, str) and
                isinstance(frequency, int) and frequency > 0):
            raise ValueError('Invalid value')

        self.online_edition = online_edition
        self.country = country
        self.frequency = frequency

    def __str__(self):
        return f'Newspaper: название {self.name}, ' \
               f'цена {self.price}, ' \
               f'возрастное ограничение {self.age_limit}, ' \
               f'стиль {self.style}, ' \
               f'интернет издание {self.online_edition}, ' \
               f'страна {self.country}, ' \
               f'периодичность {self.frequency}.'

    def __eq__(self, other):
        return self.name == other.name and self.country == other.country


class BookList(list):
    def __init__(self, name):
        super().__init__()
        self.name = name

    def append(self, p_object):
        if not isinstance(p_object, Book):
            raise TypeError(f'Invalid type {type(p_object)}')
        super().append(p_object)

    def total_pages(self):
        return sum(map(lambda x: x.pages, self))

    def print_count(self):
        print(len(self))


class NewspaperList(list):
    def __init__(self, name):
        super().__init__()
        self.name = name

    def extend(self, iterable):
        iterable = filter(lambda np: isinstance(np, Newspaper), iterable)
        super().extend(iterable)

    def print_age(self):
        print(min(map(lambda x: x.age_limit, self)))

    def print_total_price(self):
        print(sum(map(lambda x: x.price, self)))
