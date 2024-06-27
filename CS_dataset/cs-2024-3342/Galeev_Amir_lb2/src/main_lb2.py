class Node:
    def __init__(self, data, next=None):
        self.data = data
        self.next = next

    def get_data(self):
        return self.data

    def change_data(self, new_data):
        self.data = new_data

    def __str__(self):
        next_data = self.next.data if self.next else None
        return f"data: {self.data}, next: {next_data}"


class LinkedList:
    def __init__(self, head=None):
        self.head = head
        self.length = 0 if head is None else 1

    def __len__(self):
        return self.length

    def append(self, element):
        new_node = Node(element)
        if not self.head:
            self.head = new_node
        else:
            current_node = self.head
            while current_node.next:
                current_node = current_node.next
            current_node.next = new_node
        self.length += 1

    def __str__(self):
        if not self.head:
            return "LinkedList[]"
        else:
            result = "LinkedList[length = " + str(self.length) + ", ["
            current_node = self.head
            while current_node:
                result += str(current_node) + "; "
                current_node = current_node.next
            result = result.rstrip("; ") + "]]"
            return result

    def pop(self):
        if not self.head:
            raise IndexError("LinkedList is empty!")
        elif not self.head.next:
            self.head = None
        else:
            previous_node = None
            current_node = self.head
            while current_node.next:
                previous_node = current_node
                current_node = current_node.next
            previous_node.next = None
        self.length -= 1

    def clear(self):
        self.head = None
        self.length = 0

    def change_on_end(self, n: int, new_data) -> None:
        if len(self) < n or n < 1:
            raise KeyError("Element doesn't exist!")
        n = len(self) - n
        if not n:
            self.head.data = new_data
            return
        _node = self.head
        for _ in range(n):
            _node = _node.next
        _node.data = new_data