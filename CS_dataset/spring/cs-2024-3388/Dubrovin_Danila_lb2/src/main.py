class Node:
    def __init__(self, data, next=None):
        self.__data = data
        self.next = next

    def get_data(self):
        return self.__data

    def change_data(self, new_data):
        self.__data = new_data

    def __str__(self):
        next_data = "None" if self.next is None else self.next.get_data()
        return f"data: {self.get_data()}, next: {next_data}"


class LinkedList:
    def __init__(self, head=None):
        self.head = head
        self.length = 0 if head is None else 1

    def __len__(self):
        counter = 0
        current = self.head
        while current:
            counter += 1
            current = current.next
        self.length = counter
        return counter

    def append(self, element):
        new_node = Node(element)
        if not self.head:
            self.head = new_node
            return 1
        current = self.head
        while current.next:
            current = current.next
        current.next = new_node
        self.length += 1

    def __str__(self):
        if self.__len__() == 0:
            return "LinkedList[]"
        str_format = f"LinkedList[length = {self.length}, ["
        current = self.head
        while current.next is not None:
            str_format += f"data: {current.get_data()}, next: {current.next.get_data()}; "
            current = current.next
        str_format += f"data: {current.get_data()}, next: {current.next}]]"
        return str_format

    def pop(self):
        if self.__len__() == 0:
            raise IndexError("LinkedList is empty!")
        if self.head.next is None:
            self.head = None
            return
        current = self.head
        while current.next.next:
            current = current.next
        current.next = None
        self.length -= 1

    def change_on_start(self, n, new_data):
        if n > self.length or n < 1:
            raise KeyError("Element doesn't exist!")
        counter = 1
        current = self.head
        while counter < n:
            current = current.next
            counter += 1
        current.change_data(new_data)

    def clear(self):
        self.head = None
