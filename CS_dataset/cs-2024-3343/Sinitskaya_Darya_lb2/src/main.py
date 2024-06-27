class Node:
    def __init__(self, data, next=None):
        self.__data = data
        self.next = next

    def get_data(self):
        return self.__data

    def __str__(self):
        next_data = self.next.__data if self.next is not None else None
        return f"data: {self.__data}, next: {next_data}"


class LinkedList:
    def __init__(self, head=None):
        self.head = head
        self.length = 0 if head is None else 1

    def __len__(self):
        return self.length

    def append(self, element):
        new_node = Node(element)
        if self.head is None:
            self.head = new_node
        else:
            current = self.head
            while current.next is not None:
                current = current.next
            current.next = new_node
        self.length += 1

    def __str__(self):
        if self.head is None:
            return "LinkedList[]"

        def node_to_string(node):
            return str(node)

        current = self.head
        elements = []
        while current is not None:
            elements.append(node_to_string(current))
            current = current.next

        return f"LinkedList[length = {self.length}, [{'; '.join(elements)}]]"

    def pop(self):
        if self.head is None:
            raise IndexError("LinkedList is empty!")

        if self.head.next is None:
            self.head = None
        else:
            current = self.head
            while current.next.next is not None:
                current = current.next
            current.next = None

        self.length -= 1

    def clear(self):
        self.head = None
        self.length = 0
        
    def delete_on_end(self, n):
        if n <= 0 or self.length < n:
            raise KeyError("Element doesn't exist!")
        current = self.head
        end = self.length - n
        position = 0
        if position == end:
            self.head = self.head.next
            self.length -= 1
            return
        while current is not None and position + 1 != end:
            position = position + 1
            current = current.next
        if current is not None:
            current.next = current.next.next
        self.length -= 1
