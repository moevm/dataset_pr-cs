class Node:
    def __init__(self, data, next=None):
        self._data = data
        self.next = next
        pass

    def get_data(self):
        return self._data
        
    def change_data(self, new_data):
        self.data = new_data

    def __str__(self):
        if self.next:
            return f"data: {self._data}, next: {self.next.get_data()}"
        return f"data: {self._data}, next: None"


class LinkedList:
    def __init__(self, head=None):
        if head is None:
            self.head = None
            self.length = 0
        else:
            self.head = head
            self.length = 1

    def __len__(self):
        return self.length

    def append(self, element):
        if self.head is None:
            self.head = Node(element)
        else:
            current = self.head
            while current.next:
                current = current.next
            current.next = Node(element)
        self.length += 1

    def __str__(self):
        if self.head is None:
            return "LinkedList[]"
        else:
            result = "LinkedList[length = {}, [".format(self.length)
            current = self.head
            while current:
                result += f"data: {current.get_data()}, next: {current.next.get_data() if current.next else None}; "
                current = current.next
            return result[:-2] + "]]"

    def pop(self):
        if self.head is None:
            raise IndexError("LinkedList is empty!")
        elif self.length == 1:
            self.head = None
            self.length = 0
        else:
            current = self.head
            while current.next.next:
                current = current.next
            current.next = None
            self.length -= 1

    def clear(self):
        self.head = None
        self.length = 0

    def change_on_start(self, n, new_data):
        if n <= 0 or n > self.length:
            raise KeyError("Element doesn't exist!")
        current = self.head
        for _ in range(n-1):
            current = current.next
        current._data = new_data