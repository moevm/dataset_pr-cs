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
            return f"data: {self.data}, next: {self.next.data}"
        return f"data: {self.data}, next: None"


class LinkedList:
    def __init__(self, head = None):
        if head == None:
            self.head = None
            self.length = 0
        else:
            self.head = Node(head)
            self.length = 1


    def __len__(self):
        return self.length

    def append(self, element):
        if self.head == None:
            self.head = Node(element)
        else:
            node = self.head
            while node.next != None:
                node = node.next
            node.next = Node(element)
        self.length += 1

            
    def __str__(self):
        if self.head == None:
            return "LinkedList[]"
        res = f"LinkedList[length = {self.length}, ["
        node = self.head
        while node != None:
            if node.next == None:
                res += f"{str(node)}"
                break
            res += f"{str(node)}; "
            node = node.next
        res += "]]"
        return res

    def pop(self):
        if self.head == None:
            raise IndexError("LinkedList is empty!")
        elif self.head.next == None:
            self.head = None
            self.length = 0
        else:
            node = self.head
            while node.next.next != None:
                node = node.next
            node.next = None
            self.length -= 1


    def change_on_start(self, n, new_data):
        if  self.length < n or n <= 0:
            raise KeyError("Element doesn't exist!")
        else:
            node = self.head
            for i in range(n-1):
                node = node.next
            node.data = new_data

    def clear(self):
        self.head = None