class Node:
    def __init__(self, data, next=None):
        self.__data = data
        self.next = next

    def get_data(self):
        return self.__data

    def change_data(self, new_data):
        self.__data = new_data

    def __str__(self):
        if self.next is None:
            next_data = "None"
        else:
            next_data = str(self.next.get_data())
        return f"data: {self.__data}, next: {next_data}"


class LinkedList:
    def __init__(self, head=None):
        if head is None:
            self.length = 0
        else:
            self.length = 1
        self.head = head

    def __len__(self):
        return self.length

    def append(self, element):
        new_node = Node(element)
        if self.head is None:
            self.head = new_node
        else:
            current_node = self.head
            while current_node.next is not None:
                current_node = current_node.next
            current_node.next = new_node
        self.length += 1

    def __str__(self):
        if self.head is None:
            return 'LinkedList[]'
        else:
            result = f"LinkedList[length = {self.length}, ["
            current_node = self.head
            while current_node is not None:
                result += str(current_node)
                if current_node.next is not None:
                    result += '; '
                current_node = current_node.next
            result += ']]'
            return result

    def pop(self):
        if self.length == 0:
            raise IndexError("LinkedList is empty!")
        elif self.length == 1:
            self.head = None
            self.length = 0
        else:
            current_node = self.head
            while current_node.next.next is not None:
                current_node = current_node.next
            current_node.next = None
            self.length -= 1

    def change_on_end(self, n, new_data):
        if self.length < n or n < 1:
            raise KeyError("Element doesn't exist!")
        current_node = self.head
        n = self.length - n
        while n > 0:
            current_node = current_node.next
            n -= 1
        current_node.change_data(new_data)

    def clear(self):
        self.head = None
        self.length = 0