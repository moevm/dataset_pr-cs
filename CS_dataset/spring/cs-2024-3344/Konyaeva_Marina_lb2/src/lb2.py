class Node:
    def __init__(self, data, next=None):
        self.__data = data
        self.next = next

    def get_data(self):
        return self.__data

    def __str__(self):
        if self.next:
            return (f'data: {self.__data}, next: {self.next.__data}')
        return (f'data: {self.__data}, next: None')


class LinkedList:
    def __init__(self, head=None):
        self.length = 0
        self.head = head
        while head:
            head = head.next
            self.length += 1


    def __len__(self):
        return self.length

    def append(self, element):
        self.length += 1
        if self.head is not None:
            tmp = self.head
            while tmp.next:
                tmp = tmp.next
            tmp.next = Node(element)
        else:
            self.head = Node(element)


    def __str__(self):
        if self.head is not None:
            res = f'LinkedList[length = {self.length}, ['
            tmp = self.head
            while tmp:
                res += str(tmp) + '; '
                tmp = tmp.next
            res = res[:-2] + ']]'
            return res
        else:
            return 'LinkedList[]'

    def pop(self):
        if self.head is None:
            raise IndexError("LinkedList is empty!")
        if self.length == 1:
            self.__init__()
        if self.head is not None:
            tmp = self.head
            while tmp.next.next:
                tmp = tmp.next
            tmp.next = None
            self.length -= 1


    def delete_on_end(self, n):
        if self.length < n or n <= 0:
            raise KeyError("Element doesn't exist!")
        else:
            index = self.length - n
            tmp = self.head
            if index == 0:
                self.head = tmp.next
            else:
                for i in range(1, index):
                    tmp = tmp.next
                tmp.next = tmp.next.next
            self.length -= 1

    def clear(self):
        self.__init__()
