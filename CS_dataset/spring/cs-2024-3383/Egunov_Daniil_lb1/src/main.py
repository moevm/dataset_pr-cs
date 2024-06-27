from typing import Literal, List, Callable


class TypedDescriptor:
    def __init__(self, expected_type: type, *checks: Callable) -> None:
        """
        Initializes an instance of the TypedDescriptor class.

        :param expected_type: The expected type for the attribute.
        :param checks: Optional custom checks to validate the attribute.
        """
        self._expected_type = expected_type
        self._checks = checks

    def __set_name__(self, owner: type, name: str) -> None:
        """
        Sets the name of the descriptor.

        :param owner: The owner class of the descriptor.
        :param name: The name of the attribute.
        """
        self._name = '_' + name

    def __get__(self, instance: object, owner: type) -> object:
        """
        Gets the attribute value from the instance.

        :param instance: The instance of the owner class.
        :param owner: The owner class of the descriptor.

        :return: The value of the attribute.
        """
        return getattr(instance, self._name)

    def __set__(self, instance: object, value: object) -> None:
        """
        Sets the attribute value after validation.

        :param instance: The instance of the owner class.
        :param value: The owner class of the descriptor.

        :raises ValueError: When the value do not meet the requirements.
        """
        if (not isinstance(value, self._expected_type) or
                (self._checks and not all(check(value) for check in self._checks))):
            raise ValueError("Invalid value")
        setattr(instance, self._name, value)


class StringDescriptor(TypedDescriptor):
    """
    Descriptor for string attributes.
    """

    def __init__(self) -> None:
        """
        Initializes an instance of the StringDescriptor class.
        """
        super().__init__(str)


class NaturalDescriptor(TypedDescriptor):
    """
    Descriptor for natural number attributes.
    """

    def __init__(self) -> None:
        """
        Initializes an instance of the NaturalDescriptor class.
        """
        super().__init__(int, lambda x: x > 0)


class BooleanDescriptor(TypedDescriptor):
    """
    Descriptor for boolean attributes.
    """

    def __init__(self) -> None:
        """
        Initializes an instance of the BooleanDescriptor class.
        """
        super().__init__(bool)


class StyleDescriptor(TypedDescriptor):
    """
    Descriptor for style attributes.
    """

    def __init__(self) -> None:
        """
        Initializes an instance of the StyleDescriptor class.
        """
        super().__init__(str, lambda x: x in ['c', 'b'])


class Edition:
    name: str = StringDescriptor()
    price: int = NaturalDescriptor()
    age_limit: int = NaturalDescriptor()
    style: str = StyleDescriptor()

    def __init__(self, name: str, price: int, age_limit: int, style: str) -> None:
        """
        Initializes an instance of the Edition class.

        :param name: The name of the edition.
        :param price: The price of the edition.
        :param age_limit: The age limit for the edition.
        :param style: The style of the edition.
        """
        self.name = name
        self.price = price
        self.age_limit = age_limit
        self.style = style


class Book(Edition):
    author: str = StringDescriptor()
    hardcover: bool = BooleanDescriptor()
    pages: int = NaturalDescriptor()

    def __init__(self, name: str, price: int, age_limit: int, style: Literal['c', 'b'],
                 author: str, hardcover: bool, pages: int) -> None:
        """
        Initializes an instance of the Book class.

        :param name: The title of the book (string).
        :param price: The price of the book (in rubles, positive integer).
        :param age_limit: The age limit of the book (in years, positive integer).
        :param style: The style of the book (can be either 'c' for color or 'b' for black).
        :param author: The author of the book (surname, as a string).
        :param hardcover: The type of cover of the book (True for hardcover, False for other).
        :param pages: The number of pages in the book (positive integer).

        :raises ValueError: When the parameters passed to the constructor do not meet the requirements.
        """
        super().__init__(name, price, age_limit, style)
        self.author = author
        self.hardcover = hardcover
        self.pages = pages

    def __str__(self) -> str:
        """
        Returns a string representation of the book.

        :return: A string representing the book in the format:
                 Book: название <название>, цена <цена>,
                 возрастное ограничение <возрастное ограничение>, стиль <стиль>,
                 автор <автор>, твердый переплет <твердый переплет>,
                 количество страниц <количество страниц>.
        """
        return (f"Book: название {self.name}, "
                f"цена {self.price}, "
                f"возрастное ограничение {self.age_limit}, "
                f"стиль {self.style}, "
                f"автор {self.author}, "
                f"твердый переплет {self.hardcover}, "
                f"количество страниц {self.pages}.")

    def __eq__(self, other) -> bool:
        """
        Checks if two books are equal.
        To be equal to each other, books must have the same name and author.

        :param other: A book for comparison.

        :return: True if they are the same, otherwise false.
        """
        if not isinstance(other, Book):
            return False
        return self.name == other.name and self.author == other.author


