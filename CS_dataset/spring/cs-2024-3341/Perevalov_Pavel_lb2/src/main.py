class Node:

    def __init__(self, data, next=None):
        self.data = data
        self.next = next

    def get_data(self):
        return self.data

    def __str__(self):
        return f"data: {self.data}, next: {self.next.data if (self.next != None) else None}"

class LinkedList:
    head = []
    length = 0
    def __init__(self, head = None):
        if head != None:
            self.head = head
            self.length += 1

    def __len__(self):
        return self.length

    def append(self, element):
        if self.head == []:
            self.head = Node(element)
        else:
            current = self.head
            while current.next:
                current = current.next
            current.next = Node(element)
        self.length += 1

    def __str__(self):
        if self.length == 0:
            return "LinkedList[]"
        str = f"LinkedList[length = {self.length}, [{self.head.__str__()}"
        current = self.head
        while current.next:
            current = current.next
            str += f"; {current.__str__()}"
        str += "]]"
        return str

    def pop(self):
        if self.length == 0:
            raise IndexError("LinkedList is empty!")
        if self.length == 1:
            self.head = []
            self.length = 0
            return
        counter = 1
        current = self.head
        while counter != self.length - 1:
            current = current.next
            counter += 1
        current.next = None
        self.length -= 1

    def delete_on_start(self, n):
        n -= 1
        if (n < 0 or self.length <= n):
            raise KeyError("<element> doesn't exist!")

        if (n == 0):
            self.head = self.head.next
            self.length -= 1
            return

        current = self.head
        for i in range(n-1):
            current = current.next
        current.next = current.next.next
        self.length -= 1

    def clear(self):
        self.head = None
        self.length = 0