class Node:
    def __init__(self, data, next = None):
        self.next = next
        self.__data = data

    def get_data(self):
        return self.__data

    def change_data(self, new_data):
        self.__data = new_data

    def __str__(self):
        if self.next == None:
            return f"data: {self.__data}, next: {self.next}"
        else: return f"data: {self.get_data()}, next: {self.next.get_data()}"

class LinkedList:
    def __init__(self, head = None):
        self.head = head
        if self.head == None:
            self.length = 0
        else: self.length = 1

    def __len__(self):
        return self.length

    def append(self, element):
        new_node = Node(element)
        if self.length == 0:
            self.head = new_node
            self.length += 1
            return
        current = self.head
        while current.next:
            current = current.next
        current.next = new_node
        self.length += 1

    def __str__(self):
        if self.length == 0:
            return "LinkedList[]"
        else:
            s = f"LinkedList[length = {self.length}, ["
            current = self.head
            while current.next:
                s += f"{str(current)}; "
                current = current.next
            s += f"{str(current)}]]"
            return s
        
    def pop(self):
        if self.length == 0:
            raise IndexError("LinkedList is empty!")
        elif self.length == 1:
            self.head = None
            self.length -= 1
        else:
            current = self.head
            while current.next.next:
                current = current.next
            current.next = None
            self.length -= 1

    def change_on_end(self, n, new_data):
        if self.length < n or n <= 0:
            raise KeyError("Element doesn't exist!")
        else:
            current = self.head
            for i in range(self.length - n):
                current = current.next
            current.change_data(new_data)

    def clear(self):
        self.head = None
        self.length = 0
