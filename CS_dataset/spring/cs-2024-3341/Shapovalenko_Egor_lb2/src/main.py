class Node:
    def __init__(self, data, next = None):
        self.data = data
        self.next = next

    def get_data(self):
        return self.data

    def change_data(self, new_data):
        self.data = new_data

    def __str__(self):
        return f"data: {self.data}, next: {None if self.next == None else self.next.data}"


class LinkedList:
    def __init__(self, head = None):
        self.head = head
        self.length = 0 if head == None else 1

    def __len__(self):
        return self.length

    def append(self, element):
        new_node = Node(element)

        if self.length == 0:
            self.head = new_node
        else:
            tmp = self.head
            while tmp.next != None:
                tmp = tmp.next
            tmp.next = new_node

        self.length += 1

    def __str__(self):
        if self.length == 0:
            return "LinkedList[]"
        else:
            result = f"LinkedList[length = {self.length}, ["

            tmp = self.head
            while tmp != None:
                result += str(tmp)
                if tmp.next != None:
                    result += "; "
                tmp = tmp.next

            result += "]]"
            return result

    def pop(self):
        if self.length == 0:
            raise IndexError("LinkedList is empty!")
        elif self.length == 1:
            head = None
            self.length = 0
        else:
            tmp = self.head
            while tmp.next.next != None:
                tmp = tmp.next
            tmp.next = None

            self.length -= 1

    def change_on_end(self, n, new_data):
        if self.length < n or n < 1:
            raise KeyError("Element doesn't exist!")
        else:
            n = self.length - n

            tmp = self.head
            while n > 0:
                tmp = tmp.next
                n -= 1
            tmp.change_data(new_data)

    def clear(self):
        self.head = None
        self.length = 0