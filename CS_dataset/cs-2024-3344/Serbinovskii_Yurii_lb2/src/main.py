class Node:
    def __init__(self, __data, next=None):
        self.__data = __data
        self.next = next
    def get_data(self):
        return self.__data
    def change_data(self, new_data):
        self.__data = new_data
    def __str__(self):
        if self.next:
            return f"data: {self.__data}, next: {self.next.__data}"
        return f"data: {self.__data}, next: None"
class LinkedList:
    def __init__(self, _head=None):
        self._head = _head
        self._length = 0
        tmp = self._head
        while tmp:
            self._length += 1
            tmp = tmp.next
    def __len__(self):
        return self._length
    def append(self, element):
        if self._head:
            tmp = self._head
            while tmp.next:
                tmp = tmp.next
            tmp.next = Node(element, None)
        else:
            self._head = Node(element, None)
        self._length += 1
    def __str__(self):
        if self._length == 0:
            return "LinkedList[]"
        else:
            rtr_str = f"LinkedList[length = {self._length}, ["
            tmp = self._head
            while tmp.next:
                rtr_str += tmp.__str__() + "; "
                tmp = tmp.next
            rtr_str += tmp.__str__() + "]]"
            return rtr_str
    def pop(self):
        if self._length == 0:
            raise IndexError("LinkedList is empty!")
        elif self._length == 1:
            self._head = None
            self._length -= 1
        else:
            tmp = self._head
            while tmp.next.next:
                tmp = tmp.next
            tmp.next = None
            self._length -= 1
    def clear(self):
        self._head = None
        self._length = 0
    def change_on_start(self, n, new_data):
        if self._length < n or n <= 0:
            raise KeyError("Element doesn't exist!")
        else:
            tmp = self._head
            for i in range(n-1):
                tmp = tmp.next
            tmp.change_data(new_data)
