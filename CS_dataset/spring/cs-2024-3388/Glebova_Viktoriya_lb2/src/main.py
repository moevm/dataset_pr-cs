class Node:
    def __init__(self, data, next=None):
        self.data = data
        self.next = next

    def get_data(self):
        return self.data

    def __str__(self):
        if self.next is None:
            return "data: {}, next: None".format(self.data)
        else:
            return "data: {}, next: {}".format(self.data, self.next.data)


class LinkedList:
    def __init__(self, head=None):
        self.head = head
        self.length = 0 if head == None else 1

    def __len__(self):
        return self.length

    def append(self, element):
        self.length += 1
        
        if self.head == None:
            self.head = Node(element)
            return
        
        cur = self.head
        
        while cur.next is not None:
            cur = cur.next
        
        cur.next = Node(element)
            
    def __str__(self):
        if self.length == 0:
            return "LinkedList[]"
        
        string = "LinkedList[length = {}, [data: {}, next: {}".format(self.length, self.head.data, self.head.next.data if self.head.next != None else "None")
        cur = self.head.next
        for i in range(self.length - 1):
            string += "; data: {}, next: {}".format(cur.data, cur.next.data if cur.next != None else "None")
            cur = cur.next
            
        string += "]]"
        return string
        
    def delete_on_end(self, n):
        if n > self.length or n < 1:
            raise KeyError("Element doesn't exist!")
        
        n = self.length - n + 1
        if n == 1:
            self.head = self.head.next
            self.length -= 1
            return
        
        cur = self.head
        
        for i in range(n-2):
            cur = cur.next
            
        cur.next = cur.next.next
        self.length -= 1
            
    def pop(self):
        if self.length == 0:
            raise IndexError("LinkedList is empty!")
        self.delete_on_end(1)

    def clear(self):
        self.head = None
        self.length = 0
