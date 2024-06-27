class Node:
    def __init__(self, data, _next=None):
        self.data = data
        self.next = _next

    def get_data(self):
        return self.data

    def change_data(self, new_data):
        self.data = new_data

    def __str__(self):
        if self.next:
            return f"data: {self.data}, next: {self.next.data}"
        return f"data: {self.get_data()}, next: None"


class LinkedList:
    def __init__(self, head=None):
        self.head = head
        self.length = 0
        while head:
            head = head.next
            self.length += 1

    def __len__(self):
        return self.length

    def append(self, element):
        if self.head:
            tmp = self.head
            while tmp.next:
                tmp = tmp.next
            tmp.next = Node(element)
        else:
            self.head = Node(element)
        self.length += 1

    def __str__(self):
        if self.length:
            s = ''
            tmp = self.head
            while tmp:
                s += tmp.__str__() + '; '
                tmp = tmp.next
            return f"LinkedList[length = {self.length}, [{s[:-2]}]]"
        else:
            return "LinkedList[]"

    def pop(self):
        if not self.head:
            raise IndexError("LinkedList is empty!")
        if self.head.next:
            tmp = self.head
            while tmp.next.next:
                tmp = tmp.next
            tmp.next = None
        else:
            self.head = None
        self.length -= 1

    def change_on_start(self, n, new_data):
        if self.length < n or n <= 0:
            raise KeyError("Element doesn't exist!")
        tmp = self.head
        for i in range(1, n):
            tmp = tmp.next
        tmp.data = new_data

    def clear(self):
        self.head = None
        self.length = 0
