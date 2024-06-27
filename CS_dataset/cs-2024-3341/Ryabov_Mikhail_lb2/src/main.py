class Node:
    def __init__(self, data, next=None):
        self.__data = data
        self.next = next

    def get_data(self):
        return self.__data

    def __str__(self):
        if self.next is None:
            return f"data: {self.get_data()}, next: None"
        else:
            return f"data: {self.get_data()}, next: {self.next.get_data()}"


class LinkedList:

    def __init__(self, head=None):
        self.head = head
        self.length = 1 if head is not None else 0

    def __len__(self):
        return self.length

    def append(self, element):
        self.length += 1
        if self.length == 1:
            self.head = Node(element)
        else:
            current = self.head
            while current.next is not None:
                current = current.next
            current.next = Node(element)

    def __str__(self):
        if self.length == 0:
            return "LinkedList[]"
        else:
            s = f"LinkedList[length = {self.length}, ["
            current = self.head
            while current.next is not None:
                s += f"{current.__str__()}; "
                current = current.next
            s += current.__str__()
            s += "]]"
        return s

    def pop(self):
        if self.length == 0:
            raise IndexError("LinkedList is empty!")
        elif self.length == 1:
            self.head = None
            self.length -= 1
        else:
            current, del_elem = self.head, self.head
            while del_elem.next is not None:
                del_elem = del_elem.next
            while current.next != del_elem:
                current = current.next
            current.next = None
            self.length -= 1

    def delete_on_end(self, n):
        if n > self.length or n <= 0:
            raise KeyError("Element doesn't exist!")
        elif n == self.length:
            self.head = self.head.next
            self.length -= 1
        else:
            current = self.head
            current_n = self.length
            while (current_n - 1) != n:
                current_n -= 1
                current = current.next
            current.next = current.next.next
            self.length -= 1

    def clear(self):
        self.head = None
        self.length = 0
