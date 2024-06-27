class Node:
    def __init__(self, data, next=None):
        self.data = data
        self.next = next

    def get_data(self):
        return self.data
        
    def change_data(self, new_data):
        self.data = new_data

    def __str__(self):
        if self.next == None:
            return f"data: {self.data}, next: None"
        else:
            return f"data: {self.data}, next: {self.next.data}"

class LinkedList:
    def __init__(self, head = None):
        if head == None:
            self.length = 0
        else:
            self.head = Node(head)
            self.length = 1
    def __len__(self):
        return self.length

    def append(self, element):
        if self.length == 0:
            self.head = Node(element)
        else:
            val = self.head
            while val.next != None:
                val = val.next
            val.next = Node(element)
        self.length+=1
    def __str__(self):
        if self.length == 0:
            return "LinkedList[]"
        string = ""
        val = self.head
        while val.next != None:
            string += f"data: {val.data}, next: {val.next.data}; "
            val = val.next
        string += f"data: {val.data}, next: None"
        return f"LinkedList[length = {self.length}, [{string}]]"
    def pop(self):
        if self.length == 0:
            raise IndexError("LinkedList is empty!")
        if self.length != 1:
            val = self.head
            while val.next.next != None:
                val = val.next
            val.next = None
        self.length-=1
    def change_on_start(self, n, new_data):
        if self.length < n or n < 1:
            raise KeyError("Element doesn't exist!")
        val = self.head
        while n != 1:
            n-=1
            val = val.next
        val.data = new_data
    def clear(self):
        self.length = 0
        self.head = None