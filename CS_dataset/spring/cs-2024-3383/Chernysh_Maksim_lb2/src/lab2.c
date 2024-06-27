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
        if head == None:
            self.head = head
            self.__length = 0
        else:
            self.head = head
            self.__length = 1

    def __len__(self):
        return self.__length

    def append(self, element):
        self.__length += 1
        elem = Node(element, None)
        if self.head != None:
            tmp = self.head
            while tmp.next != None:
                tmp = tmp.next
            tmp.next = elem
        else:
            self.head = elem

    def __str__(self):
        if self.head != None:
            tmp = self.head
            elems = f'{tmp}'
            while tmp.next != None:
                tmp = tmp.next
                elems += "; " + tmp.__str__()
            res = f'LinkedList[length = {self.__length}, [{elems}]]'
        else:
            res = f'LinkedList[]'
        return res

    def pop(self):
        if self.head == None:
            raise IndexError("LinkedList is empty!")
        else:
            tmp1 = self.head
            tmp2 = tmp1.next
            while tmp2 != None and tmp2.next != None and tmp2:
                tmp1 = tmp2
                tmp2 = tmp2.next
            if tmp1 == self.head and self.__length == 1:
                self.head = None
            else:
                tmp1.next = None
            self.__length -= 1

    def change_on_start(self, n, new_data):
        if self.__length < n or n<=0:
            raise KeyError("Element doesn't exist!")
        else:
            tmp = self.head
            for i in range(n-1):
                tmp = tmp.next
            tmp.change_data(new_data)

    def clear(self):
        self.head = None
        self.__length = 0
