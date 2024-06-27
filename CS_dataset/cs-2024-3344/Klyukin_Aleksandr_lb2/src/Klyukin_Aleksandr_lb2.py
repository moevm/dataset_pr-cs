class Node:
    def __init__(self, data, next=None):
        self.data = data
        self.next = next


    def get_data(self):
        return self.data

    def change_data(self, new_data):
        self.data = new_data

    def __str__(self):
        if self.next != None:
            return f'data: {self.data}, next: {self.next.data}'
        else:
            return f'data: {self.data}, next: None'

class LinkedList:
    def __init__(self, head=None):
        self.head = head
        self.length = 0
        if head:
            self.length += 1

    def __len__(self):
        return self.length

    def append(self, element):
        if self.head:
            last = self.head
            while last.next != None:
                last = last.next
            last.next = Node(element)
        else:
            self.head = Node(element)
        self.length += 1

    def __str__(self):
        if self.length == 0:
            return "LinkedList[]"
        else:
            out_data = ''
            node = self.head
            while node != None:
                out_data += node.__str__() + '; '
                node = node.next
            return f"LinkedList[length = {self.length}, [{out_data[:-2]}]]"

    def pop(self):
        if not self.head:
            raise IndexError("LinkedList is empty!")
        if self.head:
            last = self.head
            if self.head.next:
                while last.next.next != None:
                    last = last.next
                last.next = None
                self.length-=1
            else:
                self.head = None
                self.length = 0

    def change_on_start(self, n, new_data):
        if self.length < n or n <= 0:
            raise KeyError("Element doesn't exist!")
        node = self.head
        i = 1
        while i < n:
            node = node.next
            i+=1
        node.data = new_data

    def clear(self):
        self.head = None
        self.length = 0
