class Node:
    def __init__(self, data, next_=None):
        self._data = data
        self.next = next_ if next_ is not None else None

    def get_data(self):
        return self._data

    def __str__(self):
        next_data = self.next.get_data() if self.next else None
        return f"data: {self._data}, next: {next_data}"


class LinkedList:
    def __init__(self, head=None):
        self._head = head
        self._length = 0 if head is None else 1

    def __len__(self):
        return self._length

    def append(self, element):
        new_node = Node(element)
        if self._head is None:
            self._head = new_node
        else:
            current = self._head
            while current.next:
                current = current.next
            current.next = new_node
        self._length += 1

    def __str__(self):
        if self._head is None:
            return "LinkedList[]"
        else:
            elements = []
            current = self._head
            while current:
                elements.append(
                    f"data: {current.get_data()}, next: {current.next.get_data() if current.next else None}")
                current = current.next
            return f"LinkedList[length = {self._length}, [{'; '.join(elements)}]]"

    def pop(self):
        if self._head is None:
            raise IndexError("LinkedList is empty!")
        elif self._head.next is None:
            self._head = None
        else:
            current = self._head
            while current.next.next:
                current = current.next
            current.next = None
        self._length -= 1

    def clear(self):
        self._head = None
        self._length = 0

    def delete_on_end(self, n):
        if n <= 0 or n > self._length:
            raise KeyError("Element doesn't exist!")
        if n == self._length:
            self._head = self._head.next
        else:
            count = 1
            current = self._head
            while count < self._length - n:
                current = current.next
                count += 1
            current.next = current.next.next
        self._length -= 1