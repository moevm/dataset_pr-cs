class Node:
    def __init__(self, data, next=None):
        self.data = data
        self.next = next
        
    def get_data(self):
        return self.data

    def __str__(self):
        if self.next:
            return f"data: {self.data}, next: {self.next.get_data()}"
        else:
            return f"data: {self.data}, next: None"


class LinkedList:
    def __init__(self, head=None):
        if head:
            self.head = head
            self.length = 1
        else:
            self.head = None
            self.length = 0

    def __len__(self):
        return self.length

    def append(self, element):
        new_node = Node(element)
        if not self.head:
            self.head = new_node
        else:
            current = self.head
            while current.next:
                current = current.next
            current.next = new_node
        self.length += 1

    def __str__(self):
        if not self.head:
            return "LinkedList[]"
        nodes = [str(self.head)]
        current = self.head
        while current.next:
            current = current.next
            nodes.append(str(current))
        return f"LinkedList[length = {self.length}, [{'; '.join(nodes)}]]"

    def pop(self):
        if not self.length:
            raise IndexError("LinkedList is empty!")
        elif self.length == 1:
            self.head = None
        else:
            current = self.head
            prev = None
            while current.next:
                prev = current
                current = current.next
            prev.next = None
        self.length -= 1

    def delete_on_end(self, n):
        if n > self.length or n <= 0:
            raise KeyError("Element doesn't exist!")
        elif n == self.length:
            self.head = self.head.next
        else:
            i = 0
            current = self.head
            prev = None
            while i != self.length - n:
                prev = current
                current = current.next
                i += 1
            prev.next = current.next
        self.length -= 1

    def clear(self):
        self.head = None
        self.length = 0
