class Node:
    def __init__(self, data, next=None):
        self.__data = data
        self.__next__ = next
    
    def get_data(self):
        return self.__data

    def change_data(self, new_data):
        self.__data = new_data
    
    def __str__(self):
        return f"data: {self.__data}, next: {self.__next__.__data if self.__next__ is not None else None}"
    
class LinkedList:
    def __init__(self, head=None):
        self.__head__ = head
        self.__length = 0

    def __len__(self):
        return self.__length

    def append(self, element):
        self.__length += 1
        elem = Node(element, None)
        if self.__head__ is not None:
            tmp = self.__head__
            while tmp.__next__ is not None:
                tmp = tmp.__next__
            tmp.__next__ = elem
        else:
            self.__head__ = elem

    def __str__(self):
        if self.__head__ is not None:
            temp = self.__head__
            el = f'{temp}'
            while temp.__next__ is not None:
                temp = temp.__next__
                el += '; ' + temp.__str__()
            return f'LinkedList[length = {self.__length}, [{el}]]'
        else:
            return f'LinkedList[]'
    
    def pop(self):
        if self.__length == 1:
            self.__length -= 1
            self.__head__ = None
        elif self.__length != 0:
            temp = self.__head__
            while temp.__next__.__next__ is not None:
                temp = temp.__next__
            temp.__next__ = None
            self.__length -= 1
        else:
            raise IndexError('LinkedList is empty!')
    
    def change_on_end(self, n, new_data):
        if self.__length < n or n <= 0:
            raise KeyError(f"<element> doesn't exist!")
        else:
            tmp = self.__head__
            length = self.__length
            while length != n:
                length -= 1
                tmp = tmp.__next__
            tmp.change_data(new_data)

    def clear(self):
        self.__head__ = None
        self.__length = 0