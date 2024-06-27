class Node:
    def __init__(self, data, next = None):
        self.__data = data
        self.next = next

    def get_data(self):
        return self.__data

    def __str__(self):
        if self.next != None:
            return f"data: {self.__data}, next: {self.next.__data}"
        return f"data: {self.__data}, next: {self.next}"


class LinkedList:
    def __init__(self, head = None):
        self.__head = head
        self.length = len(self)

    def __len__(self):
        i = 0
        current = self.__head
        while current:
            i += 1
            current = current.next
        return i

    def append(self, element):
        new = Node(element)
        if self.__head is None:
            self.__head = new
        else:
            current = self.__head
            while current.next:
                current = current.next
            current.next = new
        self.length += 1

    def __str__(self):
        if self.__head is None:
            return "LinkedList[]"
        else:
            current = self.__head
            elems = f'{current}'
            while current.next is not None:
                current = current.next
                elems += "; " + current.__str__()
            return f'LinkedList[length = {self.length}, [{elems}]]'

    def pop(self):
        if self.__head is None:
            raise IndexError("LinkedList is empty")
        elif self.length == 1:
            self.__head = None
        else:
            current = self.__head
            while current.next.next is not None:
                current = current.next
            current.next = None
        self.length -= 1

    def delete_on_start(self, n):
        if self.length < n or n < 1 :
            raise KeyError("Element doesn't exist!")
        elif n == 1:
            self.__head = self.__head.next
        else:
            i = 1
            current = self.__head
            while i != n-1:
                i += 1
                current = current.next
            current.next = current.next.next
        self.length -= 1

    def clear(self):
        self.__head = None
        self.length = 0
