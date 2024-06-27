class Node:
    def __init__(self, data, next=None):
        self.__data = data
        self.next = next

    def get_data(self):
        return self.__data

    def change_data(self, new_data):
        self.__data = new_data

    def __str__(self):
        return f"data: {self.__data}, next: {self.next.get_data() if self.next else None}"


class LinkedList:
    def __init__(self, head=None):
        self.head = head
        self.length = 0 if not head else 1

        if head is not None:
            self.append(head)

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
        if self.length == 0:
            return "LinkedList[]"
        else:
            nodes = []
            current = self.head
            while current:
                nodes.append(current.__str__())
                current = current.next
            return f"LinkedList[length = {self.length}, [{'; '.join(nodes)}]]"

    def pop(self):
        if self.length == 0:
            raise IndexError('LinkedList is empty!')
        if self.length == 1:
            self.clear()
            return
        else:
            current = self.head
            while current.next.next is not None:
                current = current.next
            current.next = None
        self.length -= 1

    def clear(self):
        self.head = None
        self.length = 0

    def change_on_end(self, n, new_data):
        if n > self.length or n <= 0:
            raise KeyError("Element doesn't exist!")
        current = self.head
        for _ in range(self.length - n):
            current = current.next
        current.change_data(new_data)