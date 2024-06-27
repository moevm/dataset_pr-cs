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
        self.length = 0
        if head is None:
            self.head = None
        else:
            self.head = Node(head)

    def __len__(self):
        c = 0
        curr = self.head
        while curr:
            c += 1
            curr = curr.next
        return c

    def append(self, element):
        new_node = Node(element)
        if self.head is None:
            self.head = new_node
        else:
            curr = self.head
            while curr.next:
                curr = curr.next
            curr.next = new_node
        self.length += 1

    def __str__(self):
        if self.head is None:
            return "LinkedList[]"
        else:
            current = self.head
            elements = []
            while current is not None:
                next_data = current.next.get_data() if current.next else None
                elements.append(f"data: {current.get_data()}, next: {next_data}")
                current = current.next
            elements_str = "; ".join(elements)
            return f"LinkedList[length = {len(self)}, [{elements_str}]]"

    def pop(self):
        if self.head is None:
            raise IndexError("LinkedList is empty!")
        elif self.head.next is None:
            self.head = None
        else:
            curr = self.head
            while curr.next.next:
                curr = curr.next
            curr.next = None
        self.length -= 1

    def delete_on_end(self, n):
        if len(self) < n or n <= 0:
            raise KeyError("Element doesn't exist!")
        elif n == len(self):
            self.head = self.head.next
        else:
            curr = self.head
            for i in range(len(self) - n - 1):
                curr = curr.next
            if curr.next != None:
                curr.next = curr.next.next
        self.length -= 1

    def clear(self):
        self.head = None
        self.length = 0
