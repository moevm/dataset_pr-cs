class Node:
    def __init__(self, data, next=None):
        self.data = data
        self.next = next

    def get_data(self):
        return self.data

    def change_data(self, new_data):
        self.data = new_data

    def __str__(self):
        next_data = self.next.data if self.next is not None else None
        return f"data: {self.data}, next: {next_data}"


class LinkedList:
    def __init__(self, head=None):
        self.head = None
        self.length = 0

        if head is not None:
            self.append(head)

    def __len__(self):
        return self.length

    def append(self, element):
        new_element = Node(element)

        if self.length == 0:
            self.head = new_element
            self.length += 1
            return

        tmp_node = self.head
        while tmp_node.next is not None:
            tmp_node = tmp_node.next

        tmp_node.next = new_element
        self.length += 1


    def __str__(self):
        if self.length == 0:
            return "LinkedList[]"

        result = "LinkedList["
        result += f"length = {self.length}, ["
        tmp_node = self.head
        while tmp_node.next is not None:
            result += f"data: {tmp_node.data}, next: {tmp_node.next.data}; "
            tmp_node = tmp_node.next

        result += f"data: {tmp_node.data}, next: None]]"
        return result

    def pop(self):
        if self.length == 0:
            raise IndexError("LinkedList is empty!")
        if self.length == 1:
            self.clear()
            return

        tmp_node = self.head
        while tmp_node.next.next is not None:
            tmp_node = tmp_node.next

        tmp_node.next = None
        self.length -= 1

    def change_on_end(self, n, new_data):
        if self.length < n or n <= 0:
            raise KeyError("Element doesn't exist!")

        count = 0
        tmp_node = self.head
        while count != self.length-n:
            tmp_node = tmp_node.next
            count += 1

        tmp_node.data = new_data

    def clear(self):
        self.head = None
        self.length = 0