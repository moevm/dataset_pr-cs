class Node:
    data = None
    next = None

    def __init__(self, data, next=None):
        self.data = data
        self.next = next

    def get_data(self):
        return self.data

    def __str__(self):
        return f"data: {self.data}, next: {None if not self.next else self.next.data}"


class LinkedList:
    head = None
    length = 0

    def __init__(self, head=None):
        self.head = Node(head)

    def __len__(self):
        i = 0
        node = self.head
        if(not node or node.data == None):
            return i
        while(node.next):
            i += 1
            node = node.next
        return i + 1

    def append(self, element):
        node = self.head
        if(not node or node.data == None):
            if(not node):
                self.__init__(element)
                return element
            node.data = element
            self.length += 1
            return element

        while(node.next):
            node = node.next
        node.next = Node(element)
        self.length += 1
        return element

    def __str__(self):
        line = f"LinkedList[length = {len(self)}, ["
        node = self.head
        if(not node or node.data == None):
            return "LinkedList[]"
        while(node.next):
            line += f"data: {node.data}, next: {node.next.data}; "
            node = node.next
        line += f"data: {node.data}, next: {node.next}]]"
        return line

    def pop(self):
        node = self.head
        prev_node = node
        if(not node or node.data == None):
            raise IndexError("LinkedList is empty!")
        while(node.next):
            prev_node = node
            node = node.next
        if prev_node.next == None:
            self.head = None
        prev_node.next = None
        return node.data

    def delete_on_end(self, n):
        node = self.head
        prev_node = node
        if(len(self) < n or n <= 0):
            raise KeyError("Element doesn't exist!")
        ind = len(self) - n
        for i in range(ind):
            prev_node = node
            node = node.next
        if prev_node == node:
            self.head = self.head.next
            return node.data
        prev_node.next = node.next
        return node.data

    def clear(self):
        self.head = None
        self.length = 0
