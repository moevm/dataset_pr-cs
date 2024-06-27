class Node:
    def __init__(self, data, next=None):
        self.__data = data
        self.next = next

    def get_data(self):
        return self.__data

    def change_data(self, new_data):
        self.__data = new_data

    def __str__(self):
        return "data: " + str(self.get_data()) + ", next: " + str(self.next.get_data() if self.next != None else None)


class LinkedList:
    def __init__(self, head=None):
        self.head = head
        self.length = 1 if head != None else 0

    def __len__(self):
        return self.length

    def append(self, element):
        elem = Node(element)
        if (self.length > 0):
            curr = self.head
            while (curr.next != None):
                curr = curr.next
            curr.next = elem
        else:
            self.head = elem
        self.length += 1

    def __str__(self):
        if (self.length == 0):
            return "LinkedList[]"
        else:
            curr = self.head
            result = "LinkedList[length = " + str(self.length) + ", ["
            while (curr != None):
                result += str(curr) + "; "
                curr = curr.next
            result = result[:-2]
            result += "]]"
            return result

    def pop(self):
        if (self.length == 0) :
            raise IndexError("LinkedList is empty!")
        elif (self.length == 1):
            self.head = None
            self.length = 0
        else:
            curr = self.head
            while (curr.next.next != None):
                curr = curr.next
            curr.next = None
            self.length -= 1

    def change_on_start(self, n, new_data):
        if (self.length < n or n < 1):
            raise KeyError("Element doesn't exist!")
        else:
            curr = self.head
            for i in range(n-1):
                curr = curr.next
            curr.change_data(new_data)

    def clear(self):
        self.head = None
        self.length = 0
