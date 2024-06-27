class Node:
    def __init__(self, data, next=None):
        self._data = data
        self.next = next

    def get_data(self):
        return self._data

    def __str__(self):
        if self.next is not None:
            return f"data: {self.get_data()}, next: {self.next.get_data()}"
        else:
            return f"data: {self.get_data()}, next: None"


class LinkedList:
    def __init__(self, head=None):
        self.head = head
        self.length = len(self)

    def __len__(self):
        c = 0
        temp = self.head
        while temp != None:
            temp = temp.next
            c += 1
        return c

    def append(self, element):
        x = Node(element)
        if self.head == None:
            self.head = x
        else:
            temp = self.head
            while temp.next != None:
                temp = temp.next
            temp.next = x

    def __str__(self):
        if len(self) == 0:
            return "LinkedList[]"
        else:
            temp = self.head
            arr = [str(temp)]
            while temp.next != None:
                temp = temp.next
                arr += [str(temp)]
            arr = "[" + '; '.join(arr) + "]"
            return f"LinkedList[length = {len(self)}, {arr}]"

    def pop(self):
        if len(self) == 0:
            raise IndexError("LinkedList is empty!")
        elif len(self) == 1:
            self.head = None
        else:
            temp = self.head
            while temp.next.next != None:
                temp = temp.next
            temp.next = None

    def delete_on_end(self, n):
        if n <= 0 or n > len(self):
            raise KeyError("Element doesn't exist!")
        elif n == len(self):
            self.head = self.head.next
        else:
            temp = self.head
            for _ in range(len(self) - n - 1):
                temp = temp.next
            temp.next = temp.next.next

    def clear(self):
        self.head = None
