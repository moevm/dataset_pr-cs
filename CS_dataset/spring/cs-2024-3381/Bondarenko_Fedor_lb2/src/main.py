class Node:
    def __init__(self, __data, next=None):
        self.__data = __data
        self.next = next

    def get_data(self):
        return self.__data

    def change_data(self, new_data):
        self.__data = new_data
        return self.__data

    def __str__(self):
        if self.next != None: nextData = self.next.__data
        else: nextData = None
        return f"data: {self.__data}, next: {nextData}"

class LinkedList:
    def __init__(self, head=None):
        self.head = head
        if (head == None):
            self.length = 0
        else:
            self.length = 1

    def __len__(self):
        return self.length

    def append(self, element):
        self.length += 1
        node = Node(element)
        if (self.length == 1):
            self.head = node
        else:
            temp = self.head
            while (temp.next):
                temp = temp.next
            temp.next = node

    def __str__(self):
        if (self.length == 0):
            return "LinkedList[]"
        else:
            headData = self.head.get_data()
            if self.head.next != None: nextHeadData = self.head.next.get_data()
            else: nextHeadData = None
            stringToReturn = f"LinkedList[length = {self.length}, [data: {headData}, next: {nextHeadData}"
            temp = self.head.next
            while (temp):
                data = temp.get_data()
                if temp.next != None: nextData = temp.next.get_data()
                else: nextData = None
                stringToReturn += f"; data: {data}, next: {nextData}"
                temp = temp.next
            stringToReturn += ']]'
            return stringToReturn

    def pop(self):
        if self.length == 0:
            raise IndexError("LinkedList is empty!")
        elif self.length == 1:
            self.head = None
            self.length = 0
        else:
            temp = self.head
            while (temp.next.next):
                temp = temp.next
            temp.next = None
            self.length -= 1

    def clear(self):
        self.head.next = None
        self.head = None
        self.length = 0

    def change_on_start(self, n, new_data):
        if n > self.length or n <= 0:
            raise KeyError("Element doesn't exist!")
        else:
            temp = self.head
            for i in range(n-1):
                temp = temp.next
            temp.change_data(new_data)
