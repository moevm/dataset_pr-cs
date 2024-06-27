class Node:
    def __init__(self, data, next = None):
        self.next = next
        self.__data = data
        
    def get_data(self):
        return self.__data
        
    def change_data(self, new_data):
        self.__data = new_data
        
    def __str__(self):
        n = self.next
        if n:
            n = n.__data
        return f'data: {self.__data}, next: {n}'


class LinkedList:
    def __init__(self, head = None):
        self.__head__ = head
        self.__length = 0
        if head:
            self.__length +=1
            
    def __len__(self):
        return self.__length
        
    def append(self, element):
        tmp = Node(element)
        if self.__head__ == None:
            self.__head__ = tmp
            self.__length = 1
        else:
            cur = self.__head__
            while cur.next:
                cur = cur.next
            cur.next= tmp
            self.__length += 1
            
    def __str__(self):
        n = ""
        if self.__length != 0:
            node_list = []
            cur = self.__head__
            while cur.next:
                node_list.append(str(cur))
                cur = cur.next
            node_list.append(str(cur))

            n = "length = " + str(self.__length) +f', [{"; ".join(node_list)}]'
        return f'LinkedList[{n}]'
        
    def pop(self):
        if self.__length == 0:
            raise IndexError("LinkedList is empty!")
        elif self.__length == 1:
            self.__length = 0
            self.__head__ = None
        else:
            cur = self.__head__
            while cur.next.next:
                cur = cur.next
            cur.next = None
            self.__length -=1
    def clear(self):
        while self.__length != 0:
            self.pop()
            
    def change_on_start(self, n, new_data):
        if self.__length < n or n <= 0:
            raise KeyError("Element doesn't exist!")
        else:
            cur = self.__head__
            for i in range (n-1):
                cur = cur.next
            cur.change_data( new_data )
