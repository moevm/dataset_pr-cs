class Node:
    def __init__(self, data, next=None):
        self.data = data
        self.next = next

    def get_data(self):
        return self.data

    def __str__(self):
        next_data = self.next.data if self.next else None
        return f"data: {self.data}, next: {next_data}"


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

    def __str__(self):
        res = "LinkedList["

        it = self.head

        if it is not None:
            res += f"length = {self.length}, "
            res += '[' + str(it)
            it = it.next

            while it is not None:
                res += '; ' + str(it)
                it = it.next

            res += ']'

        res += ']'
        return res

    def append(self, element):
        if self.head:
            it = self.head
            while it.next is not None:
                it = it.next
            it.next = Node(element)
        else:
            self.head = Node(element)

        self.length += 1

    def pop(self):
        if self.length == 0:
            raise IndexError("LinkedList is empty!")

        if self.length > 1:
            it = self.head
            while it.next.next is not None:
                it = it.next
            it.next = None
        elif self.length == 1:
            self.head = None

        self.length -= 1

    def clear(self):
        self.head = None
        self.length = 0

    def delete_on_end(self, n):
        if self.length < n or n <= 0:
            raise KeyError("Element doesn't exist!")

        if self.length == n:
            self.head = self.head.next
        elif self.length > 1:
            index = self.length - n
            it = self.head
            for i in range(index - 1):
                it = it.next
            it.next = it.next.next
        else:
            self.head = None

        self.length -= 1
