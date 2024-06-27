class Edition:
    def __init__(self, name, price, age_limit, style):
        if (isinstance(name, str)) and (isinstance(price, int)) and (price > 0)\
                and (isinstance(age_limit, int)) and age_limit > 0 and (style in ("c", "b")):
            self.name = name
            self.price = price
            self.age_limit = age_limit
            self.style = style
        else:
            raise ValueError("Invalid value")


class Book(Edition):
    def __init__(self, name, price, age_limit, style, author, hardcover, pages):
        super().__init__(name, price, age_limit, style)
        if (isinstance(author, str)) and (isinstance(hardcover, bool)) and (isinstance(pages, int)) and (pages > 0):
            self.author = author
            self.hardcover = hardcover
            self.pages = pages
        else:
            raise ValueError("Invalid value")

    def __str__(self):
        return f'Book: название {self.name}, ' \
               f'цена {self.price}, ' \
               f'возрастное ограничение {self.age_limit}, ' \
               f'стиль {self.style}, ' \
               f'автор {self.author}, ' \
               f'твердый переплет {self.hardcover}, ' \
               f'количество страниц {self.pages}.'

    def __eq__(self, other):
        return (self.name == other.name) and (self.author == other.author)


class Newspaper(Edition):
    def __init__(self, name, price, age_limit, style, online_edition, country, frequency):
        super().__init__(name, price, age_limit, style)
        if (isinstance(online_edition, bool)) and (isinstance(country, str))\
                and (isinstance(frequency, int)) and (frequency > 0):
            self.online_edition = online_edition
            self.country = country
            self.frequency = frequency
        else:
            raise ValueError("Invalid value")

    def __str__(self):
        return f'Newspaper: название {self.name}, ' \
               f'цена {self.price}, ' \
               f'возрастное ограничение {self.age_limit}, ' \
               f'стиль {self.style}, ' \
               f'интернет издание {self.online_edition}, ' \
               f'страна {self.country}, ' \
               f'периодичность {self.frequency}.'

    def __eq__(self, other):
        return (self.name == other.name) and (self.country == other.country)


class BookList(list):
    def __init__(self, name):
        super().__init__()
        self.name = name

    def append(self, p_object):
        if not isinstance(p_object, Book):
            raise TypeError(f"Invalid type {type(p_object)}")
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
        super().extend(list(filter(lambda item: True if isinstance(item, Newspaper) else False, iterable)))

    def print_age(self):
        print(min(item.age_limit for item in self))

    def print_total_price(self):
        print(sum(item.price for item in self))