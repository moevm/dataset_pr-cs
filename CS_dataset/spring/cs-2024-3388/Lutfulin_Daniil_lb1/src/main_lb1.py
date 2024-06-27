class Edition:

    def __init__(self, name, price, age_limit, style):
        self.name = name
        self.price = price
        self.age_limit = age_limit
        self.style = style
        if not (self.__fields_correct()):
            raise ValueError('Invalid value')

    def __fields_correct(self):
        return all((isinstance(self.name, str), isinstance(self.price, int),
                    self.price > 0, isinstance(self.age_limit, int),
                    self.age_limit > 0, self.style in ['c', 'b']))


class Book(Edition):

    def __init__(self, name, price, age_limit, style, author, hardcover, pages):
        super().__init__(name, price, age_limit, style)
        self.author = author
        self.hardcover = hardcover
        self.pages = pages
        if not (self.__fields_correct()):
            raise ValueError('Invalid value')

    def __fields_correct(self):
        return all((isinstance(self.author, str), isinstance(self.hardcover, bool),
                    isinstance(self.pages, int), self.pages > 0))

    def __str__(self):
        return f"Book: название {self.name}, цена {self.price}, возрастное ограничение {self.age_limit}, стиль {self.style}, автор {self.author}, твердый переплет {self.hardcover}, количество страниц {self.pages}."

    def __eq__(self, other):
        if not isinstance(other, Book):
            raise TypeError(f"'==' not supported between instances of 'Book' and '{type(other)}'")
        return (self.name == other.name and self.author == other.author)


class Newspaper(Edition):

    def __init__(self, name, price, age_limit, style, online_edition, country, frequency):
        super().__init__(name, price, age_limit, style)
        self.online_edition = online_edition
        self.country = country
        self.frequency = frequency
        if not (self.__fields_correct()):
            raise ValueError('Invalid value')

    def __fields_correct(self):
        return all((isinstance(self.online_edition, bool), isinstance(self.country, str),
                    isinstance(self.frequency, int), self.frequency > 0))

    def __str__(self):
        return f"Newspaper: название {self.name}, цена {self.price}, возрастное ограничение {self.age_limit}, стиль {self.style}, интернет издание {self.online_edition}, страна {self.country}, периодичность {self.frequency}."

    def __eq__(self, other):
        if not isinstance(other, Newspaper):
            raise TypeError(f"'==' not supported between instances of {type(self)} and '{type(other)}'")
        return (self.name == other.name and self.country == other.country)


class BookList(list):

    def __init__(self, name):
        super().__init__(self)
        self.name = name

    def append(self, p_object):
        if not isinstance(p_object, Book):
            raise TypeError(f'Invalid type {type(p_object)}')
        else:
            super().append(p_object)

    def total_pages(self):
        return sum([x.pages for x in self])

    def print_count(self):
        print(len(self))


class NewspaperList(list):

    def __init__(self, name):
        super().__init__(self)
        self.name = name

    def extend(self, iterable):
        for element in iterable:
            if isinstance(element, Newspaper):
                self.append(element)

    def print_age(self):
        print(min([x.age_limit for x in self]))

    def print_total_price(self):
        print(sum([x.price for x in self]))
