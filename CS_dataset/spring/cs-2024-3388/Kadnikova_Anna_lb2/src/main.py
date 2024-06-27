class Node:
    def __init__(self, data, next = None):
        self.__data = data 
        self.next = next
    def get_data(self):
        return self.__data 
    def __str__(self):
        return f"data: {self.__data}, next: {None if self.next is None else self.next.get_data()}"
    

class LinkedList:
    def __init__(self, head=None):
        self.head = head 
        self.__length = 0
        if head is not None:
            self.__length = 1

    def __len__(self):
        return self.__length

    def append(self, element):
        nxt = Node(element)
        if self.__len__()==0:
            self.head = nxt 
            self.__length = 1
            return
        curr = self.head 
        while curr.next is not None:
            curr = curr.next 
        curr.next = nxt 
        self.__length+=1

    def __str__(self):
        if self.__length == 0:
            return "LinkedList[]"
        else:
            s = f"LinkedList[length = {self.__length}, ["
            curr = self.head 
            while curr.next is not None:
                si = f"data: {curr.get_data()}, next: {curr.next.get_data()}; "
                s+=si 
                curr = curr.next
            si = f"data: {curr.get_data()}, next: {curr.next}]]"
            s+=si 
            return s

    def pop(self):
        if self.__length==0:
            raise IndexError("LinkedList is empty!")
        else:
            curr = self.head
            prev = self.head
            while curr.next is not None:
                prev = curr 
                curr = curr.next
            prev.next = None
            self.__length -=1

    def delete_on_end(self, n):
        if self.__length<n or n<=0:
            raise KeyError("Element doesn't exist!")
        elif n == self.__length:
            self.head = self.head.next
            self.__length -= 1
        else:
            k = self.__length - n 
            i = 0
            curr = self.head 
            prev = self.head
            while i!=k:
                prev = curr 
                curr = curr.next
                i+=1
            prev.next = curr.next 
            self.__length -= 1


    def clear(self):
        self.head = None 
        self.__length = 0