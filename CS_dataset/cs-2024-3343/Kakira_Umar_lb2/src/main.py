class Node:
    def __init__(self, data, next=None):
        self.__data = data
        self.next = next

    def get_data(self):
        return self.__data


    def __str__(self):        
        if self.next != None:
            return f"data: {self.__data}, next: {self.next.get_data()}"        
        return f"data: {self.__data}, next: {self.next}"

class LinkedList:
    def __init__(self, head = None):
        if head is not None:
            self.__length = 1
            self.__head__ = Node(head)
        else:
            self.__length = 0
            self.__head__ = None

    def __len__(self):
        return self.__length

    def append(self, element):
        node = Node(element)
        if self.__head__ is None:
            self.__head__ = node
        else:
            tmp = self.__head__
            while tmp.next is not None:
                tmp = tmp.next
            tmp.next = node
        self.__length += 1
            
    def __str__(self):
        if self.__length > 0:
            node_list = []
            tmp = self.__head__
            while tmp is not None:
                node_list.append(tmp.__str__())
                tmp = tmp.next
            node_list = '; '.join(node_list)
            return f"LinkedList[length = {self.__length}, [{node_list}]]"
        else:
            return "LinkedList[]"

    def pop(self):
        if self.__length == 0:
            raise IndexError("LinkedList is empty!")
        elif self.__length == 1:
            self.__length = 0
            self.__head__ = None
        else:
            tmp = self.__head__
            while tmp.next.next is not None:
                tmp = tmp.next
            self.__length -= 1
            tmp.next = None

    def delete_on_start(self, n):
        if n < 1 or n > self.__length:
            raise KeyError(f"{n} doesn't exist!")
        elif n == 1:
            self.__head__ = self.__head__.next
        else:
            tmp = self.__head__
            for i in range(n - 2):
                tmp = tmp.next
            tmp.next = tmp.next.next
        self.__length -= 1

    def clear(self):
        self.__head__ = None
        self.__length = 0