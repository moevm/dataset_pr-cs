class Node:
    def __init__(self, data, next=None):
        self.__data = data
        self.next = next

    def get_data(self):
        return self.__data

    def __str__(self):
        if self.next:
            next_data = self.next.get_data()
        else:
            next_data = None
        return 'data: {}, next: {}'.format(self.__data, next_data)


class LinkedList:
    length = 0

    def __init__(self, head=None):
        self.head = head
        if head:
            self.length = 1

    def __len__(self):
        return self.length

    def append(self, element):
        if self.length == 0:
            self.head = Node(element)
            self.length += 1
        else:
            tmp = self.head
            for i in range(self.length):
                if i == self.length - 1:
                    tmp.next = Node(element)
                tmp = tmp.next
            self.length += 1

    def __str__(self):
        if len(self) == 0:
            return 'LinkedList[]'
        else:
            s = 'LinkedList[length = {}, ['.format(self.length)
            tmp = self.head
            for i in range(len(self)):
                if i != len(self) - 1:
                    s = s + tmp.__str__() + '; '
                else:
                    s = s + tmp.__str__() + ']]'
                tmp = tmp.next
            return s

    def pop(self):
        if self.length == 0:
            raise IndexError('LinkedList is empty!')
        else:
            tmp = self.head
            for j in range(self.length - 1):
                if j == self.length - 2:
                    tmp.next = None
                    break
                tmp = tmp.next
            self.length -= 1

    def clear(self):
        self.head = None
        self.length = 0

    def delete_on_start(self, n):
        if n <= 0 or self.length < n:
            raise KeyError("Element doesn't exist!")
        else:
            if n == 1:
                self.head = self.head.next
            else:
                tmp = self.head
                for k in range(self.length):
                    if k == n - 2:
                        tmp.next = tmp.next.next
                        break
                    tmp = tmp.next
            self.length -= 1

