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
            return f"data: {self.get_data()}, next: None"
        else:
            return f"data: {self.get_data()}, next: {self.next.get_data()}"

class LinkedList:
    def __init__(self, head = None):
        if head is None:
            self.head = None
        else:
            self.head = [head]    
        self.length = 0

    def __len__(self):
        return self.length

    def append(self, element):
        last_element = Node(element)
        if self.head is None:
            self.head = last_element
        else:
            current_node = self.head
            while current_node.next:
                current_node = current_node.next
            current_node.next = last_element
        self.length += 1
            
    def __str__(self):
        if self.head is None:
            return f"LinkedList[]"
        else:
            current_node = self.head
            output = ''
            while current_node.next:
                output += f"data: {current_node.get_data()}, next: {current_node.next.get_data()}; "
                current_node = current_node.next
            output += f"data: {current_node.get_data()}, next: {current_node.next}"
            return f"LinkedList[length = {self.length}, [{output}]]"

    def pop(self):
        current_node = self.head
        if current_node is None:
            raise IndexError("LinkedList is empty!")
        elif self.length == 1:
                self.head = None
                self.length = 0
        elif self.length >= 2:
                while current_node.next.next:
                    current_node =current_node.next
                current_node.next = None
                self.length -= 1

    def change_on_start(self, n, new_data):
        if any([self.length < n, self.head is None, n <= 0]):
            raise KeyError("Element doesn't exist!")
        else:
            current_node = self.head
            if n == 1:
                current_node.change_data(new_data)
            for _ in range(n - 1):
                current_node = current_node.next
            current_node = current_node.change_data(new_data)

    def clear(self):
        current_node = self.head
        while self.length > 0:
            temp_node = self.head.next
            self.head = None
            self.head = temp_node
            self.length -= 1
