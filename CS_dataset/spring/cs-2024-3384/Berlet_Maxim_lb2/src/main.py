class Node:
    def __init__(self, data, next=None):
        self.__data = data
        self.next = next

    def get_data(self):
        return self.__data

    def change_data(self, new_data):
        self.__data = new_data

    def __str__(self):
        return f"data: {self.__data}, next: {self.next.__data if self.next is not None else None}"


class LinkedList:
    def __init__(self, head=None):
        self.length = 0
        self.head = head

    def __len__(self):
        return self.length

    def append(self, element):
        if self.head is None or self.length == 0:
            self.head = Node(element)
            self.length += 1
        else:
            cur = self.head
            while cur.next is not None:
                cur = cur.next
            cur.next = Node(element)
            self.length += 1

    def __str__(self):
        if self.head is None or self.length == 0:
            return "LinkedList[]"

        cur = self.head
        s = [cur.__str__()]
        while cur.next is not None:
            cur = cur.next
            s.append(cur.__str__())
        tmp = "; ".join(s)
        return f"LinkedList[length = {self.length}, [{tmp}]]"

    def pop(self):
        if self.length == 0:
            raise IndexError("LinkedList is empty!")

        elif self.length == 1:
            self.head = self.head.next
            self.length -= 1
        else:
            cur = self.head
            while cur.next.next is not None:
                cur = cur.next
            cur.next = None
            self.length -= 1

    def change_on_start(self, n, new_data):
        if n > self.length or n <= 0:
            raise KeyError("Element doesn't exist!")

        cur = self.head
        for i in range(1, n):
            cur = cur.next
        cur.change_data(new_data)

    def clear(self):
        self.head = None
        self.length = 0
