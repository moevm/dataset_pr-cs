class Node:
    def __init__(self, data, next=None):
        self.__data = data
        self.next = next

    def get_data(self):
        return self.__data

    def __str__(self):
        if self.next is not None:
            return f"data: {self.__data}, next: {(self.next).__data}"

        return f"data: {self.__data}, next: None"


class LinkedList:
    def __init__(self, head=None):
        self.head = head
        self.length = len(self)

    def __len__(self):
        length = 0
        head = self.head
        while head is not None:
            length += 1
            head = head.next

        return length

    def append(self, element):
        if self.length == 0:
            self.head = Node(element)
            self.length = 1
            return

        current = self.head
        while current.next is not None:
            current = current.next

        current.next = Node(element)
        self.length += 1

    def __str__(self):
        if self.length == 0:
            return "LinkedList[]"
        elif self.length == 1:
            if self.length == 1:
                return f'LinkedList[length = {self.length}, [data: {self.head.get_data()}, next: None]]'
        else:
            current = self.head
            result = f'data: {current.get_data()}, next: {current.next.get_data()}'
            current = current.next
            while current.next is not None:
                result = result + f'; data: {current.get_data()}, next: {current.next.get_data()}'
                current = current.next
            result = result + f'; data: {current.get_data()}, next: None'
            return f'LinkedList[length = {self.length}, [{result}]]'

    def pop(self):
        try:
            if self.length == 0:
                raise IndexError("LinkedList is empty!")
            if self.length == 1:
                self.head = None
            else:
                current = self.head
                while current.next.next is not None:
                    current = current.next
                current.next = None
            self.length -= 1
        except IndexError as error:
            return error

    def delete_on_start(self, n):
        try:
            if self.length < n or n < 1:
                raise KeyError("OK")
            if n == 1:
                self.head = self.head.next
            else:
                current = self.head
                for i in range(n - 2):
                    current = current.next
                current.next = current.next.next
            self.length -= 1
        except KeyError as error:
            raise KeyError

    def clear(self):
        self.head = None
        self.length = 0