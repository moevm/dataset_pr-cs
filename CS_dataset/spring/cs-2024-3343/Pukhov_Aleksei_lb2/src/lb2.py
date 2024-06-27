class Node:
    def __init__(self, data, next=None):
        self.__data = data
        self.next = None

    def get_data(self):
        return self.__data
        
    def change_data(self, new_data):
        self.__data = new_data

    def __str__(self):
        return f"data: {self.__data}, next: {self.next.get_data() if self.next else None}"


class LinkedList:
    def __init__(self, head = None):
        self.head = head
        self.length = 0 if head is None else 1

    def __len__(self):
        return self.length

    def append(self, element):
        new_node = Node(element)
        if self.head is None:
            self.head = new_node
        else:
            tmp = self.head
            while tmp.next:
                tmp = tmp.next
            tmp.next = new_node
        self.length += 1

            
    def __str__(self):
        if self.length == 0:
            return "LinkedList[]"
        else:
            nodes = []
            current = self.head
            while current:
                nodes.append(str(current))
                current = current.next
            return f"LinkedList[length = {self.length}, [{'; '.join(nodes)}]]"

    def pop(self):
        if self.length == 0:
            raise IndexError("LinkedList is empty!")
        tmp = self.head
        if tmp.next is None:
            self.head = None
        else:
            while tmp.next.next:
                tmp = tmp.next
            tmp.next = None
        self.length -= 1


    def change_on_end(self, n, new_data):
        tmp = self.head
        if self.length < n or n <= 0:
            raise KeyError("Element doesn't exist!")
        for i in range(self.length - n):
            tmp = tmp.next
        tmp.change_data(new_data)

    def clear(self):
        self.head = None
        self.length = 0