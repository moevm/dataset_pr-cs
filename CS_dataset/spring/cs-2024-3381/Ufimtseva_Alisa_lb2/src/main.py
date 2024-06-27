class Node:
    def __init__(self, data, next = None):
        self.__data = data
        self.next = next

    def get_data(self):
        return self.__data
        
    def change_data(self, new_data):
        self.__data = new_data

    def __str__(self):
        if (self.next is not None):
            return f"data: {self.__data}, next: {self.next.__data}"
        else:
            return f"data: {self.__data}, next: None"
            
class LinkedList:
    def __init__(self, head = None):
        self.head = head
        if head == None:
            self.__length = 0 
        else:
            self.__length = 1

    def __len__(self):
        return self.__length

    def append(self, element):
        self.__length += 1
        new = Node(element)
        if (self.head == None):
            self.head = new
        else:
            tmp = self.head
            while (tmp.next !=None):
                tmp = tmp.next
            tmp.next = new
            
    def __str__(self):
        if self.__length == 0:
            return "LinkedList[]"
        else:
            s = f"LinkedList[length = {self.__length}, ["
            tmp = self.head
            while (tmp != None):
                s += tmp.__str__()
                tmp = tmp.next
                if tmp != None:
                    s += "; "
            s += "]]"
            return s

    def pop(self):
        if (self.__length == 0):
            raise IndexError("LinkedList is empty!")
        elif (self.__length == 1):
            self.__length = 0
            self.head = None
        else:
            tmp = self.head
            while (tmp.next.next != None):
                tmp = tmp.next
            tmp.next = None
            self.__length -= 1

    def change_on_start(self, n, new_data):
        if (n > self.__length or n <= 0):
            raise KeyError("Element doesn't exist!")
        k = 1
        tmp = self.head
        while (k < n):
            tmp = tmp.next
            k+=1
        tmp.change_data(new_data)

    def clear(self):
        self.__length = 0
        self.head = None 