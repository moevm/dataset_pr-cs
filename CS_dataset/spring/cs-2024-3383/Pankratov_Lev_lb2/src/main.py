class Node:
    def __init__(self, data, next_node=None):
        self.__data = data
        self.next = next_node

    def get_data(self):
        return self.__data

    def change_data(self, new_data):
        self.__data = new_data

    def __str__(self):
        next_data = self.next.get_data() if self.next else None
        return f"data: {self.__data}, next: {next_data}"


class LinkedList:
    def __init__(self, head=None):
        if head is None:
            self.head = None
        else:
            self.head = Node(head)

    def append(self, element):
        if self.head is None:
            self.head = Node(element)
        else:
            current = self.head
            while current.next:
                current = current.next
            current.next = Node(element)

    def __len__(self):
        count = 0
        current = self.head
        while current:
            count += 1
            current = current.next
        return count

    def __str__(self):
        if self.head is None:
            return "LinkedList[]"
        else:
            current = self.head
            result = f"LinkedList[length = {len(self)}, ["
            while current:
                result += f"data: {current.get_data()}, next: {current.next.get_data() if current.next else None}; "
                current = current.next
            result = result[:-2]
            result += "]]"
            return result

    def pop(self):
        if self.head is None:
            raise IndexError("LinkedList is empty!")
        elif self.head.next is None:
            data = self.head.get_data()
            self.head = None
            return data
        else:
            current = self.head
            while current.next.next:
                current = current.next
            data = current.next.get_data()
            current.next = None
            return data

    def change_on_end(self, n, new_data):
        if n > len(self) or n <= 0:
            raise KeyError("Element doesn't exist!")
        current = self.head
        for i in range(len(self) - n):
            current = current.next
        current.change_data(new_data)

    def clear(self):
        self.head = None
