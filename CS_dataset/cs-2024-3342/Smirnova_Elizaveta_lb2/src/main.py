class Node:
    def __init__(self, data, next=None):
        self.data = data
        self.next = next

    def get_data(self):
        return self.data
        
    def change_data(self, new_data):
        self.data = new_data

    def __str__(self):
        if self.next is None:
            return f'data: {self.get_data()}, next: None'
        else:
            return f'data: {self.get_data()}, next: {self.next.get_data()}'


class LinkedList:
    def __init__(self, head = None):
        self.head = head
        if head is None:
            self.length = 0
        else:
            self.length = 1

    def __len__(self):
        return self.length

    def append(self, element):
        self.length += 1
        new_element = Node(element, None)
        head = self.head
        if head:
            while head.next:
                head = head.next
            head.next = new_element
        else:
            self.head = new_element
  
    def __str__(self):
        if self.head is not None:
            tmp = self.head
            element = f'{tmp}'
            while tmp.next is not None:
                tmp = tmp.next
                element += "; " + tmp.__str__()
            return f'LinkedList[length = {self.length}, [{element}]]'
        else:
            return f'LinkedList[]'

    def pop(self):
        if self.length == 1:
            self.length -= 1
            self.head = None
        elif self.length != 0:
            tmp = self.head
            while tmp.next.next is not None:
                tmp = tmp.next
            tmp.next = None
            self.length -= 1
        else:
            raise IndexError("LinkedList is empty!")

    def change_on_start(self, n, new_data):
        if self.length >= n and n > 0:
            tmp = self.head
            for i in range (n - 1):
                tmp = tmp.next
            tmp.change_data(new_data)
        else:
            raise KeyError("Element doesn't exist!")

    def clear(self):
        self.head = None
        self.lenght = 0
