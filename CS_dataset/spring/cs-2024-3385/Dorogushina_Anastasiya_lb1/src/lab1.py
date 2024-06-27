class Edition:
    def __init__(self, name, price, age_limit, style):
        if (isinstance(name, str) and isinstance(price, int) and (price > 0) and 
        isinstance(age_limit, int) and (age_limit > 0) and (style in ['c', 'b'])):
            self.name = name                    # name - название (строка)
            self.price = price                  # price - цена (в руб., целое положительное число)
            self.age_limit = age_limit          # age_limit - возрастное ограничение (целое положительное число)
            self.style = style                  # style - стиль(значение может быть одной из строк: c (color), b(black))
        else:
            raise ValueError('Invalid value')


class Book(Edition):  # Наследуется от класса Edition
    def __init__(self, name, price, age_limit, style, author, hardcover, pages):
        super().__init__(name, price, age_limit, style)         # name, price, age_limit, style из Edition
        if isinstance(author, str) and isinstance(hardcover, bool) and isinstance(pages, int) and (pages > 0):
            self.author = author                                # author - автор (фамилия, в виде строки)
            self.hardcover = hardcover                          # hardcover - твердый переплет (True или False)
            self.pages = pages                                  # pages - количество страниц (целое положительное число)
        else:
            raise ValueError('Invalid value')

    def __str__(self):
        return (f'Book: название {self.name}, цена {self.price}, возрастное ограничение {self.age_limit}, стиль {self.style}, '
                f'автор {self.author}, твердый переплет {self.hardcover}, количество страниц {self.pages}.')

    def __eq__(self, other):
        return self.name == other.name and self.author == other.author          #названия и авторы


class Newspaper(Edition):  # Наследуется от класса Edition
    def __init__(self, name, price, age_limit, style, online_edition, country, frequency):
        super().__init__(name, price, age_limit, style)         # name, price, age_limit, style из Edition
        if isinstance(online_edition, bool) and isinstance(country, str) and isinstance(frequency, int) and (frequency > 0):
            self.online_edition = online_edition                # online_edition - интернет издание (True или False)
            self.country = country                              # country - страна (строка)
            self.frequency = frequency                          # frequency - периодичность (в днях, целое пол число)
        else:
            raise ValueError('Invalid value')

    def __str__(self):
        return (f'Newspaper: название {self.name}, цена {self.price}, возрастное ограничение {self.age_limit}, стиль {self.style}, '
                f'интернет издание {self.online_edition}, страна {self.country}, периодичность {self.frequency}.')

    def __eq__(self, other):
        return self.name == other.name and self.country == other.country        #названия и страны


class BookList(list):  # список книг - наследуется от класса list
    def __init__(self, name):
        super().__init__()      # Вызвать конструктор базового класса
        self.name = name        # Передать в конструктор строку name и присвоить её полю name созданного объекта

    def append(self, p_object):                 # Переопределение метода append() списка
        if isinstance(p_object, Book):          # В случае, если p_object - книга, элемент добавляется в список
            super().append(p_object)            # Иначе выбрасывается исключение TypeError с текстом
        else:
            raise TypeError(f'Invalid type {type(p_object)}')

    def total_pages(self):
        sum_pages = 0
        for book in self:
            sum_pages += book.pages
        return sum_pages        # Сумма всех страниц всех имеющихся книг

    def print_count(self):
        print(len(self))        # Количество книг


class NewspaperList(list):      # Список газет - наследуется от класса list.
    def __init__(self, name):
        super().__init__()      # Вызвать конструктор базового класса
        self.name = name        # Передать в конструктор строку name и присвоить её полю name созданного объекта

    def extend(self, iterable):                 # Переопределение метода extend() списка
        if all(isinstance(x, Newspaper) for x in iterable):
            super().extend(iterable)

    def print_age(self):
        min_age = self[0].age_limit
        for newspaper in self:
            if min_age > newspaper.age_limit:
                min_age = newspaper.age_limit
        print(min_age)          # Самое низкое возрастное ограничение среди всех газет

    def print_total_price(self):
        sum_price = 0
        for newspaper in self:
            sum_price += newspaper.price
        print(sum_price)        # Общая цена всех газет
