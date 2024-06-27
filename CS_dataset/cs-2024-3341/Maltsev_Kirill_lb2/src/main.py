class Node:
    
    def __init__(self, data, next=None):
        self.data = data
        self.next = next

    def get_data(self):
        return self.data
    
    def __str__(self):
        return f"data: {self.data}, next: {self.next.data if (self.next != None) else None}"

class LinkedList:
    
    def __init__(self, head=None):
        self.head = head
        self.length = 1 if head != None else 0
    
    def __len__(self):
        return self.length
    
    def __str__(self):
        if (self.length == 0):
            return "LinkedList[]"
        string = f"LinkedList[length = {self.length}, ["
        
        current = self.head
        while (current != None):
            string += str(current)
            if (current.next != None):
                string += "; "
            current = current.next
        
        return string + "]]"
    
    def append(self, element):
        if (self.length == 0):
            self.head = Node(element)
            self.length += 1
            return
        
        current = self.head
        while (current.next != None):
            current = current.next
        current.next = Node(element)
        self.length += 1
        

    def pop(self):
        
        if (self.length == 0):
            raise IndexError("LinkedList is empty!")
        
        
        if (self.length == 1):
            self.head = None
            self.length -= 1
            return
        
        current = self.head
        while (current.next.next != None):
            current = current.next
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
