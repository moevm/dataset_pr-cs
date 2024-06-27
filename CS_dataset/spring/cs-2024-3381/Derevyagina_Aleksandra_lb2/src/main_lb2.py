class Node:
    def __init__(self, data, next=None):
        self.data = data
        self.next = next

    def get_data(self):
        return self.data

    def change_data(self, new_data):
        self.data = new_data

    def __str__(self):
        if self.next:
            return f"data: {self.data}, next: {self.next.data}"
        return f"data: {self.data}, next: {None}"


class LinkedList:
    def __init__(self, head=None):
        self.head = head
        self.length = 0
        if head:
            self.length += 1

    def __len__(self):
        return self.length

    def append(self, element):
        element = Node(element)
        if self.length == 0:
            self.head = element
            self.length = 1
        else:
            new_head = self.head
            while new_head.next:
                new_head = new_head.next
            new_head.next = element
            self.length += 1

    def __str__(self):
        if self.length == 0:
            return "LinkedList[]"
        answer = f"LinkedList[length = {self.length}, ["
        new_head = self.head
        while new_head:
            answer += str(new_head) + "; "
            new_head = new_head.next
        answer = answer[:-2] + "]]"
        return answer

    def pop(self):
        if self.length == 0:
            raise IndexError("LinkedList is empty!")
        new_head = self.head
        self.length -= 1
        if new_head.next is None:
            self.head = None
        else:
            next_head = new_head.next
            while next_head.next:
                new_head = new_head.next
                next_head = new_head.next
            new_head.next = None

    def change_on_start(self, n, new_data):
        if self.length < n or n <= 0:
            raise KeyError("Element doesn't exist!")
        new_head = self.head
        for i in range(n - 1):
            new_head = new_head.next
        new_head.data = new_data

    def clear(self):
        self.length = 0
        self.head = None
