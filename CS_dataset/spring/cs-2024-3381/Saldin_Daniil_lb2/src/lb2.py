class Node:
    def __init__(self, data, next=None):
        self.__data = data
        self.next = next

    def get_data(self):
        return self.__data

    def __str__(self):
        if (self.next != None):
            return "data: " + str(self.__data) + ", next: " + str(self.next.__data)
        return "data: " + str(self.__data) + ", next: None"
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
        node = Node(element)
        temp = self.head
        if temp == None:
            self.head = node
        else:
            while temp.next:
                temp = temp.next
            temp.next = node
        self.length += 1
    def __str__(self):
        if (self.length == 0):
            return "LinkedList[]"
        else:
            string =  "LinkedList[length = " + str(self.length) + ", ["
            tmp = self.head
            while (tmp != None):
                string += tmp.__str__() + '; '
                tmp = tmp.next
            string = string[:-2] + ']]'
        return string

    def pop(self):
        if (self.length == 0):
            raise IndexError("LinkedList is empty!")
        elif (self.length == 1):
            self.head = None
            self.length = 0
        else:
            temp = self.head
            while temp.next.next:
                temp = temp.next
            temp.next = None
            self.length -= 1

    def delete_on_end(self, n):
        if (self.length < n or n < 1):
            raise KeyError("Element doesn't exist!")
        shifts = self.length - n - 1
        if (shifts == -1):
            self.head = self.head.next
            self.length -= 1
        elif(shifts == 0):
            self.head.next = self.head.next.next
            self.length -= 1
        else:
            tmp = self.head
            for i in range(shifts):
                tmp = tmp.next
            tmp.next = tmp.next.next
            self.length -= 1
        

    def clear(self):
        prev = self.head
        tmp = prev.next
        while (tmp != None):
            prev.next = None
            prev = tmp
            tmp = tmp.next
        self.length = 0