class Node:
    def __init__(self, data, next=None):
        self.__data = data
        self.next = next
        

    def get_data(self):
        return self.__data
        
        
    def change_data(self, new_data):
        self.__data = new_data
        

    def __str__(self):
        if self.next:
            return f"data: {self.__data}, next: {self.next.get_data()}"
        else:
            return f"data: {self.__data}, next: None"
        


class LinkedList:
    def __init__(self, head = None):
        if not head:
            self.head = None
            self.length = 0
        else:
            self.head = Node(head)
            self.length = 1
        

    def __len__(self):
        return self.length
        

    def append(self, element):
        new_node = Node(element)
        if not self.head:
            self.head = new_node
        else:
            current = self.head
            while current.next:
                current = current.next
            current.next = new_node
        self.length += 1


            
    def __str__(self):
         if not self.head:
            return "LinkedList[]"
         else:
            result = f"LinkedList[length = {self.length}, ["
            current = self.head
            while current.next:
                result += f"data: {current.get_data()}, next: {current.next.get_data()}; "
                current = current.next
            result += f"data: {current.get_data()}, next: {current.next}]"
            return result + "]"

    def pop(self):
        if not self.head:
            raise IndexError("LinkedList is empty!")
        if self.length == 1:
            self.head = None
            self.length = 0
        else:
            current = self.head
            while current.next.next:
                current = current.next
            current.next = None
            self.length -= 1

    def change_on_start(self, n, new_data):
        if self.length < n:
            raise KeyError("Element doesn't exist!")
        elif n <= 0:
             raise KeyError("Element doesn't exist!")
        else:
            current = self.head
            for _ in range(n-1):
                current = current.next
            current.change_data(new_data)

    def clear(self):
        self.length = 0
        self.head = None
        
