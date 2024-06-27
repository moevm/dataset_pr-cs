class Node:
    def __init__(self, data, next=None):
        self.__data__ = data
        self.next = next

    def get_data(self):
        return self.__data__

    def __str__(self):
        if self.next is not None:
            return f'data: {self.__data__}, next: {self.next.get_data()}'
        return f'data: {self.__data__}, next: None'


class LinkedList:
    def __init__(self, head=None):
        self.__head__ = head
        self.__length__ = 1
        if head is None:
            self.__length__ = 0

    def __len__(self):
        return self.__length__

    def append(self, element):
        new = Node(element)
        if self.__len__() == 0:
            self.__head__ = new
            self.__length__ = 1
            return
        curr = self.__head__
        while curr.next is not None:
            curr = curr.next
        curr.next = new
        self.__length__ += 1

    def __str__(self):
        if self.__len__() != 0:
            arr = []
            curr = self.__head__
            while curr is not None:
                arr.append(curr.__str__())
                curr = curr.next
            return f"LinkedList[length = {self.__length__}, [{'; '.join(arr)}]]"
        return 'LinkedList[]'

    def pop(self):
        if self.__len__() != 0:
            curr = self.__head__
            if self.__len__() > 1:
                while curr.next.next is not None:
                    curr = curr.next
                curr.next = None
                self.__length__ -= 1
            else:
                self.clear()
            return
        raise IndexError("LinkedList is empty!")

    def delete_on_start(self, n):
        if 0 < n <= self.__len__():
            if n == self.__len__():
                self.pop()
            elif n != 1:
                counter = 1
                curr = self.__head__
                while counter != n-1:
                    curr = curr.next
                    counter += 1
                curr.next = curr.next.next
                self.__length__ -= 1
            else:
                self.__head__ = self.__head__.next
                self.__length__ -= 1
            return
        raise KeyError("Element doesn't exist!")

    def clear(self):
        self.__head__ = None
        self.__length__ = 0
