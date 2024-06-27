class Node:
    def __init__(self, data, next=None):
        self.__data = data
        self.next = next

    def get_data(self):
        return self.__data
        
    def change_data(self, new_data):
        self.__data = new_data

    def __str__(self):
        if self.next is None:
            return f"data: {self.get_data()}, next: {self.next}"
        return f"data: {self.get_data()}, next: {self.next.get_data()}"

class LinkedList:
    def __init__(self, head=None):
        self.head = head
        self.length = 0 if head is None else 1

    def __len__(self):
        return self.length

    def append(self, element):
        new_node = Node(element)
        self.length += 1

        if self.head is None:
            self.head = new_node
            return
        
        current_node = self.head

        while current_node.next is not None:
            current_node = current_node.next
            
        current_node.next = new_node
        

    def __str__(self):
        if self.head is None:
            return "LinkedList[]"
        
        current_node = self.head
        data = ""

        while current_node is not None:
            if current_node.next is not None:
                data += f"{current_node}; "
            else:
                data += f"{current_node}"
            current_node = current_node.next    

        return f"LinkedList[length = {self.length}, [{data}]]" 

    def pop(self):
        if self.head is None:
            raise IndexError("LinkedList is empty!")
        else:
            current_node = self.head
            self.length -= 1

            if current_node.next is None:
                self.head = None
                return
            
            while current_node.next.next is not None:   
                current_node = current_node.next
            
            current_node.next = None

    def change_on_end(self, n, new_data):
        if n > self.length or n <= 0:
            raise KeyError("Element doesn't exist!")
        
        current_node = self.head
        for _ in range(self.length - n):
            current_node = current_node.next

        current_node.change_data(new_data)

    def clear(self):
        self.head = None
        self.length = 0