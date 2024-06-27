class Edition:
    def __init__(self, name: str, price: int, age_limit: int, style: str) -> None:
        if (
            type(name) is not str
            or type(price) is not int
            or type(age_limit) is not int
            or type(style) is not str
        ) or (  # sanity check
            price < 1
            or age_limit < 1
            or style not in ["c", "b"]
            or not name
            or not style
        ):
            raise ValueError("Invalid value")
        self.name = name
        self.price = price
        self.age_limit = age_limit
        self.style = style


class Book(Edition):
    def __init__(
        self,
        name: str,
        price: int,
        age_limit: int,
        style: str,
        author: str,
        hardcover: bool,
        pages: int,
    ) -> None:
        super().__init__(name, price, age_limit, style)
        if (
            type(author) is not str
            or type(hardcover) is not bool
            or type(pages) is not int
        ) or (  # sanity check
            not author or pages < 1
        ):
            raise ValueError("Invalid value")
        self.author = author
        self.hardcover = hardcover
        self.pages = pages

    def __str__(self):
        return f"Book: название {self.name}, цена {self.price}, возрастное ограничение {self.age_limit}, стиль {self.style}, автор {self.author}, твердый переплет {self.hardcover}, количество страниц {self.pages}."

    def __eq__(self, other):
        return (
            type(other) is Book
            and other.author == self.author
            and other.name == self.name
        )


class Newspaper(Edition):
    def __init__(
        self,
        name: str,
        price: int,
        age_limit: int,
        style: str,
        online_edition: bool,
        country: str,
        frequency: int,
    ) -> None:
        super().__init__(name, price, age_limit, style)
        if (
            type(online_edition) is not bool
            or type(country) is not str
            or type(frequency) is not int
        ) or (  # sanity check
            not country or frequency < 1
        ):
            raise ValueError("Invalid value")
        self.online_edition = online_edition
        self.country = country
        self.frequency = frequency

    def __str__(self):
        return f"Newspaper: название {self.name}, цена {self.price}, возрастное ограничение {self.age_limit}, стиль {self.style}, интернет издание {self.online_edition}, страна {self.country}, периодичность {self.frequency}."

    def __eq__(self, other):
        return (
            type(other) is Newspaper
            and other.name == self.name
            and other.country == self.country
        )


class BookList(list):
    def __init__(self, name) -> None:
        super().__init__()
        self.name = name

    def append(self, p_object):
        if type(p_object) is not Book:
            raise TypeError(f"Invalid type {type(p_object)}")
        super().append(p_object)

    def total_pages(self):
        return sum(map(lambda x: x.pages, self))

    def print_count(self):
        print(len(self))


class NewspaperList(list):
    def __init__(self, name) -> None:
        super().__init__()
        self.name = name

    def extend(self, iterable):
        super().extend(filter(lambda x: type(x) is Newspaper, iterable))

    def print_age(self):
        print(min(map(lambda x: x.age_limit, self)))

    def print_total_price(self):
        print(sum(map(lambda x: x.price, self)))
