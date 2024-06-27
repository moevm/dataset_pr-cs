class Node:
    def __init__(self,data,next=None):
        self.__data = data
        self.next = next

    def get_data(self):
        return self.__data

    def change_data(self, new_data):
        self.__data = new_data

    def __str__(self):
        return f"data: {self.__data}, next: {self.next.get_data() if self.next is not None else None}"\

class LinkedList:
    def __init__(self, head=None):
        self.head = head
        self.length = 0
        if head is not None:
            self.length = 1

    def __len__(self):
        return self.length

    def append(self,element):
        new = Node(element)
        if self.head is None:
            self.head = new
            self.length = 1
            return
        temp = self.head
        while temp.next is not None:
            temp = temp.next
        temp.next = new
        self.length += 1

    def __str__(self):
        if self.length == 0:
            return "LinkedList[]"
        elements = list()
        temp = self.head
        while temp is not None:
            elements.append(str(temp))
            temp = temp.next
        return f"LinkedList[length = {self.length}, [{'; '.join(elements)}]]"

    def pop(self):
        if self.length == 0:
            raise IndexError("LinkedList is empty!")
        temp = self.head
        if self.length == 1:
            self.head = None
            self.length = 0
            return
        while temp.next.next is not None:
            temp = temp.next
        temp.next = None
        self.length -= 1

    def clear(self):
        self.head = None
        self.length = 0

    def change_on_start(self, n, new_data):
        if n > self.length or n <= 0:
            raise KeyError("Element doesn't exist!")
        if n == 1:
            new = Node(new_data, next=self.head.next)
            self.head = new
        else:
            temp = self.head
            for i in range(n-2):
                temp = temp.next
            new = Node(new_data, next=temp.next.next)
            temp.next = new
