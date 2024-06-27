class Node():
    __data = 0
    next = None
    
    def __init__(self, data, next=None):
        self.__data = data
        self.next = next
        
    def get_data(self):
        return self.__data
    
    def change_data(self, new_data):
        self.__data = new_data
        
    def __str__(self):
        return f'data: {self.__data}, next: {self.next.__data if self.next else None}'


class LinkedList():
    head = Node(None)
    length = 0
    
    def __init__(self, head=None):
        self.head = head
        self.length = 1 if head else 0
        
    def __len__(self):
        return self.length
    
    def append(self, element):
        if len(self) == 0:
            self.head = Node(element)
            self.length = 1
            return
        tmp = self.head
        while tmp.next:
            tmp = tmp.next
        tmp.next = Node(element)
        self.length += 1
        
    def __str__(self):
        if len(self) == 0:
            return 'LinkedList[]'
        else:
            res = ''
            tmp = self.head
            while tmp:
                res += str(tmp) + '; '
                tmp = tmp.next
            return f'LinkedList[length = {len(self)}, [{res[:-2]}]]'
        
    def pop(self):
        if len(self) == 0:
            raise IndexError('LinkedList is empty!')
        if len(self) == 1:
            res = self.head
            self.head = None
            self.length = 0
            return res
        prev = self.head
        tmp = self.head.next
        while tmp.next:
            prev = tmp
            tmp = tmp.next
        res = tmp
        tmp = None
        prev.next = None
        self.length -= 1
        return res
    
    def clear(self):
        while len(self) != 0:
            self.pop()
            
    def change_on_end(self, n, new_data):
        if len(self) < n:
            raise KeyError('Element doesn\'t exist!')
        if n <= 0:
            raise KeyError('n is smaller than 0')
        i = 0
        tmp = self.head
        while i != self.length - n:
            tmp = tmp.next
            i += 1
        tmp.change_data(new_data)