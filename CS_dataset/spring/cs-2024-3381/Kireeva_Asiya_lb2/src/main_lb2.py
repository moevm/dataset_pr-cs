class Node:
    def __init__(self, data, next=None):
        self.__data = data
        self.next = next

    def get_data(self):
        return self.__data

    def __str__(self):
        if self.next:
            return f"data: {self.__data}, next: {self.next.__data}"
        else:
            return f"data: {self.__data}, next: {self.next}"


class LinkedList:
    def __init__(self, head=None):
        self.head = head
        if head is None:
            self.length = 0
        else:
            self.length = 1

    def __len__(self):
        return self.length

    def append(self, element):
        node = Node(element)
        tmp = self.head
        if tmp is None:
            self.head = node
        else:
            while tmp.next:
                tmp = tmp.next
            tmp.next = node
        self.length += 1

    def __str__(self):
        if self.length == 0:
            return "LinkedList[]"
        else:
            s = []
            tmp = self.head
            while tmp:
                s.append(tmp.__str__())
                tmp = tmp.next
            return f"LinkedList[length = {self.length}, [" + "; ".join(s) + "]]"

    def pop(self):
        if self.length == 0:
            raise IndexError("LinkedList is empty!")
        elif self.length == 1:
            self.head = None
            self.length = 0
        else:
            tmp = self.head
            while tmp.next.next:
                tmp = tmp.next
            tmp.next = None
            self.length -= 1

    def clear(self):
        tmp2 = self.head
        tmp = tmp2.next
        while tmp:
            tmp2.next = None
            tmp2 = tmp
            tmp = tmp.next
        self.length = 0

    def delete_on_end(self, n):
        if self.length < n or n < 1:
            raise KeyError("Element doesn't exist!")
        else:
            if n == self.length:
                self.head = self.head.next
            else:
                count = 1
                tmp = self.head
                while tmp:
                    if count == self.length - n:
                        tmp.next = tmp.next.next
                    tmp = tmp.next
                    count += 1
            self.length -= 1