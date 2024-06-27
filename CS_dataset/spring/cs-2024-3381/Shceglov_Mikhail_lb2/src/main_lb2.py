class Node:
    def __init__(self, data, next = None):
        self.__data = data
        self.next = next

    def get_data(self):
        return self.__data
        
    def change_data(self, new_data):
        self.__data = new_data

    def __str__(self):
        if self.next is None:
            return f"data: {self.__data}, next: None"
        else:
            return f"data: {self.__data}, next: {self.next.get_data()}"


class LinkedList:
    def __init__(self, head = None):
        self.head = head
        self.length = 0
        if head is not None:
            self.length = 1

    def __len__(self):
        return self.length

    def append(self, element):
        new_node = Node(element)
        if self.head is None:
            self.head = new_node
        else:
            current = self.head
            while current.next is not None:
                current = current.next
            current.next = new_node
        self.length += 1

            
    def __str__(self):
        if self.head is None:
            return "LinkedList[]"
        else:
            result = "LinkedList[length = " + str(self.length) + ", ["
            current = self.head
            while current is not None:
                result += str(current) + "; "
                current = current.next
            return result.rstrip("; ") + "]]"

    def pop(self):
        if self.head is None:
            raise IndexError("LinkedList is empty!")
        elif self.head.next is None:
            self.head = None
        else:
            current = self.head
            while current.next.next is not None:
                current = current.next
            current.next = None
        self.length -= 1

    def change_on_start(self, n, new_data):
        if n > self.length or n <= 0:
            raise KeyError("Element doesn't exist!")
        k = 1
        current = self.head
        while (current):
            if (k == n):
                current.change_data(new_data)
                break
            k += 1
            current = current.next

    def clear(self):
        self.head = None
        self.length = 0