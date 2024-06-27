class Node:

    def __init__(self, data, next=None):
        self.__data = data
        self.next = next

    def get_data(self):
        return self.__data

    def __str__(self):
        return f"data: {self.__data}, next: {self.next.__data if (self.next is not None) else None}"


class LinkedList:

    def __init__(self, head=None):
        self.head = head
        self.length = 1

        if self.head is None:
            self.length = 0

    def __len__(self):
        return self.length

    def append(self, element):

        if self.head is None:
            self.head = Node(element)

        else:
            pointer = self.head

            while pointer.next is not None:
                pointer = pointer.next
            else:
                pointer.next = Node(element)

        self.length += 1

    def pop(self):

        if self.length == 0:
            raise IndexError("LinkedList is empty!")

        if self.length == 1:
            self.head = None

        else:
            pointer = self.head

            while pointer.next.next is not None:
                pointer = pointer.next
            else:
                pointer.next = None
        self.length -= 1

    def delete_on_end(self, n):

        if self.length == 0 or n > self.length or n <= 0:
            raise KeyError("Element doesn't exist!")

        pointer = self.head
        n = self.length - n
        number = 0

        if n == 0:
            self.head = self.head.next

        else:
            while number != n-1:
                pointer = pointer.next
                number += 1
            pointer.next = pointer.next.next

        self.length -= 1



    def clear(self):
        self.head = None
        self.length = 0

    def __str__(self):
        if self.length == 0:
            return "LinkedList[]"

        pointer = self.head
        info = ""
        while True:
            info += f"{pointer}; "
            if pointer.next is None:
                break
            pointer = pointer.next
        info = info[0:-2]

        return f"LinkedList[length = {self.length}, [{info}]]"

