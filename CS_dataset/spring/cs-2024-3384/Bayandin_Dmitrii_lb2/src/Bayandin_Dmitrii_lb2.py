class Node:
    def __init__(self, data, next=None):
        self.__data = data
        self.next = next

    def get_data(self):
        return self.__data

    def change_data(self, new_data):
        self.__data = new_data

    def __str__(self):
        return f"data: {self.__data}, next: {self.next.__data if self.next else None}"


class LinkedList:
    def __init__(self, head=None):
        self.__head__ = head
        self.length = 0 if head is None else 1

    def __len__(self):
        return self.length

    def append(self, element):
        n = Node(element)
        head = self.__head__
        if head is None:
            self.__head__ = n
        else:
            while head.next:
                head = head.next
            head.next = n
        self.length += 1

    def __str__(self):
        if self.length == 0:
            return "LinkedList[]"
        else:
            head = self.__head__
            s = f"LinkedList[length = {self.length}, ["
            while head is not None:
                if head.next is not None:
                    s += head.__str__() + "; "
                else:
                    s += head.__str__()
                head = head.next
            return s+']]'
        
    def pop(self):
        if self.length == 0:
            raise (IndexError('LinkedList is empty!'))
        elif self.length == 1:
            self.__head__ = None
        else:
            head = self.__head__
            while head.next.next is not None:
                head = head.next
            head.next = None
        self.length -= 1

    def change_on_end(self, n, new_data):
        if self.length < n or n <= 0:
            raise(KeyError("Element doesn't exist!"))
        else:
            i = 0
            head = self.__head__
            while i < self.length - n:
                head = head.next
                i += 1
            head.change_data(new_data)

    def clear(self):
        self.__head__ = None
        self.length = 0