class Newspaper(Edition):
    online_edition: bool = BooleanDescriptor()
    country: str = StringDescriptor()
    frequency: int = NaturalDescriptor()

    def __init__(self, name: str, price: int, age_limit: int, style: Literal['c', 'b'],
                 online_edition: bool, country: str, frequency: int) -> None:
        """
        Initializes an instance of the Newspaper class.

        :param name: The name of the newspaper (string).
        :param price: The price of the newspaper (in rubles, positive integer).
        :param age_limit: The age limit for the newspaper (in years, positive integer).
        :param style: The style of the newspaper (can be either 'c' for color or 'b' for black).
        :param online_edition: Whether the newspaper has an online edition (True or False).
        :param country: The country of origin for the newspaper (string).
        :param frequency: The frequency of publication (period between issues in days, positive integer).

        :raises ValueError: When the parameters passed to the constructor do not meet the requirements.
        """
        super().__init__(name, price, age_limit, style)
        self.online_edition = online_edition
        self.country = country
        self.frequency = frequency

    def __str__(self) -> str:
        """
        Returns a string representation of the newspaper.

        :return: A string representing the newspaper in the format:
                 Newspaper: название <название>, цена <цена>,
                 возрастное ограничение <возрастное ограничение>, стиль <стиль>,
                 интернет издание <интернет издание>, страна <страна>,
                 периодичность <периодичность>.
        """
        return (f"Newspaper: название {self.name}, "
                f"цена {self.price}, "
                f"возрастное ограничение {self.age_limit}, "
                f"стиль {self.style}, "
                f"интернет издание {self.online_edition}, "
                f"страна {self.country}, "
                f"периодичность {self.frequency}.")

    def __eq__(self, other) -> bool:
        """
        Checks if two newspapers are equal.

        :param other: A newspaper for comparison.
        To be equal to each other, newspapers must have the same name and country.

        :return: True if they are the same, otherwise false.
        """
        if not isinstance(other, Newspaper):
            return False
        return self.name == other.name and self.country == other.country


class BookList(list):
    def __init__(self, name: str) -> None:
        """
        Initializes an instance of the BookList class.

        :param name: The name of the list of the books (string).

        :raises ValueError: When the parameters passed to the constructor do not meet the requirements.
        """
        super().__init__()
        self._name = name

    def append(self, __object: Book) -> None:
        """
        Appends a book to the list of books.

        :param __object: The book to be appended.

        :raises TypeError: If the passed object is not of the Book type.
        """
        if not isinstance(__object, Book):
            raise TypeError(f"Invalid type {type(__object)}")
        super().append(__object)

    def total_pages(self) -> int:
        """
        Returns the total number of pages of all books in the list.

        :return: The sum of pages of all the books in the list.
        """
        return sum(book.pages for book in self)

    def print_count(self) -> None:
        """
        Prints the number of books.

        :return: The number of books in the list.
        """
        print(len(self))


class NewspaperList(list):
    def __init__(self, name: str) -> None:
        """
        Initializes an instance of the NewspaperList class.

        :param name: The name of the list of newspapers (string).

        :raises ValueError: When the parameters passed to the constructor do not meet the requirements.
        """
        super().__init__()
        self._name = name

    def extend(self, __iterable: List[Newspaper]) -> None:
        """
        If an element in the iterable is an object of the Newspaper class,
        that element is added to the list, otherwise it is not added.

        :param __iterable: The iterable containing objects to extend the list with.
        """
        super().extend(filter(lambda x: isinstance(x, Newspaper), __iterable))

    def print_age(self) -> None:
        """
        Prints the lowest age limit among all newspapers in the list.
        """
        print(min(newspaper.age_limit for newspaper in self))

    def print_total_price(self) -> None:
        """
        Prints the total cost of all newspapers in the list.
        """
        print(sum(newspaper.price for newspaper in self))

