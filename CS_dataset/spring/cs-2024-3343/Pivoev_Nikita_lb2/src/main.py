class Node:
    def __init__(self, data, next = None):
        self.__data = data
        self.next = next

    def get_data(self):
        return self.__data

    def change_data(self, new_data):
        self.__data = new_data

    def __str__(self):
        return f'data: {self.__data}, next: {None if self.next is None else self.next.get_data()}'


class LinkedList():
    def __init__(self, head=None):
        if head is None:
            self.length = 0
            self.head = None

        else:
            self.length = 1
            self.head = Node(head)

    def __len__(self):
        return self.length

    def append(self, element):
        pt = Node(element)
        if self.length == 0:
            self.length = 1
            self.head = pt
            return

        current = self.head
        while current.next:
            current = current.next
        
        self.length += 1
        current.next = pt

    def __str__(self):
        pt = self.head
        if self.head is None:
            return 'LinkedList[]'

        else:
            value = []
            while pt != None:
                value.append(pt.__str__())
                pt = pt.next
            return f'LinkedList[length = {len(self)}, [{"; ".join(value)}]]'

    def pop(self):
        if self.length == 0:
            raise IndexError('LinkedList is empty!')

        elif self.length == 1:
            self.clear()

        else:
            pt = self.head
            while pt.next.next:
                pt = pt.next

            self.length -= 1
            pt.next = None
            
    def clear(self):
        self.length = 0
        self.head = None

    def change_on_start(self, n, new_data):
        pt = self.head
        previous = pt
        current = Node(new_data)

        if n <= 0 or self.length < n:
            raise KeyError("Element doesn't exist!")
        
        if n == 1:
            current.next = self.head.next
            self.head = current

        else:
            for i in range(n - 1):
                previous = pt
                pt = pt.next
            current.next = pt.next
            previous.next = current