class Node:
    def __init__(self, data, next=None):
        self.__data = data
        self.next = next

    def get_data(self):
        return self.__data

    def change_data(self, new_data):
        self.__data = new_data

    def __str__(self):
        if self.next is not None:
            return f"data: {self.__data}, next: {self.next.__data}"
        else:
            return f"data: {self.__data}, next: {self.next}"

class LinkedList:
    def __init__(self, head=None):
        self.length = 0
        self.head = head
        if head != None:
            self.length = 1

    def __len__(self):
        return self.length

    def append(self, element):
        new_node = Node(element)
        if self.head != None:
            current = self.head
            while (current.next != None):
                current = current.next
            current.next = new_node
            self.length += 1
        else:
            self.head = new_node
            self.length += 1

    def __str__(self):
        if self.length == 0:
            return "LinkedList[]"
        else:
            node_list = ""
            current = self.head
            while current.next != None:
                node_list += f"{str(current)}; "
                current = current.next
            node_list += f"{str(current)}"
            return f"LinkedList[length = {self.length}, [{node_list}]]"

    def pop(self):
        if self.length >= 1:
            current = self.head
            previous = None
            while current.next != None:
                previous = current
                current = current.next
            if previous == None:
                self.head = None
                self.length -= 1
            else:
                previous.next = None
                self.length -= 1
        else:
            raise IndexError("LinkedList is empty!")


    def change_on_start(self, n, new_data):
        if (self.length < n) or (n <= 0):
            raise KeyError("Element doesn't exist!")
        else:
            current_index = 1
            current = self.head
            while (current_index != n):
                current = current.next
                current_index += 1
            current.change_data(new_data)


    def clear(self):
        self.head = None
        self.length = 0
