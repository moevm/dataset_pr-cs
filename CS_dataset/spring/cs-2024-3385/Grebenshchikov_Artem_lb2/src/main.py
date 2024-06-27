class Node:
    def __init__(self, data, next = None):
        self.__data = data
        self.next = next
        
    def get_data(self):
        return self.__data
    
    def change_data(self, new_data):
        self.__data = new_data
    
    def __str__(self):
        return f'data: {self.__data}, next: {self.next.__data if self.next else None}'


class LinkedList:
    def __init__(self, head = None):
        self.__head = head
        if head is None:
            self.__length = 0
        else:
            self.__length = 1
    
    def __len__(self):
        return self.__length
    
    def append(self, element):
        node = Node(element)
        tmp = self.__head
        if tmp is None:
            self.__head = node
        else:
            while tmp.next is not None:
                tmp = tmp.next
            tmp.next = node
        self.__length += 1
    
    def __str__(self):
        if self.__length == 0:
            return "LinkedList[]"
        else:
            string = f'LinkedList[length = {self.__length}, ['
            tmp = self.__head
            while tmp is not None:
                string += f'{tmp.__str__()}; '
                tmp = tmp.next
            return string[0:len(string)-2] + ']]'
    
    def pop(self):
        if self.__length == 0:
            raise (IndexError('LinkedList is empty!'))
        elif self.__length == 1:
            self.__head = None
            self.__length = 0
        elif self.__length > 1:
            tmp = self.__head
            while (tmp.next.next is not None):
                tmp = tmp.next
            tmp.next = None
            self.__length -= 1
    
    def change_on_end(self, n, new_data):
        if self.__length < n or n <= 0:
            raise (KeyError(f"{n} doesn't exist!"))
        else:
            tmp = self.__head
            cnt = 0
            while cnt != self.__length-n:
                tmp = tmp.next
                cnt += 1
            tmp.change_data(new_data)
    
    def clear(self):
        self.__head = None
        self.__length = 0
