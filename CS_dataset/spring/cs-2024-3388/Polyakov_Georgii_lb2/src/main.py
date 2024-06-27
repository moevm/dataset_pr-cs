class Node:
    def __init__(self, data, next=None):
        self.__data = data
        self.next = next

    def get_data(self):
        return self.__data

    def __str__(self):
        if self.next is not None:
            str_concept = f"data: {self.__data}, next: {self.next.__data}"
        else:
            str_concept = f"data: {self.__data}, next: None"
        return str_concept


class LinkedList:
    def __init__(self, head=None):
        self.head = head
        if head is not None:
            self.length = 1
        else:
            self.length = 0

    def __len__(self):
        return self.length

    def append(self, element):
        new_node = Node(element)
        last_element = self.head
        if last_element == None:
            self.head = new_node
        else:
            while last_element.next is not None:
                last_element = last_element.next
            last_element.next = new_node
        self.length += 1

    def __str__(self):
        if self.length == 0:
            return "LinkedList[]"
        else:
            last_element = self.head
            list_nodes = [str(last_element)]
            while last_element.next is not None:
                last_element = last_element.next
                list_nodes.append(str(last_element))
            return f"LinkedList[length = {self.length}, [{'; '.join(list_nodes)}]]"

    def pop(self):
        if self.length == 0:
            raise IndexError("LinkedList is empty!")
        else:
            self.delete_on_end(1)

    def delete_on_end(self, n):
        if self.length < n or n <= 0:
            raise KeyError("Element doesn't exist!")
        else:
            if n == self.length:
                self.head = self.head.next
            else:
                current_element = self.head
                element_index = 1
                while element_index < self.length - n:
                    current_element = current_element.next
                    element_index += 1
                current_element.next = current_element.next.next
            self.length -= 1

    def clear(self):
        self.head = None
        self.length = 0
