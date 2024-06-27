class Node:
    def __init__(self, data, next=None):
        self._data = data
        self.next = next

    def get_data(self):
        if(self != None):
            return self._data

    def change_data(self, new_data):
        self._data = new_data

    def __str__(self):
        return f'data: {self._data}, next: {Node.get_data(self.next)}'

class LinkedList:

    def __init__(self, head=None):
        if head == None:
            self.length = 0
            self.head = None
        else:
            self.length = 1
            self.head = Node(head)
    def __len__(self):
        return self.length

    def append(self, element):
        if self.head == None:
            self.head = Node(element)
            self.length += 1
        else:
            current = self.head
            while current.next != None:
                current = current.next
            current.next = Node(element)
            self.length += 1
    def __str__(self):
        if self.length == 0:
            return "LinkedList[]"
        else:
            a = self.head
            s = f"LinkedList[length = {self.length}, ["
            while a.next != None:
                s += str(a) + "; "
                a = a.next
            s += str(a) + "]]"
            return s

    def pop(self):
        if self.length == 0:
            raise IndexError("LinkedList is empty!")
        a = self.head
        b = a
        while a.next != None:
            b= a
            a = a.next
        if self.length > 1:
            b.next = None
        else:
            self.head = None
        self.length -= 1

    def change_on_start(self, n, new_data):
        if self.length < n or n <= 0:
            raise KeyError("Element doesn't exist!")
        else:
            a = self.head
            while n !=1:
                a = a.next
                n -= 1
            Node.change_data(a, new_data)

    def clear(self):
        a = self.head
        while a.next != None:
            b = a
            a = a.next
            b = None
        self.length = 0