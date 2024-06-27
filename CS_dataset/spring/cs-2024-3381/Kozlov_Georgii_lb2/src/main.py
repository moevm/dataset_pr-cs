class Node:
    def __init__(self, data, next=None):
        self.__data = data
        self.next = next

    def get_data(self):
        return self.__data

    def __str__(self):
        if self.next is not None:
            return f"data: {self.__data}, next: {self.next.__data}"
        return f"data: {self.__data}, next: {self.next}"


class LinkedList:
    def __init__(self, head = None):
        self.head = head
        if head is None:
            self.length = 0
        else:
            self.length = 1
            tmp = head
            while tmp.next is not None:
                tmp = tmp.next
                self.length += 1
            

    def __len__(self):
        return self.length

    def append(self, element):
        if self.length >= 1:
            node = Node(element, None)
            tmp = self.head
            while tmp.next is not None:
                tmp = tmp.next
            tmp.next = node
            self.length += 1
        else:
            self.head = Node(element, None)
            self.length = 1

            
    def __str__(self):
        if self.length == 0:
            return "LinkedList[]"
        else:
            array = []
            tmp = self.head
            while tmp.next is not None:
                array.append(f"data: {tmp.get_data()}, next: {tmp.next.get_data()}")
                tmp = tmp.next
            array.append(f"data: {tmp.get_data()}, next: None")
            return f"LinkedList[length = {self.length}, [{'; '.join(array)}]]"
        
    def pop(self):
        if self.length == 0:
            raise IndexError("LinkedList is empty!")
        elif self.length == 1:
            self.length -= 1
            self.head = None
        else:
            last = self.head
            tmp = self.head.next
            while tmp.next is not None:
                last = tmp
                tmp = tmp.next
            last.next = None
            self.length -= 1

    def delete_on_start(self, n):
        if self.length < n or n < 1:
            raise KeyError("Element doesn't exist!")
        elif n == 1:
            self.head = self.head.next
            self.length -= 1
        elif n == self.length:
            self.pop()
        else:
            last = self.head
            tmp = self.head.next
            idx = 2
            while idx != n:
                last = tmp
                tmp = tmp.next
                idx += 1
            last.next = tmp.next
            self.length -= 1

    def clear(self):
        self.length = 0
        self.head = None
