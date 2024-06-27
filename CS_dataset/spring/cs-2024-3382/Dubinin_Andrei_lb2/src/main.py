class Node:
    def __init__(self, data, next = None):
        self.data = data
        self.next = next

    def get_data(self):
        return self.data

    def __str__(self):
        if self.next: return f'data: {self.data}, next: {self.next.get_data()}'
        else: return f'data: {self.data}, next: None'


class LinkedList:
    def __init__(self, head = None):
        self.head = head
        self.length = 0
        if head: self.length += 1

    def __len__(self):
        return self.length

    def append(self, element):
        new = Node(element)
        if len(self) == 0: self.__init__(new)
        else:
            current = self.head
            while current.next:
                current = current.next
            current.next = new
            self.length += 1
            
    def __str__(self):
        if len(self) == 0: return 'LinkedList[]'
        else:
            list_data = []
            current = self.head
            while current:
                list_data.append(str(current))
                current = current.next
            list_data = '; '.join(list_data)
            return f'LinkedList[length = {len(self)}, [{list_data}]]'

    def pop(self):
        if len(self) == 0: raise IndexError('LinkedList is empty!')
        elif len(self) == 1: self.head = None
        else:
            current = self.head
            for i in range(len(self) - 2): current = current.next
            current.next = None
        self.length -= 1

    def delete_on_start(self, n):
        if len(self) < n or n <= 0: raise KeyError("Element doesn't exist!")
        elif n == 1: self.head = self.head.next
        else:
            current = self.head
            for i in range(n - 2): current = current.next
            if current.next: current.next = current.next.next
        self.length -= 1

    def clear(self):
        self.length = 0
        self.head = None