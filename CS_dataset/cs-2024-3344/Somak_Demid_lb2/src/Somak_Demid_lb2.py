class Node:
    def __init__(self, data, next=None):
        self.__data = data
        self.next = next

    def get_data(self):
        return self.__data

    def __str__(self):
        if self.next:
            return (f'data: {self.__data}, next: {self.next.__data}')
        return (f'data: {self.__data}, next: None')


class LinkedList:
    def __init__(self, head=None):
        self.head = head
        self.length = 0
        while head:
            head = head.next
            self.length += 1

    def __len__(self):
        return self.length

    def append(self, element):
        if self.head != None:
            temp = self.head
            while temp.next:
                temp = temp.next
            temp.next = Node(element)
        else:
            self.head = Node(element)
        self.length +=1

    def __str__(self):
        if self.head != None:
            inf = f'LinkedList[length = {self.length}, ['
            temp = self.head
            while temp:
                inf += str(temp) + '; '
                temp = temp.next
            inf = inf[:-2] + ']]'
            return inf
        else:
            return 'LinkedList[]'

    def pop(self):
        if self.head is None:
            raise IndexError("LinkedList is empty!")
        elif self.length == 1:
            self.__init__()
        else:
            temp = self.head
            while temp.next.next:
                temp = temp.next
            temp.next = None
            self.length -= 1


    def delete_on_end(self, n):
        if self.length < n or n <= 0:
            raise KeyError("Element doesn't exist!")
        else:
            index = self.length - n
            temp = self.head
            if index == 0:
                self.head = temp.next
            else:
                for i in range(index-1):
                    temp = temp.next
                temp.next = temp.next.next
            self.length -= 1


    def clear(self):
        self.__init__()