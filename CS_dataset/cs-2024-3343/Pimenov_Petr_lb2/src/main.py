from itertools import islice


class Node:
    def __init__(self, data, next=None):
        self.__data = data
        self.next = next

    def get_data(self):
        return self.__data

    def __str__(self):
        if self.next is None:
            return f'data: {self.get_data()}, next: {self.next}'
        return f'data: {self.get_data()}, next: {self.next.get_data()}'


class LinkedList:
    def __init__(self, head=None):
        self.head = head
        self.length = int(head is not None)

    def __len__(self):
        return self.length

    def append(self, element):
        if len(self) == 0:
            self.head = Node(element)
        else:
            *rest, last = self  # PEP 448
            last.next = Node(element)
        self.length += 1

    def __str__(self):
        if len(self) == 0:
            return 'LinkedList[]'
        return f"LinkedList[length = {len(self)}, [{'; '.join(map(str, self))}]]"

    def pop(self):
        if len(self) == 0:
            raise IndexError('LinkedList is empty!')
        elif len(self) == 1:
            self.head = None
        else:
            *rest, previous, last = self
            previous.next = None
        self.length -= 1

    def delete_on_end(self, n):
        if len(self) < n or n <= 0:
            raise KeyError("Element doesn't exist!")
        if n == 1:
            self.pop()
        elif n == len(self):
            second = self.head.next
            self.head = second
            self.length -= 1
        else:
            target_index = len(self) - n
            first, mid, last = islice(self, target_index - 1, target_index + 2)
            first.next = last
            self.length -= 1

    def clear(self):
        self.head = None
        self.length = 0

    def __iter__(self):
        self.__current = self.head
        return self

    def __next__(self):
        if self.__current is None:
            raise StopIteration
        last = self.__current
        self.__current = self.__current.next
        return last
