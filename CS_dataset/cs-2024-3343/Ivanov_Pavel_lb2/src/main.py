class Node:
    def __init__(self, data, next_element=None):
        self.__data = data
        self.next = next_element

    def get_data(self):
        return self.__data

    def __str__(self):
        return f"data: {self.__data}, next: {None if self.next is None else self.next.__data}"


class LinkedList:
    def __init__(self, head=None):
        self.head = head

    @property
    def length(self):
        ct = 0
        current = self.head
        if current is None:
            return 0

        while current.next is not None:
            ct += 1
            current = current.next
        ct += 1
        return ct

    def __len__(self):
        return self.length

    def append(self, element):
        current = self.head
        if current is None:
            self.head = Node(element)
        else:
            while current.next is not None:
                current = current.next

            current.next = Node(element)

    def get_list(self):
        res = []
        current = self.head
        while current.next is not None:
            res.append(str(current))
            current = current.next
        res.append(str(current))

        return res

    def __str__(self):
        if self.head is None:
            return "LinkedList[]"

        return f"LinkedList[length = {self.length}, [{'; '.join(self.get_list())}]]"

    def pop(self):
        if self.head is None:
            raise IndexError('LinkedList is empty!')

        current = self.head
        if current.next is None:
            self.head = None
        else:
            while current.next.next is not None:
                current = current.next
            current.next = None

    def clear(self):
        self.head = None

    def delete_on_end(self, n):
        if (self.length < n) or (n <= 0):
            raise KeyError("Element doesn't exist!")

        idx = self.length - n
        current = self.head
        for _ in range(idx - 1):
            current = current.next

        if idx == 0:
            self.head = self.head.next
        if idx == self.length - 1:
            current.next = None
        else:
            current.next = current.next.next

