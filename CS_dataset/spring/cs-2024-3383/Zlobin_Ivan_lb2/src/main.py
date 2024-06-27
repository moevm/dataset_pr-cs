class Node:
    def __init__(self, data, next=None):
        self.__data = data
        self.next = next

    def get_data(self):
        return self.__data

    def change_data(self, new_data):
        self.__data = new_data

    def __str__(self):
        return f'data: {self.__data}, next: {self.next.get_data() if self.next is not None else self.next}'


class LinkedList:
    def __init__(self, head=None):
        if head is None:
            self.length = 0
        else:
            self.length = 1
        self.head = head

    def __len__(self):
        return self.length

    def append(self, element):
        new_element = Node(element)
        if self.head is None:
            self.head = new_element
        else:
            tmp = self.head
            while tmp.next is not None:
                tmp = tmp.next
            tmp.next = new_element
        self.length += 1

    def __str__(self):
        if self.length == 0:
            return "LinkedList[]"
        else:
            s = f'LinkedList[length = {self.length}, ['
            tmp = self.head
            while tmp.next is not None:
                s += f'data: {tmp.get_data()}, next: {tmp.next.get_data()}; '
                tmp = tmp.next
            s += f'data: {tmp.get_data()}, next: {tmp.next}]]'
            return s

    def pop(self):
        if self.length == 0:
            raise IndexError("LinkedList is empty!")
        else:
            tmp = self.head
            if tmp.next is None:
                self.head = None
                self.length -= 1
            else:
                while tmp.next.next is not None:
                    tmp = tmp.next
                tmp.next = None
                self.length -= 1

    def change_on_start(self, n, new_data):
        if n > self.length or n < 1:
            raise KeyError("Element doesn't exist!")
        else:
            tmp = self.head
            for i in range(1, n):
                tmp = tmp.next
            tmp.change_data(new_data)

    def clear(self):
        for i in range(self.length):
            self.pop()
