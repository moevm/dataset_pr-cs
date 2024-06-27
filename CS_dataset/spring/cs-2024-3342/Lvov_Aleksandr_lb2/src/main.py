class Node:
    def __init__(self, data, next=None):
        self.data = data
        self.next = next

    def get_data(self):
        return self.data

    def __str__(self):
        if self.next is not None:
            return f'data: {self.get_data()}, next: {self.next.get_data()}'
        else:
            return f'data: {self.get_data()}, next: {None}'


class LinkedList:
    def __init__(self, head=None):
        self.head = head
        if head is None:
            self.len = 0
        else:
            self.len = 1

    def __len__(self):
        curr = self.head
        c = 0
        while curr is not None:
            c += 1
            curr = curr.next
        self.len = c
        return self.len

    def append(self, data):
        new_node = Node(data)
        curr = self.head
        if curr is not None:
            while curr.next is not None:
                curr = curr.next
            curr.next = new_node
        else:
            self.head = new_node
        self.len += 1

    def __str__(self):
        if self.head is not None:
            curr = self.head
            elements = []
            while curr is not None:
                elements.append(str(curr))
                curr = curr.next
            return f'LinkedList[length = {len(self)}, [{"; ".join(elements)}]]'
        else:
            return f'LinkedList[]'

    def pop(self):
        if self.len == 1:
            self.head = None
        elif self.head is not None:
            curr = self.head
            while curr.next.next is not None:
                curr = curr.next
            curr.next = None
        else:
            raise IndexError('LinkedList is empty!')
        self.len -= 1

    def clear(self):
        curr = self.head
        tmp = self.head
        while curr is not None:
            tmp = curr.next
            curr.next = None
            curr = tmp
        self.head = None
        self.len = 0

    def delete_on_start(self, n):
        if len(self) < n or n <= 0:
            raise KeyError("Element doesn't exist!")
        else:
            curr = self.head
            if n == 1:
                self.head = curr.next
            else:
                for _ in range(n - 2):
                    curr = curr.next
                curr.next = curr.next.next if curr.next is not None else None