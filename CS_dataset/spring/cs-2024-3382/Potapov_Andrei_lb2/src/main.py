class Node:
    def __init__(self, data, next=None):
        self.__data = data
        self.next = next

    def get_data(self):
        return self.__data

    def __str__(self):
        return f"data: {self.__data}, next: {self.next.get_data() if self.next is not None else None}"


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
            while tmp.next is not None:
                tmp = tmp.next
            tmp.next = node
        self.length += 1

    def __str__(self):
        if self.length == 0:
            return "LinkedList[]"
        else:
            datas = []
            tmp = self.head
            datas.append(str(tmp))
            while tmp.next is not None:
                tmp = tmp.next
                datas.append(str(tmp))
            datas_str = '[' + '; '.join(datas) + ']'
            return f"LinkedList[length = {self.length}, {datas_str}]"

    def pop(self):
        if self.length == 0:
            raise (IndexError("LinkedList is empty!"))
        elif self.length == 1:
            self.head = None
            self.length = 0
        else:
            tmp = self.head
            i = 1
            while i < self.length - 1:
                tmp = tmp.next
                i += 1
            tmp.next = tmp.next.next
            self.length -= 1

    def delete_on_start(self, n):
        if self.length < n or n <= 0:
            raise (KeyError("Element doesn't exist!"))
        elif n == self.length:
            self.pop()
        elif n == 1:
            self.head = self.head.next
            self.length -= 1
        else:
            tmp = self.head
            i = 1
            while i < n - 1:
                tmp = tmp.next
                i += 1
            tmp.next = tmp.next.next
            self.length -= 1

    def clear(self):
        self.head = None
        self.length = 0
