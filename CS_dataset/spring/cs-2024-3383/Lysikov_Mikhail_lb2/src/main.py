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
            return f"data: {self.__data}, next: {self.next}"
        return f"data: {self.__data}, next: {self.next.__data}"


class LinkedList:
    def __init__(self, head=None):
        self.head = head
        self.length = 0
        if head is not None:
            self.length = 1

    def __len__(self):
        return self.length

    def append(self, element):
        self.length += 1
        if self.head is None:
            self.head = Node(element)
        else:
            current_node = self.head
            while current_node.next is not None:
                current_node = current_node.next
            current_node.next = Node(element)

    def __str__(self):
        if len(self) == 0:
            return "LinkedList[]"
        else:
            str_linked_list = str(self.head)
            current_node = self.head.next
            while current_node is not None:
                str_linked_list = str_linked_list + "; " + str(current_node)
                current_node = current_node.next
            return f"LinkedList[length = {self.length}, [{str_linked_list}]]"

    def pop(self):
        if self.length == 0:
            raise IndexError("LinkedList is empty!")
        elif self.length == 1:
            self.head = None
        else:
            current_node = self.head
            while current_node.next.next is not None:
                current_node = current_node.next
            current_node.next = None
        self.length -= 1

    def change_on_start(self, n, new_data):
        if n > self.length or n < 1:
            raise KeyError("Element doesn't exist!")
        current_node = self.head
        for i in range(n - 1):
            current_node = current_node.next
        current_node.change_data(new_data)

    def clear(self):
        self.length = 0
        self.head = None