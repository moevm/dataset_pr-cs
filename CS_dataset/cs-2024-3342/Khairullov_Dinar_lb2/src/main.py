class Node:
    def __init__(self, data, next=None):
        self.__data = data
        self.next = next
        pass

    def get_data(self):
        return self.__data

    def __str__(self):
        next_data = "None" if self.next is None else self.next.get_data()
        return f"data: {self.get_data()}, next: {next_data}"
        pass


class LinkedList:
    def __init__(self, head=None):
        self.head = head
        self.length = 0 if head is None else 1
        pass

    def __len__(self):
        return self.length
        pass

    def append(self, element):
        new_node = Node(element)
        
        if self.head is None:
            self.head = new_node
        else:
            current_node = self.head
            while(current_node.next is not None):
                current_node = current_node.next
            current_node.next = new_node
        
        self.length +=1
        pass

    def __str__(self):
        if self.head is None:
            return "LinkedList[]"
        else:
            current_node = self.head
            str_list =  f"LinkedList[length = {self.length}, [{str(current_node)}"
            current_node = current_node.next
            
            while(current_node is not None):
                str_list += f"; {str(current_node)}"
                current_node = current_node.next
                
            str_list += "]]"
            return str_list
        pass

    def pop(self):
        if self.head is None:
            raise IndexError("LinkedList is empty!")
        elif self.head.next is None:
            self.length = 0
            self.head = None
        else:
            current_node = self.head
            while(current_node.next.next is not None):
                current_node = current_node.next
            current_node.next = None
            self.length -= 1
        pass

    def delete_on_end(self, n):
        
        if self.length < n or n <= 0  or self.head is None:
            raise KeyError("Element doesn't exist!")
            
        elif self.length == n:
            self.head = self.head.next
            self.length -= 1
            
        else:
            current_node = self.head
            for i in range(self.length - n - 1):
                current_node = current_node.next
            current_node.next = current_node.next.next
            
            self.length -= 1
        pass

    def clear(self):
        self.head = None
        self.length = 0
        pass
