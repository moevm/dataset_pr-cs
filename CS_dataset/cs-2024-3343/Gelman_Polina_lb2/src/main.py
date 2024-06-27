class Node:
    def __init__(self, data, next=None):
        self.__data = data
        self.next = next

    def get_data(self):
        return self.__data

    def change_data(self, new_data):
        self.__data = new_data

    def __str__(self):
        if self.next:
            return f"data: {self.__data}, next: {self.next.get_data()}"
        else:
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
        new_node = Node(element)
        if self.head is None:
            self.head = new_node
        else:
            current = self.head
            while current.next:
                current = current.next
            current.next = new_node
        self.length += 1

    def __str__(self):
        if not hasattr(self, 'head') or self.head is None or self.length == 0:
            return "LinkedList[]"
        else:
            current = self.head
            nodes = []
            while current:
                nodes.append(current.__str__())
                current = current.next

            return f"LinkedList[length = {self.length}, [{'; '.join(nodes)}]]"


    def pop(self):
        if self.length == 0:
            raise IndexError("LinkedList is empty!")
        elif self.length == 1:
            self.head = None
            self.length = 0

        else:
            current = self.head
            while current.next.next:
                current = current.next
            self.length -= 1
            current.next = None


    def change_on_start(self, n, new_data):
        if self.length < n or n <= 0:
            raise KeyError("Element doesn't exist!")

        current = self.head
        tmp = self.head
        for _ in range(n-1):
            current = current.next
        current.change_data(new_data)

    def clear(self):
        self.head = None
        self.length = 0

