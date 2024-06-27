class Node:
    def __init__(self, data, next=None):
        self.__data = data
        self.next = next

    def get_data(self):
        return self.__data

    def change_data(self, new_data):
        self.__data = new_data

    def __str__(self):
        if self.next == None:
            return f"data: {self.__data}, next: None"
        else:
            return f"data: {self.__data}, next: {self.next.get_data()}"


class LinkedList:
    def __init__(self, head=None):
        if head == None:
            self.__head = None
            self.__length = 0
        else:
            self.__head = Node(head, None)
            self.__length = 1

    def __len__(self):
        return self.__length

    def append(self, element):
        if self.__length == 0:
            self.__head = Node(element, None)
        else:
            tmp = self.__head
            for i in range(self.__length - 1):
                tmp = tmp.next
            tmp.next = Node(element, None)
        self.__length += 1

    def __str__(self):
        if self.__length == 0:
            return "LinkedList[]"
        else:
            s = f"LinkedList[length = {self.__length}, ["
            tmp = self.__head
            for i in range(self.__length):
                s += str(tmp) + "; "
                tmp = tmp.next
            return s[:-2] + "]]"

    def pop(self):
        if self.__length == 0:
            raise IndexError("LinkedList is empty!")
        else:
            tmp = self.__head
            for i in range(self.__length - 2):
                tmp = tmp.next
            tmp.next = None
            self.__length -= 1

    def change_on_start(self, n, new_data):
        if n <= 0 or n > self.__length:
            raise KeyError("Element doesn't exist!")
        else:
            tmp = self.__head
            for i in range(n - 1):
                tmp = tmp.next
            tmp.change_data(new_data)

    def clear(self):
        self.__head = None
        self.__length = 0
