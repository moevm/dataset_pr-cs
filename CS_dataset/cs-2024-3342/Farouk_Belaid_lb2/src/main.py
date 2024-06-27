class Node:
    def __init__(self, data, next = None):
        self.__data = data
        self.next = next

    def get_data(self):
        return self.__data
    
    def change_data(self, new_data):
        self.__data = new_data

    
    def __str__(self):
        if self.next != None:
            return f"data: {self.__data}, next: {self.next.get_data()}"
        return f"data: {self.__data}, next: {self.next}"


class LinkedList:
    def __init__(self, head = None):
        if head is None:
            self.__head__ = None
            self.__length = 0
        else:
            self.__head__ = Node(head)
            self.__length = 1

    def __len__(self):
        return self.__length

    def append(self, element):
        self.__length += 1
        if self.__head__ == None:
            self.__head__ = Node(element)
        else:
            tmp = self.__head__
            while tmp.next!= None:
                tmp = tmp.next
            tmp.next = Node(element)
            
    def __str__(self):
        if self.__length == 0:
            return "LinkedList[]"
        else:
            tmp = self.__head__
            string = tmp.__str__()
            while tmp.next != None:
                tmp = tmp.next
                string += "; " + tmp.__str__()
            return f'LinkedList[length = {self.__length}, [{string}]]'

    def pop(self):
        if self.__length == 0:
            raise IndexError("LinkedList is empty!")
        tmp = self.__head__
        if tmp.next != None:
            while tmp.next.next != None:
                tmp = tmp.next
            tmp.next= None            
        else: 
            self.__head__ = None
        self.__length -= 1

    def change_on_end(self, n, new_data):
        if self.__length < n or n <= 0:
            raise KeyError("<element> doesn't exist!")
        else:
            num = self.__length - n
            if num == 0:
                self.__head__.change_data(new_data)
            else:
                tmp = self.__head__
                for i in range(num):
                    tmp = tmp.next
                tmp.change_data(new_data)

    def clear(self):
        self.__length = 0
        self.__head__ = None