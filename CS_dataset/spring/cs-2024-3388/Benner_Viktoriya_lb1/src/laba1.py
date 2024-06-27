class Edition:
    def __init__(self, name, price, age_limit, style):
        if not isinstance(name, str):
            raise TypeError('Name should be a string')
        if not isinstance(price, int) or price <= 0:
            raise ValueError('Price should be a positive integer')
        if not isinstance(age_limit, int) or age_limit <= 0:
            raise ValueError('Age limit should be a positive integer')
        if style not in ("c", "b"):
            raise ValueError('Invalid style. Choose either "c" or "b"')
        
        self.name = name
        self.price = price
        self.age_limit = age_limit
        self.style = style


class Book(Edition):
    def __init__(self, name, price, age_limit, style, author, hardcover, pages):
        super().__init__(name, price, age_limit, style)
        self.author = author
        self.hardcover = hardcover
        self.pages = pages

        if type(self.author) is not str:
            raise ValueError('Invalid value')
        if type(self.hardcover) is not bool:
            raise ValueError('Invalid value')
        if type(self.pages) is not int or self.pages <= 0:
            raise ValueError('Invalid value')

    def __str__(self):
        return f"Book: название {self.name}, цена {self.price}, возрастное ограничение {self.age_limit}" \
               f", стиль {self.style}, автор {self.author}, твердый переплет {self.hardcover}," \
               f" количество страниц" \
               f" {self.pages}."

    def __eq__(self, other):
        return (self.author == other.author) and (self.name == other.name)


class Newspaper(Edition):  # Наследуется от класса Edition
    def __init__(self, name, price, age_limit, style, online_edition, country, frequency):
        super().__init__(name, price, age_limit, style)
        self.online_edition = online_edition
        self.country = country
        self.frequency = frequency

        if type(self.online_edition) is not bool:
            raise ValueError('Invalid value')
        if type(self.country) is not str:
            raise ValueError('Invalid value')
        if type(self.frequency) is not int or self.frequency <= 0:
            raise ValueError('Invalid value')

    def __str__(self):
        return f'Newspaper: название {self.name}, цена {self.price},' \
               f' возрастное ограничение {self.age_limit}, стиль {self.style},' \
               f' интернет издание {self.online_edition}, страна {self.country},' \
               f' периодичность {self.frequency}.'

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
            raise TypeError(f"Invalid type {type(p_object)}")

    def total_pages(self):
        res = 0
        for i in self:
            res += i.pages
        return res

    def print_count(self):
        print(len(self))


class NewspaperList(list):
    def __init__(self, name):
        super().__init__()
        self.name = name

    def extend(self, iterable):
        to_extend = filter(lambda x: isinstance(x, Newspaper), iterable)
        super().extend(to_extend)

    def print_age(self):
        print(min(i.age_limit for i in self))

    def print_total_price(self):
        res = 0
        for i in self:
            res += i.price
        print(res)