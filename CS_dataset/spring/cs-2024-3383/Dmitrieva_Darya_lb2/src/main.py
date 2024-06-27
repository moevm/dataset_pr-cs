class Node:
    def __init__(self, data, next_node=None):
        self.data = data
        self.next = next_node
    def get_data(self):
        return self.data
    def change_data(self, new_data):
        self.data = new_data
    def __str__(self):
        if self.next:
            next_data = self.next.data
        else:
            next_data = None
        return f"data: {self.data}, next: {next_data}"

class LinkedList:
    def __init__(self, head=None):
        self.head = head
        self.length = 0
        if head:
            self.length = 1

    def __len__(self):
        return self.length

    def append(self, element):
        new_node = Node(element)
        if self.head is None:
            self.head = new_node
        else:
            tmp = self.head
            while tmp.next is not None:
                tmp = tmp.next
            tmp.next = new_node
        self.length += 1

    def __str__(self):
        if self.head is None:
            return f"LinkedList[]"
        res =  f"LinkedList[length = {self.length}, ["
        tmp = self.head
        while tmp.next is not None:
            res += f"data: {tmp.data}, next: {tmp.next.data}; "
            tmp = tmp.next
        res += f"data: {tmp.data}, next: None]]"
        return res


    def pop(self):
        if self.head is None:
            raise IndexError("LinkedList is empty!")
        if self.length == 1:
            self.head = None
            self.length -=1
        else:
            tmp = self.head
            while tmp.next.next is not None:
                tmp = tmp.next
            tmp.next = None
            self.length -= 1

    def change_on_end(self, n, new_data):
        k = 0
        prev = None
        tmp = self.head
        if self.length < n or n<=0:
            raise KeyError("Element doesn't exist")
        elif self.length - n == 0:
            new_node = Node(new_data)
            self.head = new_node
            self.head.next = tmp.next
        else:
            while tmp.next is not None and (self.length - n)!=k:
                prev = tmp
                tmp = tmp.next
                k += 1
            if tmp.next is not None:
                new_node = Node(new_data)
                prev.next = new_node
                new_node.next = tmp.next
            else:
                new_node = Node(new_data)
                prev.next = new_node
                new_node.next = None

    def clear(self):
        tmp = self.head
        while self.head is not None:
            tmp = self.head
            self.head = self.head.next
            self.length -= 1