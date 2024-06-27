class Node:
    def __init__(self, data, next=None):
        self.__data = data
        self.next = next

    def get_data(self):
        return self.__data

    def __str__(self):
        return f"data: {self.__data}, next: {self.next.get_data() if self.next else None}"


class LinkedList:
    def __init__(self, head=None):
        self.head = head
        if head is None:
            self.length = 0
        else:
            self.length = 1

    def __len__(self):
        return self.length

    def append(self, element):
        if self.length == 0:
            self.head = Node(element)
        else:
            curr = self.head
            for i in range(self.length - 1):
                curr = curr.next
            curr.next = Node(element)
        self.length += 1

    def __str__(self):
        res = "LinkedList["
        curr = self.head
        if self.length != 0:
            res += f"length = {self.length}, ["
            for i in range(self.length):
                res += f"{curr}; "
                curr = curr.next
            res = res[:-2] + ']'
        return res + ']'

    def pop(self):
        if self.length == 0:
            raise IndexError("LinkedList is empty!")
        if self.length == 1:
            self.head = None
        else:
            curr = self.head
            for i in range(self.length - 2):
                curr = curr.next
            curr.next = None
        self.length -= 1

    def delete_on_start(self, n):
        if self.length < n or n <= 0:
            raise KeyError("Element doesn't exist!")
        if self.length == 1:
            self.head = None
        elif n == 1:
            self.head = self.head.next
        else:
            curr = self.head
            for i in range(n - 2):
                curr = curr.next
            curr.next = curr.next.next
        self.length -= 1

    def clear(self):
        self.head = None
        self.length = 0
