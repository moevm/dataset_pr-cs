class Node:
    def __init__(self, data, next = None):
        self.__data = data
        self.next = next

    def get_data(self):
        return self.__data

    def __str__(self):
        return f"data: {self.__data}, next: {self.next.get_data() if self.next is not None else None}"

class LinkedList:
    def __init__(self, head=None):
        self.head = head
        self.length = 0 if head is None else 1

    def __len__(self):
        return self.length

    def append(self, element):
        new_node = Node(element)

        if self.head is None:
            self.head = new_node
        else:
            current = self.head
            while current.next is not None:
                current = current.next
            current.next = new_node
        self.length += 1

    def __str__(self):

        if self.head is None:
            return "LinkedList[]"

        else:
            nodes = []
            current = self.head
            while current is not None:
                nodes.append(
                    f"data: {current.get_data()}, next: {current.next.get_data() if current.next is not None else None}")
                current = current.next
            return f"LinkedList[length = {self.length}, [{'; '.join(nodes)}]]"

    def pop(self):

        if self.head is None:
            raise IndexError("Empty")

        if self.head.next is None:
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

        if n > len(self):
            raise KeyError("Doesn't exist")

        if n <= 0:
            raise ValueError("Doesn't exist")

        if n == len(self):
            self.head = self.head.next

        else:
            current = self.head
            for _ in range(len(self) - n - 1):
                current = current.next

            current.next = current.next.next

        self.length -= 1