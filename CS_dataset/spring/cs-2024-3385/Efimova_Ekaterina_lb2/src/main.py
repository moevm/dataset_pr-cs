class Node:
    def __init__(self, data, next=None):
        self.__data = data
        self.next = next

    def get_data(self):
        return self.__data

    def __str__(self):
        if self.next:
            return f"data: {self.__data}, next: {self.next.__data}"
        return f"data: {self.__data}, next: None"


class LinkedList:
    def __init__(self, head=None):
        if head:
            self.head = Node(head)
            self.length = 1
        else:
            self.head = None
            self.length = 0

    def __len__(self):
        return self.length

    def append(self, element):
        self.length += 1
        if self.head is None:
            self.head = Node(element)
        else:
            cur = self.head
            while cur.next:
                cur = cur.next
            cur.next = Node(element)

    def __str__(self):
        if self.head is None:
            return "LinkedList[]"
        else:
            current_node = self.head
            nodes = []
            while current_node:
                nodes.append(str(current_node))
                current_node = current_node.next
            return f"LinkedList[length = {self.length}, [{'; '.join(nodes)}]]"

    def pop(self):
        if not self.head:
            raise IndexError("LinkedList is empty!")
        if self.length == 1:
            self.head = None
        else:
            current_node = self.head
            while current_node.next.next:
                current_node = current_node.next
            current_node.next = None
        self.length -= 1

    def delete_on_start(self, n):
        if self.length < n or n <= 0:
            raise KeyError("Element doesn't exist!")
        if n == 1:
            self.head = self.head.next
        else:
            prev_del = self.head
            for i in range(n - 2):
                prev_del = prev_del.next
            prev_del.next = prev_del.next.next
        self.length -= 1

    def clear(self):
        self.head = None
        self.length = 0
