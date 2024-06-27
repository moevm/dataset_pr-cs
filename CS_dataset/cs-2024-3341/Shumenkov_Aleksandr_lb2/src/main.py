class Node:
    def __init__(self, data, next=None):
        self.__data = data
        self.next = next

    def get_data(self):
        return self.__data
        
    def change_data(self, new_data):
        self.__data = new_data

    def __str__(self):
        return f"data: {self.get_data()}, next: {None if self.next == None else self.next.get_data()}"


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
        last_element = Node(element)
        if self.head is None:
            self.head = last_element
        else:
            current_node = self.head
            while current_node.next:
                current_node = current_node.next
            current_node.next = last_element
        self.length += 1
            
    def __str__(self):
        if self.length == 0:
            return "LinkedList[]"
        else:
            result = f"LinkedList[length = {self.length}, ["
            cur = self.head
            while(cur != None):
                result += str(cur)
                cur = cur.next
                if(cur != None):
                    result += "; "
            result += "]]"
        return result
        
    def pop(self):
        current_node = self.head
        if current_node is None:
            raise IndexError("LinkedList is empty!")
        elif self.length == 1:
                self.head = None
                self.length = 0
        elif self.length >= 2:
                while current_node.next.next:
                    current_node =current_node.next
                current_node.next = None
                self.length -= 1
    def change_on_start(self, n, new_data):
        if n > self.length or n <= 0:
            raise KeyError("Element doesn't exist!")
        current = self.head
        for i in range(n-1):
            current = current.next
        current.change_data(new_data)
    
    def clear(self):
        self.head = None
        self.length = 0