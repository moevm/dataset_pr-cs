class Node:
    def __init__(self, data, next = None):
        self.data = data
        self.next = next

    def get_data(self):
        return self.data

    def change_data(self, new_data):
        self.data = new_data

    def __str__(self):
        if self.next:
            return f"data: {self.data}, next: {self.next.data}"
        else:
            return f"data: {self.data}, next: None"


class LinkedList:
    def __init__(self, head=None):
        self.length = 0
        self.head = head

    def __len__(self):
        return self.length

    def append(self, element):
        new_node = Node(element)
        if self.head is None:
            self.head = new_node
        else:
            cur = self.head
            while cur.next:
                cur = cur.next
            cur.next = new_node
        self.length += 1

    def __str__(self):
        if self.head is None:
            return "LinkedList[]"
        else:
            result = []
            cur = self.head
            while cur:
                result += [cur.__str__()]
                cur = cur.next
            res = "; ".join(result)
            return f"LinkedList[length = {self.length}, [{res}]]"


    def pop(self):
        if self.head is None:
            raise IndexError("LinkedList is empty!")
        elif self.head.next is None:
            self.head = None
            self.length = 0
        else:
            cur = self.head
            while cur.next.next:
                cur = cur.next
            cur.next = None
            self.length -= 1

    def change_on_start(self, n, new_data):
        if n > self.length or n <= 0:
            raise KeyError("Element doesn't exist!")
        cur = self.head
        for i in range(1, n):
            cur = cur.next
        cur.change_data(new_data)

    def clear(self):
        self.head = None
        self.length = 0

