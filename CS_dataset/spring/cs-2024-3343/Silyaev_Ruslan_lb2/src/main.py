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
        temp = Node(element)
        if self.length == 0:
            self.length = 1
            self.head = temp
            return
        cur = self.head
        while cur.next:
            cur = cur.next     
        self.length += 1
        cur.next = temp


    def __str__(self):
        temp = self.head
        if self.head is None:
            return 'LinkedList[]'
        else:
            value = []
            while temp != None:
                value.append(temp.__str__())
                temp = temp.next
            return f'LinkedList[length = {len(self)}, [{"; ".join(value)}]]'

    def pop(self):
        if self.length == 0:
            raise IndexError('LinkedList is empty!')
        elif self.length == 1:
            self.clear()
        else:
            temp = self.head
            while temp.next.next:
                temp = temp.next
            self.length -= 1
            temp.next = None

    def change_on_start(self, n, new_data):
        temp = self.head
        prev = temp
        cur = Node(new_data)
        if n <= 0 or self.length < n:
            raise KeyError("Element doesn't exist!")
        if n == 1:
            cur.next = self.head.next
            self.head = cur
        else:
            for i in range(n - 1):
                prev = temp
                temp = temp.next
            cur.next = temp.next
            prev.next = cur

    def clear(self):
        self.head = None
        self.length = 0
