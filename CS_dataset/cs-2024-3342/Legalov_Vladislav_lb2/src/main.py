class Node:
    def __init__(self, data, next=None):
        self.__data = data
        self.next = next

    def get_data(self):
        return self.__data
        
    def change_data(self, new_data):
        self.__data = new_data

    def __str__(self):
        if self.next is None:
            return f'data: {self.__data}, next: None'
        return f'data: {self.__data}, next: {self.next.get_data()}'

class LinkedList:
    def __init__(self, head = None):
        if head is None:
            self.head = None
            self.length = 0
        else:
            self.head = Node(head)
            self.length = 1

    def __len__(self):
        return self.length

    def append(self, element):
        if self.head is None:
            self.head = Node(element)
            self.length = 1
            return None
        current = self.head
        while current.next is not None:
            current = current.next
        current.next = Node(element)
        self.length += 1

    def __str__(self):
        elementslist = []
        element = self.head
        while element is not None:
            elementslist.append(str(element))
            element = element.next
        res = "LinkedList["
        if self.length > 0:
            res = res + f"length = {self.length}, [" + "; ".join(elementslist) + "]"
        return res + "]"
        
    def pop(self):
        if self.length == 0:
            raise IndexError("LinkedList is empty!")
        if self.length == 1:
            self.head = None
            self.length = 0
            return None
        element = self.head
        while element.next.next is not None:
            element = element.next
        element.next = None
        self.length -= 1

    def change_on_start(self, n, new_data):
        if self.length < n or n <= 0:
            raise KeyError("Element doesn't exist!")
        element = self.head
        for i in range(n-1):
            element = element.next
        element.change_data(new_data)

    def clear(self):
        self.head = None
        self.length = 0
