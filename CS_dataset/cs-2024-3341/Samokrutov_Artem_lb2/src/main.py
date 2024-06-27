class Node:
    def __init__(self, data, next=None):
        self.__data = data
        self.next = next

    def get_data(self):
        return self.__data

    def __str__(self):
        return f"data: {self.get_data()}, next: {self.next.get_data() if self.next is not None else None}"


class LinkedList:
    def __init__(self, head=None):
        self.head = head
        self.__length = 0 if head is None else 1

    def __len__(self):
        return self.__length

    def append(self, element):
        node = Node(element)

        if len(self) == 0:
            self.head = node
        else:
            current = self.head

            while current.next is not None:
                current = current.next

            current.next = node

        self.__length += 1

    def __str__(self):
        if (len(self) == 0):
            return "LinkedList[]"
        string = f"LinkedList[length = {len(self)}, ["

        current = self.head
        while (current != None):
            string += str(current)

            if (current.next != None):
                string += "; "

            current = current.next

        string += "]]"

        return string

    def pop(self):
        if self.head is None:
            raise IndexError("LinkedList is empty!")

        if self.__length == 1:
            self.head = None
        else:
            current = self.head

            while current.next.next is not None:
                current = current.next

            current.next = None

        self.__length -= 1

    def clear(self):
        self.head = None
        self.__length = 0

    def delete_on_start(self, n):
        if (n > len(self)) or (n < 1):
            raise KeyError("Element doesn't exist!")

        if n == 1:
            self.head = self.head.next
        else:
            current = self.head

            for _ in range(n - 2):
                current = current.next

            current.next = current.next.next

        self.__length -= 1
