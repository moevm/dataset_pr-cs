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
            return "data: " + str(self.data) + ", next: " + str(self.next.data)
        else:
            return "data: " + str(self.data) + ", next: None"


class LinkedList:
    def __init__(self, head=None):
        self.head = head
        self.length = 0
        if head:
            self.length = 1

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
        else:
            result = "LinkedList[length = " + str(self.length) + ", ["
            current = self.head
            while current:
                result += "data: " + str(current.get_data()) + ", next: "
                if current.next:
                    result += str(current.next.get_data()) + "; "
                else:
                    result += "None"
                current = current.next
            result += "]]"
            return result

    def pop(self):
        if not self.head:
            raise IndexError("LinkedList is empty!")
        elif self.length == 1:
            self.head = None
            self.length = 0
        else:
            current = self.head
            while current.next.next:
                current = current.next
            current.next = None
            self.length -= 1

    def change_on_end(self, n, new_data):
        if n <= 0 or n > self.length:
            raise KeyError("Element doesn't exist!")
        elif n == self.length:
            self.head.data = new_data
        else:
            current = self.head
            for _ in range(self.length - n):
                current = current.next
            current.data = new_data

    def clear(self):
        self.head = None
        self.length = 0

