class Node:
    def __init__(self, data=None, next=None):
        self.__data = data
        self.next = next

    def get_data(self):
        return self.__data

    def change_data(self, new_data):
        self.__data = new_data

    def __str__(self):
        return f'data: {self.__data}, next: {self.next.get_data() if self.next else None}'


class LinkedList:
    def __init__(self, head=None):
        self.head = Node()
        self.length = 1 if head else 0

    def __len__(self):
        return self.length

    def append(self, element):
        if self.length == 0:
            self.head = Node(element)
        else:
            tmp = self.head
            for i in range(self.length - 1):
                tmp = tmp.next

            tmp.next = Node(element)

        self.length += 1

    def get_nodes(self):
        nodes = []
        tmp = self.head
        for i in range(self.length):
            nodes.append(str(tmp))
            tmp = tmp.next

        return nodes

    def __str__(self):
        if self.length == 0:
            return 'LinkedList[]'

        return f'LinkedList[length = {self.length}, [{"; ".join(self.get_nodes())}]]'

    def pop(self):
        if self.length == 0:
            raise IndexError('LinkedList is empty!')

        if self.length == 1:
            self.head = None
        else:
            tmp = self.head
            for i in range(self.length - 2):
                tmp = tmp.next

            tmp.next = None

        self.length -= 1

    def clear(self):
        for i in range(self.length):
            self.pop()

    def change_on_start(self, n, new_data):
        if self.length < n or n < 1:
            raise KeyError("Element doesn't exist!")

        if n == 1:
            self.head.change_data(new_data)
        else:
            tmp = self.head
            for i in range(n - 1):
                tmp = tmp.next

            tmp.change_data(new_data)
            
