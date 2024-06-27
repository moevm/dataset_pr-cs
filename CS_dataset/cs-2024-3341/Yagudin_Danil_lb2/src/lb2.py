class Node:
    __data = None
    next = None
    def __init__(self, data, next = None):
        self.__data = data
        self.next = next

    def get_data(self):
        return self.__data

    def __str__(self):
        next_data = self.next.__data if self.next else None
        return f"data: {self.get_data()}, next: {next_data}"

node = Node(1)

class LinkedList:
    head = []
    length = 0
    def __init__(self, head = None):
        if head != None:
            self.head = head
            self.length += 1

    def __len__(self):
        return self.length

    def append(self, element):
        if self.head == []:
            self.head = Node(element)
        else:
            current = self.head
            while current.next:
                current = current.next
            current.next = Node(element)
        self.length += 1

    def __str__(self):
        if self.length == 0:
            return "LinkedList[]"
        str = f"LinkedList[length = {self.length}, [{self.head.__str__()}"
        current = self.head
        while current.next:
            current = current.next
            str += f"; {current.__str__()}"
        str += "]]"
        return str

    def pop(self):
        if self.length == 0:
            raise IndexError("LinkedList is empty!")
        if self.length == 1:
            self.head = []
            self.length = 0
            return
        counter = 1
        current = self.head
        while counter != self.length - 1:
            current = current.next
            counter += 1
        current.next = None
        self.length -= 1

    def delete_on_end(self, n):
        if self.length < n or n <= 0:
            raise KeyError("Element doesn't exist!")
        if self.length - n == 0:
            next_to_head = self.head.next
            self.head = next_to_head
            self.length -= 1
            return
        counter = 1
        current = self.head
        next_to_current = current.next
        while counter != self.length - n:
            current = next_to_current
            next_to_current = next_to_current.next
            counter += 1
        current.next = next_to_current.next
        self.length -= 1


    def clear(self):
        self.head = []
        self.length = 0

