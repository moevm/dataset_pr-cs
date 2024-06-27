class Node:
    def __init__(self, data, next=None):
        self.__data = data
        self.next = next

    def get_data(self):
        return self.__data

    def change_data(self, data):
        self.__data = data

    def __str__(self):
        if self.next is not None:
            return f'data: {self.__data}, next: {self.next.get_data()}'
        return f'data: {self.__data}, next: {self.next}'


class LinkedList:
    def __init__(self, head=None):
        self.head = head
        self.length = 0

    def __len__(self):
        return self.length

    def append(self, element):
        node = Node(element)
        if self.head is None:
            self.head = node
            self.length += 1
        else:
            item = self.head
            while item:
                if item.next is None:
                    item.next = node
                    self.length += 1
                    break
                item = item.next

    def pop(self):
        if self.length == 0:
            raise IndexError('LinkedList is empty!')
        self.length -= 1
        if self.length == 0:
            self.head = None
        else:
            current = self.head
            for i in range(self.length - 1):
                current = current.next
            current.next = None

    def clear(self):
        self.head = None
        self.length = 0

    def delete_on_start(self,n):
        if n > self.length or n < 1:
            raise KeyError("Element doesn't exist!")
        if n == 1:
            self.head = self.head.next
        else:
            current = self.head
            for i in range(n - 2):
                current = current.next
            current.next = current.next.next
        self.length -= 1

    def __str__(self):
        if self.length == 0:
            return 'LinkedList[]'
        items = []
        item = self.head
        while item:
            items.append(f'data: {item.get_data()}, next: {item.next.get_data() if item.next else None}')
            item = item.next
        return f"LinkedList[length = {self.length}, [{'; '.join(items)}]]"
