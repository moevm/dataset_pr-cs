class Node:
    def __init__(self, data, next=None):
        self.data = data
        self.next = next

    def get_data(self):
        return self.data

    def __str__(self):
        return f"data: {self.data}, next: {None if self.next is None else self.next.get_data()}"


class LinkedList:
    def __init__(self, head=None):
        self.__head__ = head
        self.__length = 0
        if head is not None:
            self.__length = 1

    def __len__(self):
        return self.__length

    def append(self, element):
        new_element = Node(element)
        if self.__head__ is None:
            self.__head__ = new_element
            self.__length += 1
            return
        current_element = self.__head__
        while current_element.next is not None:
            current_element = current_element.next
        current_element.next = new_element
        self.__length += 1
        return

    def __str__(self):
        list = []
        curr = self.__head__
        if self.__length == 0:
            return "LinkedList[]"
        list.append(f"data: {curr.get_data()}, next: {None if curr.next is None else curr.next.get_data()}")
        while curr.next is not None:
            curr = curr.next
            list.append(f" data: {curr.get_data()}, next: {None if curr.next is None else curr.next.get_data()}")
        return f"LinkedList[length = {self.__length}, [{';'.join(list)}]]"

    def pop(self):
        if self.__head__ is None:
            raise IndexError("LinkedList is empty!")
        if self.__length == 1:
            self.__head__ = None
            self.__length -= 1
            return
        current_element = self.__head__
        previous_element = current_element
        while current_element.next is not None:
            previous_element = current_element
            current_element = current_element.next
        previous_element.next = None
        self.__length -= 1
        return

    def delete_on_start(self, n):
        if n > self.__length or n <= 0:
            raise KeyError("Element doesn't exist!")
        if n == 1 and self.__length >= 2:
            self.__head__ = self.__head__.next
            self.__length -= 1
            return
        elif n==1 and self.__length == 1:
            self.__head__ = None
            return 
        index = 1
        current_element = self.__head__
        previous_element = current_element
        while current_element.next is not None and index != n:
            previous_element = current_element
            current_element = current_element.next
            index += 1
        previous_element.next = current_element.next
        self.__length -= 1

    def clear(self):
        self.__head__ = None
        self.__length = 0

