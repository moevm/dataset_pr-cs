class Node:
    def __init__(self, data, next = None):
        self.__data = data
        self.next = next

    def get_data(self):
        return self.__data

    def __next__(self):
        if self.next == None:
            raise StopIteration
    
        self.__data = self.next.__data
        self.next   = self.next.next
        return self 

    def __str__(self):
        return f"data: {self.__data}, next: {None if self.next == None else self.next.__data}"

class LinkedList:
    def __calculate_length(self):
        cur = self.__head
        cnt = 0
        while cur != None:
            cnt += 1
            cur = cur.next
            
        return cnt

    def __init__(self, head = None):
        self.__head   = head
        self.__length = self.__calculate_length()

    def __iter__(self):
        return Node(None, self.__head)

    def __len__(self):
        return self.__length

    def append(self, element):
        if self.__length == 0:
            self.__head = Node(element)
            self.__length = 1
            return
        
        cur = self.__head
        while cur.next != None:
            cur = cur.next
        cur.next = Node(element)
        self.__length += 1

    def __str__(self):
        if self.__length == 0:
            return "LinkedList[]"

        return f"LinkedList[length = {self.__length}, [{'; '.join(map(str, self))}]]"

    def pop(self):
        if self.__length == 0:
            raise IndexError("LinkedList is empty!")

        prev = None
        cur = self.__head
        while cur.next != None:
            prev = cur
            cur = cur.next
        
        if prev == None:
            self.__head = None
        else:
            prev.next = None
        del cur
        self.__length -= 1

    def clear(self):
        self.__head = None
        self.__length = 0

    def delete_on_start(self, n):
        if n < 1:
            raise KeyError("Element doesn`t exist!")        

        prev = None
        cur = self.__head
        
        for i in range(n - 1):
            prev = cur
            cur = cur.next
            if cur == None:
                raise KeyError("Element doesn`t exist!")
        
        if prev == None:
            self.__head = cur.next
        else:
            prev.next = cur.next
        del cur
        self.__length -= 1
