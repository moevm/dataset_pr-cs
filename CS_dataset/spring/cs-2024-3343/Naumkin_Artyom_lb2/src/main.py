class Node:
    def __init__(self, data, next=None):
        self.__data = data
        self.next = next

    def get_data(self):
        return self.__data

    def __str__(self):
        next_data = "None" if self.next is None else str(self.next.get_data())
        return f"data: {self.__data}, next: {next_data}"


class LinkedList:
    def __init__(self, head=None):
        self.head = head
        self.length = 0 if head is None else 1

    def __len__(self):
        return self.length

    def append(self, element):
        if self.head is None:
            self.head = Node(element)
        else:
            current = self.head
            while current.next is not None:
                current = current.next
            current.next = Node(element)
        self.length += 1

    def __str__(self):
        if self.head is None:
            return "LinkedList[]"
        else:
            elements = []
            current = self.head
            while current is not None:
                elements.append(str(current))
                current = current.next
            return f"LinkedList[length = {self.length}, [{'; '.join(elements)}]]"

    def pop(self):
        if self.head is None:
            raise IndexError("LinkedList is empty!")
        elif self.head.next is None:
            self.head = None
        else:
            current = self.head
            while current.next.next is not None:
                current = current.next
            current.next = None
        self.length -= 1

    def clear(self):
        self.head = None
        self.length = 0

    def delete_on_end(self, n):
        if n > self.length or n <= 0:
            raise KeyError("Element doesn't exist!")
        elif n == self.length:
            self.head = self.head.next
        else:
            current = self.head
            for _ in range(self.length - n - 1):
                current = current.next
            current.next = current.next.next
        self.length -= 1
