class Edition:
    def __init__(self, n, p, a, s):
        if isinstance(n,str) and isinstance(p,int) and p > 0 and isinstance(a,int) and a > 0 and isinstance(s,str) and s in "cb":
            self.name = n
            self.price = p
            self.age_limit = a
            self.style = s
        else:
            raise ValueError("Invalid value")
class Book(Edition): 
    def __init__(self, n, p, a, s, au, h, pa):
        if isinstance(n,str) and isinstance(p,int) and p > 0 and isinstance(a,int) and a > 0 and isinstance(s,str) and s in "cb" and isinstance(au, str) and isinstance(h,bool) and isinstance(pa,int) and pa > 0:
            super().__init__(n,p,a,s)
            self.author = au
            self.hardcover = h
            self.pages = pa
        else:
            raise ValueError("Invalid value")
    def __str__(self):
        return f"Book: название {self.name}, цена {self.price}, возрастное ограничение {self.age_limit}, стиль {self.style}, автор {self.author}, твердый переплет {self.hardcover}, количество страниц {self.pages}." 
    def __eq__(self, other):
        return (self.name == other.name) and (self.author == other.author)

class Newspaper(Edition): 
    def __init__(self, n, p, a, s, o, c, f):
        if isinstance(n,str) and isinstance(p,int) and p > 0 and isinstance(a,int) and a > 0 and isinstance(s,str) and s in "cb" and isinstance(o, bool) and isinstance(c,str) and isinstance(f,int) and f > 0:
            super().__init__(n,p,a,s)
            self.online_edition = o
            self.country = c
            self.frequency = f
        else:
            raise ValueError("Invalid value")
    def __str__(self):
        return f"Newspaper: название {self.name}, цена {self.price}, возрастное ограничение {self.age_limit}, стиль {self.style}, интернет издание {self.online_edition}, страна {self.country}, периодичность {self.frequency}."
    def __eq__(self, other):
        return (self.name == other.name) and (self.country == other.country)
    
class BookList(list):
    def __init__(self, name):
        super().__init__()
        self.name = name
    def append(self, p_object):
        if isinstance(p_object,Book):
            super().append(p_object)
        else:
            raise TypeError(f"Invalid type {type(p_object)}")
    def total_pages(self):
        ans = 0
        for book in self:
            ans += book.pages
        return ans   
    def print_count(self):
        print(len(self))
        
class NewspaperList(list):
    def __init__(self, name):
        super().__init__()
        self.name = name
    def extend(self, iterable):
        for item in iterable:
            if isinstance(item, Newspaper):
                super().append(item)
    def print_age(self):
        ans = int(1e9)
        for np in self:
            ans = min(ans,np.age_limit)
        print(ans)
    def print_total_price(self):
        ans = 0
        for np in self:
            ans += np.price
        print(ans)