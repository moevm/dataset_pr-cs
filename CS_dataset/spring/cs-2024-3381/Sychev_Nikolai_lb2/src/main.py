class Node:
    def __init__(self, data, next=None):
        self.__data = data
        self.next = next

    def get_data(self):
        return self.__data

    def change_data(self, new_data):
        self.__data = new_data

    def __str__(self):
        return f"data: {self.__data}, next: {self.next.__data if self.next != None else None}"


class LinkedList:
    def __init__(self, head = None):
        if head is None:
            self.head = None
            self.__length = 0
        else:
            self.head = Node(head)
            self.__length = 1

    def __len__(self):
        return self.__length

    def append(self, element):
        if self.head == None:
            self.head = Node(element)
        else:
            current = self.head
            while current.next is not None:
                current = current.next
            current.next = Node(element)
        self.__length += 1


    def __str__(self):
        if self.__length == 0:
            return "LinkedList[]"
        else:
            current = self.head
            result = f"LinkedList[length = {self.__length}, [{current}"
            while current.next is not None:
                current = current.next
                result += f"; {current}"
            return result + "]]"

    def pop(self):
        if self.head == None:
            raise IndexError("LinkedList is empty!")
        elif self.__length == 1:
            self.head = None
            self.__length = 0
        else:
            current = self.head
            while current.next.next is not None:
                current = current.next
            current.next = None
            self.__length -= 1  

    def change_on_end(self, n, new_data):
        if n <= 0 or self.__length < n:
            raise KeyError("Element doesn't exist!")
        else:
            current = self.head
            count = 0
            while count < self.__length - n:
                current = current.next
                count += 1
            current.change_data(new_data)

    def clear(self):
        self.head = None
        self.__length = 0