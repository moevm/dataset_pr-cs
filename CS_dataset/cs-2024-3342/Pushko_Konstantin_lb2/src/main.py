class Node:
    def __init__(self, data, next=None):
        self.__data = data
        self.next = next

    def get_data(self):
        return self.__data

    def change_data(self, new_data):
        self.__data = new_data

    def __str__(self):
        if (self.next is None):
            return f'data: {self.__data}, next: None'
        return f'data: {self.__data}, next: {self.next.get_data()}'

class LinkedList:
    def __init__(self, head=None):
        if head is None:
            self.head = None
            self.length = 0
        else:
            self.head = head
            self.length = 1


    def __len__(self):
        return self.length

    def append(self, element):

        if self.head is None:
            self.head = Node(element)
            self.length = 1
            return

        temp = self.head
        while temp.next is not None:
            temp = temp.next
        temp.next = Node(element)
        self.length +=1

    def __str__(self):
        if (self.length == 0):
            return 'LinkedList[]'
        message = 'LinkedList[length = ' + str(self.length) + ', ['
        temp = self.head
        while temp.next is not None:
            message += str(temp) + '; '
            temp = temp.next
        message += str(temp)
        message += ']]'
        return message

    def pop(self):
        if self.length == 0:
            raise IndexError("LinkedList is empty!")
        if self.length == 1:
            self.head = None
            self.length = 0
            return
        temp = self.head
        while temp.next.next is not None:
            temp = temp.next
        temp.next = None
        self.length -=1

    def change_on_start(self, n, new_data):
        if self.length < n or n <=0:
            raise KeyError("Element doesn't exist!")
        temp = self.head
        for i in range(n-1):
            temp = temp.next
        temp.change_data(new_data)


    def clear(self):
        self.head = None
        self.length = 0



