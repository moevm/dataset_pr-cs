class Node:
    def __init__(self, data, next=None):
        self.__data = data
        self.next = next

    def get_data(self):
        return self.__data

    def change_data(self, new_data):
        self.__data = new_data

    def __str__(self):
        next_data = self.next.get_data() if self.next else None
        return f"data: {self.__data}, next: {next_data}"


class LinkedList:
    def __init__(self, head=None):
        self.__head__ = head
        self.__length = 1 if head is not None else 0

    def __len__(self):
        return self.__length

    def append(self, element):
        node = Node(element)
        current = self.__head__
        if current is None:
            self.__head__ = node
        else:
            while (current.next != None):
                current = current.next
            current.next = node
        self.__length += 1

    def __str__(self):
        if self.__length == 0:
            return "LinkedList[]"
        else:
            res = []
            current = self.__head__
            while (current is not None):
                res.append(current.__str__())
                current = current.next
            return f"LinkedList[length = {self.__length}, [{'; '.join(res)}]]"

    def pop(self):
        if self.__length == 0:
            raise IndexError('LinkedList is empty!')
        elif self.__length == 1:
            self.__head__ = None
            self.__length = 0
        elif self.__length > 1:
            current = self.__head__
            while (current.next.next is not None):
                current = current.next
            current.next = None
            self.__length -= 1

    def change_on_end(self, n, new_data):
        if self.__length < n or n <= 0:
            raise KeyError(f"{n} doesn't exist!")
        else:
            current = self.__head__
            cnt = 0
            while cnt != self.__length - n:
                current = current.next
                cnt += 1
            current.change_data(new_data)

    def clear(self):
        self.__head__ = None
        self.__length = 0