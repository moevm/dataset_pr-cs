class Node:
    def __init__(self, data, next=None):
        self._data = data
        self.next = next

    def get_data(self):
        return self._data

    def change_data(self, new_data):
        self._data = new_data

    def __str__(self):
        return f"data: {self.get_data()}, next: {self.next.get_data() if self.next else None}"


class LinkedList:
    def __init__(self, head=None):
        self.head = head

    def __len__(self):
        _len = 0
        cursor = self.head
        while cursor:
            _len += 1
            cursor = cursor.next
        return _len

    def append(self, element):
        if self.head is None:
            self.head = Node(element)
        else:
            cursor = self.head
            while cursor.next:
                cursor = cursor.next
            cursor.next = Node(element)

    def __str__(self):
        if self.head is None:
            return "LinkedList[]"
        _nodes = []
        cursor = self.head
        while cursor:
            _nodes.append(str(cursor))
            cursor = cursor.next
        return f"LinkedList[length = {len(self)}, [{'; '.join(_nodes)}]]"

    def pop(self):
        if not self.head:
            raise IndexError("LinkedList is empty!")
            # should be:
            # raise IndexError("pop from empty LinkedList")
        cursor = self.head
        if not cursor.next:
            self.head = None
        else:
            while cursor.next.next:
                cursor = cursor.next
            cursor.next = None

    def change_on_start(self, n, new_data):
        if n > len(self) or n <= 0:
            raise KeyError("Element doesn't exist!")
            # should be:
            # raise IndexError("LinkedList assignment index out of range")
        cursor = self.head
        for _ in range(n - 1):
            cursor = cursor.next
        cursor.change_data(new_data)

    def clear(self):
        self.head = None
