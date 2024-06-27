class Node:
    def __init__(self, data, next=None):
        self.__data = data
        self.next = next

    def get_data(self):
        return self.__data

    def __str__(self):
        next_data = self.next.get_data() if self.next else None
        return f"data: {self.__data}, next: {next_data}"

class LinkedList:
    def __init__(self, head=None):
        self.head = head
        self.length = 0 if head is None else 1

    def __len__(self):
        return self.length

    def append(self, element):
        new_node = Node(element)
        if not self.head:
            self.head = new_node
        else:
            current = self.head
            while current.next:
                current = current.next
            current.next = new_node
        self.length += 1

    def __str__(self):
        if not self.head:
            return "LinkedList[]"
        
        result = f"LinkedList[length = {self.length}, ["
        current = self.head
        while current:
            result += str(current)
            if current.next:
                result += "; "
            current = current.next
        result += "]]"
        return result

    def pop(self):
        if not self.head:
            raise IndexError("LinkedList is empty!")
        if self.head.next is None:
            self.head = None
        else:
            current = self.head
            while current.next and current.next.next:
                current = current.next
            current.next = None
        self.length -= 1

    def clear(self):
        self.head = None
        self.length = 0
    def delete_on_end(self, n):
        if n <= 0:
            raise KeyError("Element doesn't exist!")
        if n > self.length:
            raise KeyError("Element doesn't exist!")
        
        index_from_start = self.length - n
        if index_from_start == 0:
            self.head = self.head.next
        else:
            current = self.head
            for _ in range(index_from_start - 1):
                current = current.next
            current.next = current.next.next
        self.length -= 1