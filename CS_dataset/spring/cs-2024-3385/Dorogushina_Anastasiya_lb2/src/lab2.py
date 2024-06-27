class Node:
    def __init__(self, data, next=None):
        self.__data = data
        self.next = next if next else None

    def get_data(self):
        return self.__data

    def change_data(self, new_data):
        self.__data = new_data

    def __str__(self):
        next_data = self.next.__data if self.next else None
        return f'data: {self.__data}, next: {next_data}'


class LinkedList:
    def __init__(self, head=None):
        self.head = Node(head) if head is not None else None
        self.length = 1 if head is not None else 0

    def __len__(self):
        return self.length

    def append(self, element):
        self.length += 1
        element = Node(element)
        if self.head is None:
            self.head = element
        else:
            cur = self.head
            while cur.next:
                cur = cur.next
            cur.next = element

    def __str__(self):
        if self.head is None:
            return "LinkedList[]"
        else:
            elements = []
            cur = self.head
            while cur is not None:
                elements.append(f'{cur}')
                cur = cur.next
            return f'LinkedList[length = {len(self)}, [{"; ".join(elements)}]]'

    def pop(self):
        if self.head is None:
            raise IndexError('LinkedList is empty!')
        self.length -= 1
        if self.head.next is None:
            self.head = None
        else:
            cur = self.head
            while cur.next.next:
                cur = cur.next
            cur.next = None

    def change_on_start(self, n, new_data):
        if len(self) < n or n < 1:
            raise KeyError("Element doesn't exist!")
        cur = self.head
        for i in range(n-1):
            cur = cur.next
        cur.change_data(new_data)

    def clear(self):
        self.head = None
        self.length = 0