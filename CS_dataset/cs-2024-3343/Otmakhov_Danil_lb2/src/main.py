class Node:
    def __init__(self, data, next = None):
        self.__data = data
        self.next = next

    def get_data(self):
        return self.__data

    def change_data(self, new_data):
        self.__data = new_data

    def __str__(self):
        if self.next:
            return f"data: {self.__data}, next: {self.next.__data}"
        else:
            return f"data: {self.__data}, next: None"


class LinkedList:
    def __init__(self, head = None):
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
            while current.next:
                current = current.next
            current.next = new_node
        self.length += 1

    def __str__(self):
        if self.head is None:
            return "LinkedList[]"
        else:
            st = ""
            current = self.head
            while current:
                st += f"{current}; "
                current = current.next
            st = st[:-2]
            return f"LinkedList[length = {self.length}, [{st}]]"

    def pop(self):
        if self.head is None:
            raise IndexError("LinkedList is empty!")
        elif self.head.next is None:
            self.head = None
            self.length = 0
        else:
            current = self.head
            while current.next.next:
                current = current.next
            current.next = None
            self.length -= 1

    def change_on_end(self, n, new_data):
        if self.length < n or n <= 0:
            raise KeyError("Element doesn't exist!")
        current = self.head
        for _ in range(self.length - n):
            current = current.next
        current.change_data(new_data)

    def clear(self):
        self.head = None
        self.length = 0
