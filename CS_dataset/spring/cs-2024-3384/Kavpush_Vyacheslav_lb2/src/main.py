class Node:
    def __init__(self, data, next=None):
        self.__data = data
        self.next = next

    def get_data(self):
        return self.__data
        
    def change_data(self, new_data):
        self.__data = new_data

    def __str__(self):
        return f"data: {self.__data}, next: {self.next.__data if self.next else None}"


class LinkedList:
    def __init__(self, head = None):
        self.__head__ = head
        self.length = 0 if head is None else 1

    def __len__(self):
        return self.length

    def append(self, element):
        head = self.__head__
        if head is None:
            self.__head__ = Node(element)
        else:
            while head.next:
                head = head.next
            head.next = Node(element)
        self.length += 1
            
    def __str__(self):
        if self.length == 0:
            return "LinkedList[]"
        elem = self.__head__
        str = f"LinkedList[length = {self.length}, ["
        while elem is not None:
            if elem.next is not None:
                str += elem.__str__() + "; "
            else:
                str += elem.__str__()
            elem = elem.next
        str += ']]'
        return str

    def pop(self):
        if self.length == 0:
            raise (IndexError('LinkedList is empty!'))
        elif self.length == 1:
            self.__head__ = None
        else:
            elem = self.__head__
            while elem.next.next is not None:
                elem = elem.next
            elem.next = None
        self.length -= 1
    
    def clear(self):
        self.length = 0
        self.__head__ = None

    def change_on_end(self, n, new_data):
        if (n <= 0) or (self.length < n):
            raise(KeyError("Element doesn't exist!"))
        i = 0
        elem = self.__head__
        while i < self.length - n:
            elem = elem.next
            i += 1
        elem.change_data(new_data)