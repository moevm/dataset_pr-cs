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
            return f'data: {self.data}, next: {self.next.get_data()}'
        else:
            return f'data: {self.data}, next: None'

class LinkedList:
    def __init__(self, head=None):
        self.head = head
        self.length = len(self)
    def __len__(self):
        l = 0
        head = self.head
        while head != None:
            l += 1
            head = head.next
        return l
    def append(self, element):
        new = Node(element)
        if len(self) == 0:
            self.__init__(new)
        else:
            head = self.head
            for i in range(len(self) - 1):
                head = head.next
            head.next = new
    def __str__(self):
        if len(self) == 0:
            return 'LinkedList[]'
        else:
            data = []
            head = self.head
            while head != None:
                data.append(str(head))
                head = head.next
            answer = '; '.join(data)
            return f'LinkedList[length = {len(self)}, [{answer}]]'
    def pop(self):
        if len(self) == 0:
            raise IndexError("LinkedList is empty!")
        elif len(self) == 1:
            self.head = None
        else:
            head = self.head
            for i in range(len(self) - 2):
                head = head.next
            head.next = None
    def clear(self):
        self.head = None
    def change_on_end(self, n, new_data):
        if len(self) < n or n <= 0:
            raise KeyError("Element doesn't exist!")
        else:
            head = self.head
            for i in range(len(self) - n):
                head = head.next
            head.change_data(new_data)