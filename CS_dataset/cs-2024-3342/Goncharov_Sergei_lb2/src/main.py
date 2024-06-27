class Node:
    def __init__(self, data, next_node=None):
        self._data = data
        self.next = next_node

    def get_data(self):
        return self._data

    def change_data(self, new_data):
        self._data = new_data

    def __str__(self):
        if self.next is None:
            return f"data: {self._data}, next: None"
        else:
            return f"data: {self._data}, next: {self.next.get_data()}"

class LinkedList:
    def __init__(self, head=None):
        if head is None:        # Если переменная head равна None, создаем пустой список
            self.head = None
            self.length = 0
        else:
            self.head = head    # Если head не равен None, создаем список из 1 элемента
            self.length = 1

    def __len__(self):
        return self.length

    def append(self, element):
        if self.head is None:
            self.head = Node(element)
            self.length += 1
            return None

        current_element = self.head
        while current_element.next is not None:
            current_element = current_element.next

        current_element.next = Node(element)
        self.length += 1

    def __str__(self):
        if self.length == 0:
            return "LinkedList[]"
        
        current_element = self.head
        elements_array = [str(current_element)]

        while (current_element.next != None):
            current_element = current_element.next
            elements_array += [str(current_element)]

        elements_array = "[" + '; '.join(elements_array) + "]"
        return f"LinkedList[length = {len(self)}, {elements_array}]"

    def pop(self):
        if self.length == 0:
            raise IndexError("LinkedList is empty!")
        if self.length == 1:
            self.head = None
            self.length = 0
            return None

        current_element = self.head
        while current_element.next.next is not None:
            current_element = current_element.next
        current_element.next = None
        self.length -= 1

    def change_on_start(self, n, new_data):
        if self.length < n or n <= 0:
            raise KeyError("Element doesn't exist!")
        current_element = self.head
        for i in range(n-1):
            current_element = current_element.next
        current_element.change_data(new_data)

    def clear(self):
        self.head = None
        self.length = 0
