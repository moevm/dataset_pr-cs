class Node:
    def __init__(self, data, next=None):
        self.__data = data
        self.next  = next

    def get_data(self):
        return self.__data

    def __str__(self):
        return f"data: {self.get_data()}, next: {self.next.get_data() if self.next else None}"


class LinkedList:
    def __init__(self, head=None):
        self.head = head
        if (head):
            self.length = 1
        else:
            self.length = 0

    def __len__(self):
        return self.length

    def append(self, element):
        current_node = self.head
        if (current_node):
            while (current_node.next):
                current_node = current_node.next
            current_node.next = Node(element)
        else:
            self.head = Node(element)
        self.length += 1

    def __str__(self):
        if (self.length == 0):
            return "LinkedList[]"
        current_node = self.head
        output = f"LinkedList[length = {self.length}, ["
        output += str(current_node)
        current_node = current_node.next
        while (current_node):
            output += "; "
            output += str(current_node)
            current_node = current_node.next
        output += "]]"
        return output

    def pop(self):
        current_node = self.head
        if self.length == 0:
          raise  IndexError("LinkedList is empty!")
        elif self.length == 1:
            self.head = None
            self.length = 0
        else:
            while (current_node.next.next):
                current_node = current_node.next
            current_node.next = None
            self.length -= 1
 
    def delete_on_end(self, n):
        if (self.length < n or n < 1):
            raise KeyError("Element doesn't exist!")
        
        if (self.length == n):
            self.head = self.head.next
        else:
            current_node = self.head
            for i in range(self.length - n - 1):
                current_node = current_node.next
            current_node.next = current_node.next.next
        self.length -= 1

    def clear(self):
        self.head = None
        self.length = 0