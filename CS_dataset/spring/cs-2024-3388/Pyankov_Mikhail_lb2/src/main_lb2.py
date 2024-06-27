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
        return f'data: {self.data}, next: {None}'


class LinkedList:
    def __init__(self, head=None):
        if head != None:
            self.head = Node(head)
            self.length = 1
        else:
            self.head = None
            self.length = 0

    def __len__(self):
        return self.length

    def append(self, element):
        element = Node(element)
        if self.length == 0:
            self.head = element
            self.length += 1
        else:
            start = self.head
            while(start.next != None):
                start = start.next
            start.next = element
            self.length += 1

    def __str__(self):
        if self.length == 0:
            return 'LinkedList[]'
        elems_string = ''
        start = self.head
        while(start):
            if start.next != None:
                elems_string += f'data: {start.data}, next: {start.next.data}; '
            else:
                elems_string += f'data: {start.data}, next: {None}'
            start = start.next
        return f'LinkedList[length = {self.length}, [{elems_string}]]'

    def pop(self):
        if self.length == 0:
            raise IndexError("LinkedList is empty!")
        if self.length == 1:
            self.data = None
            self.head = None
            self.length -= 1
        else:
            start = self.head
            while(start.next.next != None):
                start = start.next
            start.next = None
            self.length -= 1

    def change_on_end(self, n, new_data):
        if n > self.length or n <= 0:
            raise KeyError("Element doesn't exist!")
        index = 0
        find_index = self.length - n
        start = self.head
        while(start != None):
            if index == find_index:
                start.data = new_data
                break
            start = start.next
            index+=1

    def clear(self):
        self.length = 0
        start = self.head
        while(start != None):
            start.data = None
            new = start.next
            start.next = None
            start = new