class Node:
    def __init__(self, data, next=None):
        self.__data=data
        self.next=next

    def get_data(self):
        return  self.__data

    def __str__(self):
        if self.next is not None:
            return f"data: {self.__data}, next: {self.next.get_data()}"
        else:
            return f"data: {self.__data}, next: None"



class LinkedList:
    def __init__(self, head=None):
        if head is None:
            self.head = None
            self.length = 0
        else:
            self.head = Node(head)
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
            result = "LinkedList[length = {}, [".format(self.length)
            current = self.head
            while current is not None:
                result += "data: {}, next: {}; ".format(current.get_data(), current.next.get_data() if current.next is not None else "None")
                current = current.next
            result = result[:-2]  # Remove the extra "; "
            result += "]]"
            return result

    def pop(self):
        if self.head is None:
            raise IndexError("LinkedList is empty!")
        elif self.head.next is None:
            self.head = None
            self.length = 0
        else:
            current = self.head
            while current.next.next is not None:
                current = current.next
            current.next = None
            self.length -= 1

    def clear(self):
        self.head = None
        self.length = 0

    def delete_on_end(self, n):
        if self.length < n or n <= 0:
            raise KeyError("Element doesn't exist!")
        else:
            index = self.length - n
            tmp = self.head
            if index == 0:
                self.head = tmp.next
            else:
                for i in range(1, index):
                    tmp = tmp.next
                tmp.next = tmp.next.next
            self.length -= 1

