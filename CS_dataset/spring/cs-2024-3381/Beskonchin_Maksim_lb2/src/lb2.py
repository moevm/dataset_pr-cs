class Node:
    def __init__(self, data, next=None):
        self.__data = data
        self.next = next

    def get_data(self):
        return self.__data

    def change_data(self, new_data):
        self.__data = new_data

    def __str__(self):
        return f"data: {self.get_data()}, next: {self.next.get_data() if self.next else None}"


class LinkedList:
    def __init__(self, head=None):
        self.head = head

    def __len__(self):
        if self.head is None:
            return 0
        count = 1
        node = self.head
        while node.next:
            node = node.next
            count += 1
        return count

    def append(self, element):
        if self.head is None:
            self.head = Node(element)
            return
        node = self.head
        while node.next:
            node = node.next
        node.next = Node(element)

    def __str__(self):
        if self.head is None:
            return "LinkedList[]"
        node = self.head
        result = f"LinkedList[length = {len(self)}, [data: {node.get_data()}, next: {node.next.get_data() if node.next else None}"
        while node.next:
            node = node.next
            result += f'; data: {node.get_data()}, next: {node.next.get_data() if node.next else None}'
        result += ']]'
        return result

    def pop(self):
        if self.head is None:
            raise IndexError("LinkedList is empty!")
        if self.head.next is None:
            self.head = None
            return
        node = self.head
        while node.next.next:
            node = node.next
        node.next = None

    def change_on_end(self, n, new_data):
        if n < 1 or n > len(self):
            raise KeyError("Element doesn't exist!")
        node = self.head
        for _ in range(len(self) - n):
            node = node.next
        node.change_data(new_data)

    def clear(self):
        while self.head:
            self.pop()