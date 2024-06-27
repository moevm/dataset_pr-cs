class Node:
    def __init__(self, data, next=None):
        self.data = data
        self.next = next
    
    def get_data(self):
        return self.data
    
    def __str__(self):
        return f"data: {self.data}, next: {self.next.data if self.next else None}"


class LinkedList:
    def __init__(self, head=None):
        self.head = head
        self.length = 0
        cur = self.head
        while cur:
            self.length += 1
            cur = cur.next

    def __len__(self):
        return self.length

    def append(self, element):
        if not self.head:
            self.head = Node(element)
        else:
            cur = self.head
            while cur.next:
                cur = cur.next
            cur.next = Node(element)
        self.length += 1
    
    
    def __str__(self):
        if not self.head:
            return f"LinkedList[]"
        s, cur = [], self.head
        while cur:
            s.append(str(cur))
            cur = cur.next
        return f"LinkedList[length = {self.length}, [{'; '.join(s)}]]"

    def pop(self):
        if not self.head:
            raise(IndexError("LinkedList is empty!"))
        cur = self.head
        if not cur.next:
            self.head = None
        for _ in range(self.length-2):
            cur = cur.next
        cur.next = None
        self.length -= 1

    def delete_on_start(self, n):
        if self.length < n or n < 1:
            raise KeyError("Element doesn't exist!")
        cur = self.head
        if n == 1:
            self.head = cur.next
        else:
            for _ in range(n-2):
                cur = cur.next
            cur.next = cur.next.next
        self.length -= 1

    def clear(self):
        self.head, self.length = None, 0
