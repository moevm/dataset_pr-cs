class Node:
    def __init__(self, data, next=None):
        self.data = data
        self.next = next
    def get_data(self):
        return self.data
    def __str__(self):
        return f"data: {self.data}, next: {self.next.data if self.next is not None else None}"

class LinkedList:
    def __init__(self, head=None):
        self.head = head
    def __len__(self):
        if self.head == None:
            return 0
        k = 1
        cur = self.head
        while cur.next != None:
            cur = cur.next
            k += 1
        return k
    def append(self, element):
        path = Node(element)
        if len(self) == 0:
            self.head = path
            return None
        cur = self.head
        while cur.next != None:
            cur = cur.next
        cur.next = path
    def __str__(self):
        start = 'LinkedList'
        free = ''
        if len(self) == 0:
            return 'LinkedList[]'
        current = self.head
        while current.next != None:
            free += str(current) + '; '
            current = current.next
        free += str(current)
        return start + '[length = ' + str(len(self)) + ', [' +  free + ']]'
    def pop(self):
        if len(self) == 0:
            raise IndexError("LinkedList is empty!")
        cur = self.head
        if cur.next == None:
            self.head = None
            return
        while cur.next.next != None:
            cur = cur.next
        cur.next = None
    def delete_on_end(self, n):
        if len(self) - n < 0 or n <= 0:
            raise KeyError("Element doesn't exist!")
        count = len(self) - n
        k = 1
        if count == 0:
            self.head = self.head.next
            return
        cur = self.head
        while k < count:
            cur = cur.next
            k += 1
        if cur.next.next == None:
            cur.next = None
        else:
            cur_2 = cur.next.next
            cur.next = cur_2
    def clear(self):
        self.head = None
