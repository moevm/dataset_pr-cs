class Node:
    def __init__(self, data, next=None):
        self.__data = data
        self.next = next

    def get_data(self):
        return self.__data

    def change_data(self, new_data):
        self.__data = new_data

    def __str__(self):
        next_data = self.next.get_data() if self.next else "None"
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
        else:
            current = self.head
            nodes = []
            while current:
                node_str = f"data: {current.get_data()}, next: {current.next.get_data() if current.next else 'None'}"
                nodes.append(node_str)
                current = current.next
            return f"LinkedList[length = {self.length}, [{'; '.join(nodes)}]]"

    def pop(self):
        if not self.head:
            raise IndexError("LinkedList is empty!")
        if self.length == 1:
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

    def change_on_end(self, n, new_data):
        if n <= 0 or n > self.length:
            raise KeyError("Element doesn't exist!")
    
        steps_to_move = self.length - n
        current = self.head
        for _ in range(steps_to_move):
            current = current.next
        current.change_data(new_data)
