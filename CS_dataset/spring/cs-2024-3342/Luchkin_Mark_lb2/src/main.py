class Node:
    def __init__(self, data, next=None):
        self.__data = data
        self.next = next

    def get_data(self):
        return self.__data

    def __str__(self):
        if self.next is not None:
            return f'data: {self.get_data()}, next: {self.next.get_data()}'
        return f'data: {self.get_data()}, next: {None}'


class LinkedList:
    def __init__(self, head=None):
        self.head = head
        if head is not None:
            self.length = 1
        else:
            self.length = 0

    def __len__(self):
        return self.length

    def append(self, element):
        new = Node(element)
        if self.head is not None:
            curr = self.head
            while curr.next is not None:
                curr = curr.next
            curr.next = new
        else:
            self.head = new

        self.length += 1

    def __str__(self):
        if self.head is None:
            return f'LinkedList[]'
        else:
            res_list = []
            curr = self.head
            while curr is not None:
                res_list.append(str(curr))
                curr = curr.next
            return f'LinkedList[length = {self.length}, [{"; ".join(res_list)}]]'

    def pop(self):
        if self.length == 1:
            self.head = None


        elif self.head is None:
            raise IndexError('LinkedList is empty!')

        else:
            curr = self.head
            while curr.next.next is not None:
                curr = curr.next
            curr.next = None

        self.length -= 1

    def delete_on_end(self, n):
        if n <= 0 or n > self.length:
            raise KeyError("Element doesn't exist!")
        elif n == self.length:
            self.head = self.head.next
        else:
            curr = self.head
            for i in range(self.length - n - 1):
                curr = curr.next
            curr.next = curr.next.next

        self.length -= 1

    def clear(self):
        self.head = None
        self.length = 0
