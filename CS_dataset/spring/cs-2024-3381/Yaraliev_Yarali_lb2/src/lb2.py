class Node:
    def __init__(self, data, next=None):
        self.data = data
        self.next = next
    def get_data(self):
        return self.data
    def change_data(self, new_data):
        self.data = new_data
    def __str__(self):
        if (self.next != None):
            return f"data: {self.data}, next: {self.next.data}"
        else:
            return f"data: {self.data}, next: None"
class LinkedList:
    def __init__(self, head = None):
        self.head = head
        if(head == None):
            self.length = 0
        else:
            self.length = 1
    def __len__(self):
        return self.length
    def append(self, element):
        end = Node(element)
        self.length += 1
        if(self.head == None):
            self.head = end
        else:
            current = self.head
            while(current.next != None):
                current = current.next
            current.next = end
    def __str__(self):
        if (self.length == 0):
            return "LinkedList[]"
        else:
            s = f"LinkedList[length = {len(self)}, [{self.head}"
            current = self.head.next
            while (current != None):
                s += f"; {current}"
                current = current.next
            s += ']]'
            return s
    def pop(self):
        if(self.length == 0):
            raise IndexError("LinkedList is empty!")
        else:
            current = self.head
            self.length -= 1
            if(self.length == 0):
                self.head = None
            else:
                while(current.next.next != None):
                    current = current.next
            current.next = None
    def change_on_end(self, n, new_data):
        if(self.length < n) or (n < 1):
            raise KeyError("Element doesn't exist!")
        else:
            current = self.head
            for i in range(self.length-n):
                current = current.next
            current.data = new_data
    def clear(self):
        self.length = 0
        self.head = None
