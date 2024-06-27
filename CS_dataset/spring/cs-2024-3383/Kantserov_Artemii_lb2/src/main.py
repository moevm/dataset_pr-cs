class Node:
    def __init__(self, data, next=None):
        self.__data = data
        self.next = next

    def get_data(self):
        return self.__data

    def __str__(self):
        return f"data: {self.__data}, next: {self.next.get_data() if self.next else None}"


class LinkedList:
    def __init__(self, head=None):
        self.head = head
        self.length = 0 if head is None else 1

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
            result = result[:-2] + "]]"
            return result

    def pop(self):
        if self.head is None:
            raise IndexError("LinkedList is empty!")
        else:
            if self.length == 1:
                self.head = None
                self.length = 0
            else:
                current = self.head
                while current.next.next is not None:
                    current = current.next
                self.length -= 1
                if current.next is not None:
                    current.next = None
                else:
                    self.head = None

    def clear(self):
        self.head = None
        self.length = 0

    def delete_on_end(self, n):
        if self.length < n or n < 1:
            raise KeyError("Element doesn't exist!")
        else:
            if n == self.length:
                self.head = self.head.next
                self.length -= 1
            else:
                current = self.head
                for _ in range(self.length - n - 1):
                    current = current.next
                current.next = current.next.next
                self.length -= 1