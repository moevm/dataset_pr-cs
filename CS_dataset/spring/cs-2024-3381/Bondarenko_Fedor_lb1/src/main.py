class Edition:
    def __init__(self, name, price, age_limit, style):
        if isinstance(name, str) and isinstance(price, int) and price > 0 and isinstance(age_limit, int) and age_limit > 0 and isinstance(style, str) and style in "cb":
            self.name = name
            self.price = price
            self.age_limit = age_limit
            self.style = style
        else:
            raise ValueError("Invalid value")

class Book(Edition):
    def __init__(self, name, price, age_limit, style, author, hardcover, pages):
        if isinstance(name, str) and isinstance(price, int) and price > 0 and isinstance(age_limit, int) and age_limit > 0 and isinstance(style, str) and style in "cb" and isinstance(author, str) and isinstance(hardcover, bool) and isinstance(pages, int) and pages > 0:
            super().__init__(name, price, age_limit, style)
            self.author = author
            self.hardcover = hardcover
            self.pages = pages
        else:
            raise ValueError("Invalid value")

    def __str__(self):
        return f"Book: название {self.name}, цена {self.price}, возрастное ограничение {self.age_limit}, стиль {self.style}, автор {self.author}, твердый переплет {self.hardcover}, количество страниц {self.pages}."

    def __eq__(self, other):
        if (self.name == other.name) and (self.author == other.author):
            return True
        return False

class Newspaper(Edition):
    def __init__(self, name, price, age_limit, style, online_edition, country, frequency):
        if isinstance(name, str) and isinstance(price, int) and price > 0 and isinstance(age_limit, int) and age_limit > 0 and isinstance(style, str) and style in "cb" and isinstance(online_edition, bool) and isinstance(country, str) and isinstance(frequency, int) and frequency > 0:
            super().__init__(name, price, age_limit, style)
            self.online_edition = online_edition
            self.country = country
            self.frequency = frequency
        else:
            raise ValueError("Invalid value")

    def __str__(self):
        return f"Newspaper: название {self.name}, цена {self.price}, возрастное ограничение {self.age_limit}, стиль {self.style}, интернет издание {self.online_edition}, страна {self.country}, периодичность {self.frequency}."

    def __eq__(self, other):
        if (self.name == other.name) and (self.country == other.country):
            return True
        return False
    
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
        pages = 0
        for book in self:
            pages += book.pages
        return pages

    def print_count(self):
        print(len(self))
        
class NewspaperList(list):
    def __init__(self, name):
        super().__init__()
        self.name = name

    def extend(self, iterable):
        for paper in iterable:
            if isinstance(paper, Newspaper):
                super().append(paper)

    def print_age(self):
        min_age = 10**100
        for paper in self:
            min_age = min(min_age, paper.age_limit)
        print(min_age)

    def print_total_price(self):
        price = 0
        for paper in self:
            price += paper.price
        print(price)