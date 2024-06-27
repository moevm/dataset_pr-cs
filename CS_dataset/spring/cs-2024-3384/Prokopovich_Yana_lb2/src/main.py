class Node:
    def __init__(self, data, next=None):
        self.__data = data
        self.next = next

    def get_data(self):
        return self.__data

    def change_data(self, new_data):
        self.__data = new_data

    def __str__(self):
        if self.next is None:
            return f"data: {self.__data}, next: None"
        return f'data: {self.__data}, next: {self.next.__data}'


class LinkedList:
    def __init__(self, head=None):
        if head is None:
            self.head = None
            self.length = 0
        else:
            self.head = head
            self.length = 1

    def __len__(self):
        return self.length

    def append(self, element):
        self.length += 1
        current = Node(element)
        position = self.head
        if position is None:
            self.head = current
        else:
            while position.next is not None:
                position = position.next
            position.next = current

    def __str__(self):
        if self.length == 0:
            return f"LinkedList[]"
        else:
            result = f"LinkedList[length = {self.length}, ["
            current = self.head
            while current.next is not None:
                result += (current.__str__() + "; ")
                current = current.next
            result += current.__str__() + ']]'
            return result

    def pop(self):
        if self.length > 1:
            current = self.head
            while current.next.next is not None:
                current = current.next
            current.next = None
            self.length -= 1
        elif self.length == 0:
            raise IndexError('Linked list is empty')
        elif self.length == 1:
            self.head = None
            self.length = 0

    def clear(self):
        self.head = None
        self.length = 0

    def change_on_end(self, n, new_data):
        if self.length < n or n <= 0:
            raise KeyError("Element doesn't exist!")
        else:
            index = self.length - n
            count = 0
            current = self.head
            while count != index:
                count += 1
                current = current.next
            current.change_data(new_data)