class Node:
    def __init__(self, data, next = None):
        self.__data = data
        self.next = next
        
    def get_data(self):
        return self.__data
    
    def change_data(self, new_data):
        self.__data = new_data
        
    def __str__(self):
        if self.next is not None:
            return f"data: {self.get_data()}, next: {self.next.get_data()}"
        else:
            return f"data: {self.get_data()}, next: None"
    
class LinkedList:
    def __init__(self, head = None):
        self.head = head
        if head is not None:
            self.length = 1 
        else:
            self.length = 0
            
    def __len__(self):
        return self.length
    
    def append(self, element):
        new_node = Node(element)
        if self.head is not None:
            current = self.head
            while current.next is not None:
                current = current.next
            current.next = new_node
        else:
            self.head = new_node
        self.length += 1 
    
    def __str__(self):
        if self.head is None:
            result = f"LinkedList[]"
        else:
            result = f"LinkedList[length = {self.length}, ["
            current = self.head
            while current is not None:
                if current.next is None:
                    result += f"data: {current.get_data()}, next: None]]"
                else:
                    result += f"data: {current.get_data()}, next: {current.next.get_data()}; "
                current = current.next
        return result
    
    def pop(self):
        if self.head is None:
            raise IndexError("LinkedList is empty!")
        elif self.head.next is None:
            self.head = None
        else:
            current = self.head
            while current.next.next is not None:
                current = current.next
            current.next = None
        self.length -= 1 
    
    def clear(self):
        self.head = None 
        self.length = 0
    
    def change_on_start(self, n, new_data):
        if n > self.length or n <= 0:
            raise KeyError("Element doesn't exist!")
        current = self.head
        for i in range(n-1):
            current = current.next
        current.change_data(new_data)
        
        