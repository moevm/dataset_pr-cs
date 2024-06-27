class Node:
    def __init__(self, data, next = None):
        self.data = data
        self.next = next

    def get_data(self):
        return self.data

    def __str__(self):
        if self.next:
            return f"data: {self.data}, next: {self.next.data}"
        return f"data: {self.data}, next: {self.next}"


class LinkedList:
    def __init__(self, head=None):
        self.head = head
        if head:
            self.length = 1
        else:
            self.length = 0

    def __len__(self):
        return self.length

    def append(self, element):
        element = Node(element)
        if self.length == 0:
            self.head = element
            self.length = 1
        else:
            current_head = self.head
            while current_head.next:
                current_head = current_head.next
            current_head.next = element
            self.length += 1


    def __str__(self):
        if self.length == 0:
            return "LinkedList[]"
        s = f"LinkedList[length = {self.length}, ["
        data = []
        current_head = self.head
        while current_head:
            data.append(str(current_head))
            current_head = current_head.next
        s = s + "; ".join(data) + "]]"
        return s

    def pop(self):
        if self.length == 0:
            raise IndexError("LinkedList is empty!")
        current_head = self.head
        prev_node = current_head
        while current_head.next:
            prev_node = current_head
            current_head = current_head.next
        prev_node.next = None
        self.length -= 1

    def delete_on_end(self, n):
        if self.length < n or n <= 0:
            raise KeyError("Element doesn't exist!")
        if n == self.length:
            self.head = self.head.next
            self.length -= 1
        elif n == 1:
            c = 0
            current_head = self.head
            while c < self.length - 2:
                current_head = current_head.next
                c += 1
            current_head.next = None
            self.length -= 1
        else:
            c = 0
            current_head = self.head
            while c < self.length - n - 1:
                current_head = current_head.next
                c += 1
            current_head.next = current_head.next.next
            self.length -= 1

    def clear(self):
        self.head = None
        self.length = 0