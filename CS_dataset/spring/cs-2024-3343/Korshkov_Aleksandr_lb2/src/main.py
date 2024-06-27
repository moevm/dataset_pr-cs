class Node:
    def __init__(self, data, next=None):
        self.__data = data
        self.next = next

    def get_data(self):
        return self.__data

    def __str__(self):
        if self.next is None:
            return f"data: {self.__data}, next: None"
        return f"data: {self.__data}, next: {self.next.get_data()}"


class LinkedList:
    def __init__(self, head=None):
        self.head = head
        self.length = 0

    def __len__(self):
        return self.length

    def append(self, element):
        new = Node(element)
        if self.head is None:
            self.head = new
            self.length += 1
            return
        current = self.head
        while current.next:
            current = current.next
        current.next = new
        self.length += 1

    def __str__(self):
        if self.length == 0:
            return "LinkedList[]"
        res = ""
        current = self.head
        while current.next:
            res += f"data: {current.get_data()}, next: {current.next.get_data()}; "
            current = current.next
        res += f"data: {current.get_data()}, next: None"
        return f"LinkedList[length = {self.length}, [{res}]]"

    def pop(self):
        if self.head is None:
            raise IndexError("LinkedList is empty!")
        if self.length == 1:
            self.head = None
            self.length -= 1
            return
        current = self.head
        while current.next.next:
            current = current.next
        current.next = None
        self.length -= 1

    def delete_on_end(self, n):
        if n <= 0 or self.length < n:
            raise KeyError("Element doesn't exist!")
        current = self.head
        end = self.length - n
        position = 0
        if position == end:
            self.head = self.head.next
            self.length -= 1
            return
        while current is not None and position + 1 != end:
            position = position + 1
            current = current.next
        if current is not None:
            current.next = current.next.next
        self.length -= 1

    def clear(self):
        self.head = None
        self.length = 0

