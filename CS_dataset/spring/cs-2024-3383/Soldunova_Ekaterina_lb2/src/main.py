class Node:
    def __init__(self, data, next=None):
        self.data = data
        self.next = next

    def get_data(self):
        return self.data

    def __str__(self):
        if self.next != None:
            strg = f"data: {self.data}, next: {self.next.data}"
        else:
            strg = f"data: {self.data}, next: None"
        return strg

class LinkedList:
    def __init__(self, head = None):
        self.head = head
        count = 0
        current = head
        while current:
            count += 1
            current = current.next
        self.length = count

    def __len__(self):
        return self.length

    def append(self, element):
        newEl = Node(element)
        if self.head:
            self.length += 1
            current = self.head
            while current.next:
                current = current.next
            current.next = newEl
        else:
            self.length = 1
            self.head = newEl

    def __str__(self):
        if self.head:
            strg = f"LinkedList[length = {self.length}, ["
            current = self.head
            while current.next:
                strg += str(current) + "; "
                current = current.next
            strg += str(current) + "]]"
            return strg
        else:
            return "LinkedList[]"
        
    def pop(self):
        if self.length > 1:    
            self.length -= 1
            current = self.head
            while current.next.next:
                current = current.next
            current.next = None
        elif self.length == 1:
            self.head = None
        else:
            raise IndexError("LinkedList is empty!")

    def delete_on_end(self, n):
        if n > self.length or n < 1:
            raise KeyError("Element doesn't exist!")
        if n == self.length:
            self.head = self.head.next
            self.length -= 1
        else:
            num = self.length - n
            prev = None
            current = self.head
            for i in range(num):
                prev = current
                current = current.next
            prev.next = current.next
            self.length -= 1

    def clear(self):
        self.head = None
        self.length = 0