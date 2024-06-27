class Node:
    def __init__(self, data, next=None):
        self.__data = data
        self.next = next

    def get_data(self):
        return self.__data

    def __str__(self):
        next_data = self.next if self.next is None else self.next.get_data()
        return f"data: {self.get_data()}, next: {next_data}"


class LinkedList:
    def __init__(self, head=None):
        self.head = head if head is None else Node(head)
        self.length = self.__len__()

    def __len__(self):
        count = 0
        temp = self.head
        while temp is not None:
            count += 1
            temp = temp.next
        return count

    def append(self, element):
        if  self.head is None:
            self.head = Node(element)
        else:
            temp = self.head
            while temp.next is not None:
                temp = temp.next
            temp.next = Node(element)
        self.length += 1

    def __str__(self):
        str_len = "" if len(self) == 0 else f"length = {len(self)}"
        temp = self.head
        list_str_array = []
        while temp is not None:
            list_str_array.append(str(temp))
            temp = temp.next
        if len(list_str_array) != 0:
            body = f", [{'; '.join(list_str_array)}]"
        else:
            body = ""
        return f"LinkedList[{str_len}{body}]"

    def pop(self):
        if self.length == 0:
            raise IndexError("LinkedList is empty!")
        if self.length == 1:
            self.head = self.head.next
        else:
            temp = self.head
            while temp.next.next is not None:
                temp = temp.next
            temp.next = None
        self.length-=1


    def delete_on_end(self, n):
        if n > self.length or n<1:
            raise KeyError("Element doesn't exist!")
        if n == self.length:
            self.head = self.head.next
            return

        count = 0
        temp = self.head
        while count != self.length - n - 1:
            temp = temp.next
            count+=1
        temp.next = temp.next.next
        self.length -= 1

    def clear(self):
        self.head = None
        self.length = 0