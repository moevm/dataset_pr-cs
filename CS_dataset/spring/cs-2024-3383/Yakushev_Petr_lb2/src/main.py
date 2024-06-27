class Node:
    def __init__(self, data, next=None):
        self.data = data
        self.next = next
        
    def get_data(self):
        return self.data
        
    def __str__(self):
        if self.next is None:
            next_data = "None" 
        else:
            next_data =str(self.next.data)
        return f"data: {self.data}, next: {next_data}"


class LinkedList:
    def __init__(self, head=None):
        self.head = head
        count = 0
        current = self.head
        while current:
            count += 1
            current = current.next
        self.length = count

    def __len__(self):
        return self.length

    def append(self, element):
        self.length += 1
        newNode = Node(element)
        if self.head is None:
            self.head = newNode
            return
        current = self.head
        while current.next:
            current = current.next
        current.next = newNode

    def __str__(self):
        if self.length == 0:
            return "LinkedList[]"
        nodes = []
        current = self.head
        while current:
            nodes.append(str(current))
            current = current.next
        return f"LinkedList[length = {self.length}, [{'; '.join(nodes)}]]"

    def pop(self):
        if self.length == 0:
            raise IndexError("LinkedList is empty!")
        if self.length == 1:
            self.head = None
            self.length -= 1
            return
        prev = None
        current = self.head
        while current.next:
            prev = current
            current = current.next
        prev.next = None
        self.length -= 1

    def clear(self):
        self.head = None
        self.length = 0
        
    def delete_on_start(self, n):
        if n > self.length or n < 1:
            raise KeyError("Element doesn't exist or invalid index!")
        if n == 1:
            self.head = self.head.next
            self.length -= 1
            return
        i = 1  
        prev = None
        current = self.head
        while i < n:
            prev = current
            current = current.next
            i += 1
        if current.next is None:
            prev.next = None
        else:
            prev.next = current.next
        self.length -= 1
