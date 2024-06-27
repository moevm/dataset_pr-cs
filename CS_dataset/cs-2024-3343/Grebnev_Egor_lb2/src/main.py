class Node:
    def __init__(self, data, next=None):
        self.__data = data
        self.next = next

    def get_data(self):
        return self.__data

    def __str__(self):
        return f"data: {self.__data}, next: {self.next.get_data() if self.next else None}"


class LinkedList:
    def __init__(self, head=None):
        self.head = head
        self.length = 0 if head is None else 1

    def __len__(self):
        return self.length

    def append(self, element):
        node = Node(element)
        if not self.head:
            self.head = node
        else:
            current = self.head
            while current.next:
                current = current.next
            current.next = node
        self.length += 1

    def __str__(self):
        if not self.head:
            return "LinkedList[]"
        current = self.head
        node_strings = []
        while current:
            node_strings.append(current.__str__())
            current = current.next
        return f"LinkedList[length = {len(node_strings)}, [{'; '.join(node_strings)}]]"

    def pop(self):
        if not self.head:
            raise IndexError("LinkedList is empty!")
        elif not self.head.next:
            data = self.head.get_data()
            self.head = None
            self.length = 0
            return data
        else:
            current = self.head
            while current.next.next:
                current = current.next
            data = current.next.get_data()
            current.next = None
            self.length -= 1
            return data

    def clear(self):
        self.head = None
        self.length = 0

    def delete_on_end(self, n):
        if not self.head:
            raise KeyError("Element doesn't exist!")

        current = self.head
        if n > self.length or n < 1:
            raise KeyError("Element doesn't exist!")

        position = self.length - n

        if position == 0:
            self.head = self.head.next
            self.length -= 1
            return
        current = self.head
        for _ in range(position - 1):
            current = current.next

        current.next = current.next.next
        self.length -= 1