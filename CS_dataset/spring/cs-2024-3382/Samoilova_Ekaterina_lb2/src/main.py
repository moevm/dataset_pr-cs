class Node:
    def __init__(self, data, next=None):
        self.data = data
        self.next = next

    def get_data(self):
        return self.data

    def change_data(self, new_data):
        self.data = new_data

    def __str__(self):
        next_data = self.next.get_data() if self.next else None
        return f"data: {self.data}, next: {next_data}"

class LinkedList:
    def __init__(self, head=None):
        self.head = head
        self.length = 0 if head is None else 1

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
            nodes = []
            current = self.head
            while current:
                nodes.append(f"data: {current.get_data()}, next: {current.next.get_data() if current.next else None}")
                current = current.next
            return f"LinkedList[length = {self.length}, [{'; '.join(nodes)}]]"

    def pop(self):
        if not self.head:
            raise IndexError("LinkedList is empty!")
        current = self.head
        prev = None
        while current.next:
            prev = current
            current = current.next
        if prev:
            prev.next = None
        else:
            self.head = None
        self.length -= 1

    def clear(self):
        self.head = None
        self.length = 0

    def change_on_end(self, n, new_data):
        if len(self) < n or n<=0: raise KeyError ("Element doesn't exist!")
        else:
            head = self.head
            for i in range(len(self) - n):
                head = head.next
            head.change_data(new_data)

    
