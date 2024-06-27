class Node:

    def __init__(self, data=None, next=None):
        self.__data = data
        self.next = next

    def get_data(self):
        return self.__data
    
    def __str__(self):
        if self.next:
            return f'data: {self.__data}, next: {self.next.get_data()}'
        else:
            return f'data: {self.__data}, next: {self.next}'


class LinkedList:

    def __init__(self, head=None):
        self.head = head
        self.length = len(self)

    def __len__(self):
        count = 0
        current = self.head
        while current:
            count += 1
            current = current.next
        return count

    def append(self, element):
        addition = Node(element)
        if self.head is None:
            self.head = addition
        else:
            current = self.head
            while current.next:
                current = current.next
            current.next = addition

    def __iter__(self):
        current = self.head
        while current:
            yield current
            current = current.next

    def __str__(self):
        if len(self) == 0:
            return "LinkedList[]"
        else:
            nodes_info = []
            current = self.head
            while current:
                nodes_info.append(str(current))
                current = current.next
            nodes_info_str = "; ".join(nodes_info)
            return f'LinkedList[length = {len(self)}, [{nodes_info_str}]]'

    def pop(self):
        if self.head is None:
            raise IndexError("LinkedList is empty!")
        elif self.head.next is None:
            self.head = None
        else:
            current = self.head
            while current.next.next:
                current = current.next
            current.next = None

    def clear(self):
        self.head = None

    def delete_on_end(self, n):
        if n > len(self) or n <= 0:
            raise KeyError("Element doesn't exist!")

        first = self.head
        second = self.head

        for _ in range(n):
            if not first:
                raise KeyError("Element doesn't exist!")
            first = first.next

        if not first:
            self.head = self.head.next
            return self

        while first.next:
            first = first.next
            second = second.next
        second.next = second.next.next
        return self
