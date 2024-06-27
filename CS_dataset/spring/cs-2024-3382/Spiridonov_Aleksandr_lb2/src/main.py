class Node:
    def __init__(self, data, next=None):
        self.data = data
        self.next = next

    def get_data(self):
        return self.data

    def change_data(self, new_data):
        self.data = new_data

    def __str__(self):
        if self.next == None:
            return f"data: {self.data}, next: None"
        else:
            return f"data: {self.data}, next: {self.next.data}"


class LinkedList:
    def __init__(self, head=None):
        self.head = head
        self.length = len(self)

    def __len__(self):
        count = 0
        elem = self.head

        while elem is not None:
            count += 1
            elem = elem.next

        return count

    def append(self, element):
        end_elem = Node(element)
        elem = self.head

        if len(self) == 0:
            self.head = end_elem
        else:
            while elem.next is not None:
                elem = elem.next
            elem.next = end_elem

    def __str__(self):
        if len(self) == 0:
            return "LinkedList[]"

        else:
            return_str = f"LinkedList[length = " + str(len(self)) + ", ["

            elem = self.head
            while elem.next is not None:
                return_str += str(elem)
                return_str += '; '
                elem = elem.next

            return_str += str(elem)

            return return_str + "]]"

    def pop(self):
        if self.head is None:
            raise IndexError("LinkedList is empty!")
        elif len(self) == 1:
            self.head = None

        else:
            elem = self.head
            while elem.next.next is not None:
                elem = elem.next

            elem.next = None

    def change_on_start(self, n, new_data):
        if n > len(self) or n <= 0:
            raise KeyError(f"Element doesn't exist!")

        elem = self.head
        for i in range(n - 1):
            elem = elem.next
        elem.change_data(new_data)

    def clear(self):
        self.head = None
