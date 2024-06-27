class Node:
    def __init__(self, data, next=None):
        self.__data = data
        self.next = next

    def get_data(self):
        return self.__data

    def __str__(self):
        return f"data: {self.get_data()}, next: {self.next.get_data() if self.next else None}"


class LinkedList:
    def __init__(self, head=None):
        self.head = head
        self.length = 1 if self.head else 0

    def __len__(self):
        return self.length

    def append(self, element):
        if not self.head:
            self.head = Node(element)
        else:
            current = self.head
            while current.next:
                current = current.next
            current.next = Node(element)
        self.length += 1

    def __str__(self):
        if not self.head:
            return "LinkedList[]"

        elements = [self.head]
        elements.extend(elements[-1].next for _ in range(self.length - 1))
        return f"LinkedList[length = {self.length}, [{'; '.join(map(str, elements))}]]"

    def pop(self):
        if not self.head:
            raise IndexError("LinkedList is empty!")

        if not self.head.next:
            self.head = None
            self.length -= 1
            return

        current = self.head
        while current.next.next:
            current = current.next
        current.next = None
        self.length -= 1

    def clear(self):
        self.head = None
        self.length = 0

    def delete_on_start(self, n):
        if n > self.length or n < 1:
            raise KeyError("Element doesn't exist!")
        
        if n == 1:
            self.head = self.head.next
            self.length -= 1
            return
        
        position = 1
        current = self.head
        while current.next and position <= n:
            if position == n - 1:
                current.next = current.next.next
                self.length -= 1
                break
            current = current.next
            position += 1
