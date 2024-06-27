class Node:
    def __init__(self, data, next=None):
        self.__data = data
        self.next = next

    def get_data(self):
        return self.__data

    def change_data(self, new_data):
        self.__data = new_data

    def __str__(self):
        if self.next:
            return f"data: {self.__data}, next: {self.next.get_data()}"
        return f"data: {self.__data}, next: None"


class LinkedList:
    def __init__(self, head=None):
        if head:
            self.head = Node(head)
            self.length = 1
        else:
            self.head = None
            self.length = 0

    def __len__(self):
        return self.length

    def append(self, element):
        new_node = Node(element)
        if self.head:
            current = self.head
            while current.next:
                current = current.next
            current.next = new_node
        else:
            self.head = new_node
        self.length += 1

    def __str__(self):
        print_list = []
        current = self.head
        while current:
            print_list.append(str(current))
            current = current.next
        if print_list:
            return f'LinkedList[length = {self.length}, [{"; ".join(print_list)}]]'
        return 'LinkedList[]'

    def pop(self):
        if not self.head:
            raise IndexError('LinkedList is empty')
        if self.head.next is None:
            self.head = None
            self.length = 0
        else:
            current = self.head
            while current.next.next:
                current = current.next
            current.next = None
            self.length -= 1

    def clear(self):
        self.head = None
        self.length = 0

    def change_on_end(self, n, new_data):
        if n > self.length or n < 0:
            raise KeyError("Element doesn't exist!")
        current = self.head
        for _ in range(self.length - n):
            current = current.next
        if current is None:
            raise KeyError("Element doesn't exist!")
        current.change_data(new_data)
