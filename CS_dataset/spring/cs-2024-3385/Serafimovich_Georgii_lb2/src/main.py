class Node:
    def __init__(self, data, next_node=None):
        self.data = data
        self.next = next_node

    def get_data(self):
        return self.data

    def __str__(self):
        if self.next:
            return f"data: {self.data}, next: {self.next.data}"
        else:
            return f"data: {self.data}, next: None"

class LinkedList:
    def __init__(self, head=None):
        if head:
            self.head = Node(head)
            self.length = 1
        else:
            self.head = head
            self.length = 0

    def __len__(self):
        return self.length

    def append(self, element):
        if not self.head:
            self.head = Node(element)
        else:
            temp = self.head
            while temp.next:
                temp = temp.next
            temp.next = Node(element)
        self.length += 1

    def __str__(self):
        result = "LinkedList["
        if self.head:
            temp = self.head
            result += f"length = {self.length}, ["
            while temp.next:
                result += str(temp) + "; "
                temp = temp.next
            result += str(temp) + "]"
        result += "]"
        return result

    def pop(self):
        if not self.head:
            raise IndexError("LinkedList is empty!")
        if not self.head.next:
            self.head = None
        else:
            temp = self.head
            while temp.next.next:
                temp = temp.next
            temp.next = None
        self.length -= 1

    def delete_on_end(self, n):
        if abs(n) > self.length:
            raise KeyError("Element doesn't exist!")
        if n > 0:
            n = self.length - n
        else:
            raise KeyError("Element doesn't exist!")
        if n == 0:
            self.head = self.head.next
        else:
            if not self.head.next:
                self.head = None
            else:
                temp = self.head
                i = 0
                while i < n - 1:
                    temp = temp.next
                    i += 1
                if temp.next.next:
                    temp.next = temp.next.next
                else:
                    temp.next = None
        self.length -= 1

    def clear(self):
        self.head = None
        self.length = 0
