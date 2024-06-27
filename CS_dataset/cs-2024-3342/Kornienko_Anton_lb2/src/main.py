class Node:
    def __init__(self, data, next=None):
        self.__data = data
        self.next = next

    def get_data(self):
        return self.__data

    def __str__(self):
        if self.next is None:
            return f"data: {self.__data}, next: None"
        else:
            return f"data: {self.__data}, next: {self.next.get_data()}"


class LinkedList:
    def __init__(self, head=None):
        self.head = None
        if head is not None:
            self.length = 1
            self.head = Node(head)
        else:
            self.length = 0

    def __len__(self):
        return self.length

    def append(self, element):
        if self.length != 0:
            self.length += 1
            node = Node(element)
            current = self.head
            while current.next is not None:
                current = current.next
            current.next = node
        else:
            self.length += 1
            self.head = Node(element)

    def __str__(self):
        if self.length == 0:
            return "LinkedList[]"
        else:
            string = f"LinkedList[length = {self.length}, ["
            current = self.head
            while current is not None:
                if current.next is None:
                    string += f"data: {current.get_data()}, next: None; "
                else:
                    string += f"data: {current.get_data()}, next: {current.next.get_data()}; "
                current = current.next

            string = string[:len(string) - 2]
            string += "]]"
            return string

    def pop(self):
        if self.length == 0:
            raise IndexError("LinkedList is empty!")
        else:
            if self.head.next is not None:
                self.length -= 1
                current = self.head
                while current.next.next is not None:
                    current = current.next

                current.next = None
            else:
                self.head = None
                self.length = 0

    def delete_on_start(self, n):
        if self.length < n or n <= 0:
            raise KeyError("Element doesn't exist!")
        elif n == self.length:
            self.pop()
        elif n == 1:
            self.length -= 1
            self.head = self.head.next
        else:
            self.length -= 1
            current = self.head
            for i in range(n - 2):
                current = current.next

            current.next = current.next.next

    def clear(self):
        while self.length != 0:
            self.pop()


