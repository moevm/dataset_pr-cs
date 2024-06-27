class Node:
    def __init__(self, data, next=None):
        self.__data = data
        self.next = next

    def get_data(self):
        return self.__data

    def __str__(self):
        return f"data: {self.__data}, next: {self.next.__data if self.next else None}"


class LinkedList:
    def __init__(self, head: Node = None):
        self.head = head
        if head is not None:
            self.length = 1
        else:
            self.length = 0

    def __len__(self):
        return self.length

    def append(self, element):
        self.length += 1
        current_node = self.head
        if current_node is None:
            self.head = Node(element)
            return
        while current_node.next:
            current_node = current_node.next
        current_node.next = Node(element)

    def __str__(self):
        if self.length == 0: return "LinkedList[]"
        current_node = self.head
        node_to_str_list = []
        while current_node:
            node_to_str_list.append(current_node.__str__())
            current_node = current_node.next
        linkedlist_elements = "; ".join(node_to_str_list)
        return f"LinkedList[length = {self.length}, [{linkedlist_elements}]]"

    def pop(self):
        if self.length == 0: raise IndexError("LinkedList is empty!")
        current_node = self.head
        if self.length == 1:
            self.head = None
        else:
            while current_node.next.next:
                current_node = current_node.next
            current_node.next = None
        self.length -= 1

    def delete_on_start(self, n):
        if self.length < n or n <= 0: raise KeyError("Element doesn't exist!")
        current_node = self.head
        count = 1
        if n == 1:
            self.head = current_node.next
        else:
            while count + 1 != n:
                count += 1
                current_node = current_node.next
            current_node.next = current_node.next.next
        self.length -= 1

    def clear(self):
        while self.head:
            self.pop()
