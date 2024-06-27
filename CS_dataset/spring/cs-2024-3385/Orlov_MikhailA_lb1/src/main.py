class Edition:
	def __init__(self, name, price, age_limit, style):
		if isinstance(name, str) and isinstance(price, int) and (price > 0) and \
			isinstance(age_limit, int) and (age_limit > 0) and (style == "c" or style == "b"):
				self.name = name
				self.price = price
				self.age_limit = age_limit
				self.style = style
		else:
			raise ValueError("Invalid value")


class Book(Edition):
	def __init__(self, name, price, age_limit, style, author, hardcover, pages):
		super().__init__(name, price, age_limit, style)
		if isinstance(author, str) and isinstance(hardcover, bool) and isinstance(pages, int) and (pages > 0):
			self.author = author
			self.hardcover = hardcover
			self.pages = pages
		else:
			raise ValueError('Invalid value')

	def __str__(self):
		return F"Book: название {self.name}, " \
			   F"цена {self.price}, " \
			   F"возрастное ограничение {self.age_limit}, " \
			   F"стиль {self.style}, " \
			   F"автор {self.author}, " \
			   F"твердый переплет {self.hardcover}, " \
			   F"количество страниц {self.pages}."

	def __eq__(self, other):
		return self.author == other.author and self.name == other.name


class Newspaper(Edition):
	def __init__(self, name, price, age_limit, style, online_edition, country, frequency):
		super().__init__(name, price, age_limit, style)
		if isinstance(online_edition, bool) and isinstance(country, str) and isinstance(frequency, int) and (frequency > 0):
			self.online_edition = online_edition
			self.country = country
			self.frequency = frequency
		else:
			raise ValueError('Invalid value')

	def __str__(self):
		return F"Newspaper: название {self.name}, " \
			   F"цена {self.price}, " \
			   F"возрастное ограничение {self.age_limit}, " \
			   F"стиль {self.style}, " \
			   F"интернет издание {self.online_edition}, " \
			   F"страна {self.country}, " \
			   F"периодичность {self.frequency}."

	def __eq__(self, other):
		return self.name == other.name and self.country == other.country


class BookList(list):
	def __init__(self, name):
		super().__init__()
		self.name = name

	def append(self, __object):
		if not isinstance(__object, Book):
			raise TypeError(F"Invalid type {type(__object)}")
		super().append(__object)

	def total_pages(self):
		return sum(map(lambda b: b.pages, self))

	def print_count(self): print(self.__len__())


class NewspaperList(list):
	def __init__(self, name):
		super().__init__()
		self.name = name

	def extend(self, __iterable):
		super().extend(filter(lambda n: isinstance(n, Newspaper), __iterable))

	def print_age(self):
		print(min(map(lambda n: n.age_limit, self)))

	def print_total_price(self):
		print(sum(map(lambda n: n.price, self)))