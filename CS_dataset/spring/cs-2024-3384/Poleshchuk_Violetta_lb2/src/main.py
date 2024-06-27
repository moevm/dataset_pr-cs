class Node:
    def __init__(self, data, next=None):
        self.__data = data
        self.next = next

    def get_data(self):
        return self.__data

    def __str__(self):
        return f"data: {self.__data}, next: {None if self.next == None else self.next.__data}"


class LinkedList:
    def __init__(self, head = None):
        self.head = head
        self.length = 0
        if head is not None:
            self.length = 1

    def __len__(self):
        return self.length

    def append(self, element):
        node = Node(element)
        tmp = self.head
        if self.head is None:
            self.head = node
        else:
            while tmp.next:
                tmp = tmp.next
            tmp.next = node
        self.length += 1
                
    def __str__(self):
        if self.head is None:
            return  "LinkedList[]"
        tmp = self.head
        lst = []
        while tmp:
            lst.append(str(tmp))
            tmp = tmp.next
        return f"LinkedList[length = {self.length}, " + "[" + ('; '.join(lst)) + "]]"    

    def pop(self):
        if self.head is None:
            raise IndexError("LinkedList is empty!")
        if self.length == 1:
            self.head = None
            self.length = 0
        else:
            tmp = self.head
            prev = None
            while tmp.next:
                prev = tmp
                tmp = tmp.next
            prev.next = None
            self.length -= 1



    def delete_on_start(self, n):
        
        if n > self.length or n <= 0:
            raise KeyError("Element doesn't exist!")
        elif n == 1:
            self.head = self.head.next
        else:
            tmp = self.head
            for _ in range(n-2):
                tmp = tmp.next
            tmp.next = tmp.next.next    
        self.length -= 1


    def clear(self):
        self.head = None
        self.length = 0