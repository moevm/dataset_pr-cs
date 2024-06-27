class Node:
    
    def __init__(self, data, next=None):
        self.data = data
        self.next = next

    def get_data(self):
        return self.data

    def __str__(self):
        next_data = self.next.data if self.next else None
        return f"data: {self.data}, next: {next_data}"


class LinkedList:
    def __init__(self, head=None):
        self.head = head
        self.length = 0 if head is None else 1

    def __len__(self):
        return self.length

    def append(self, element):
        new_node = Node(element)
        if self.head is None:
            self.head = new_node
        else:
            current = self.head
            while current.next:
                current = current.next
            current.next = new_node
        self.length += 1

    def __str__(self):
        if self.head is None:
            return "LinkedList[]"
        else:
            current = self.head
            result = "LinkedList[length = {}, [".format(self.length)
            while current:
                result += f"data: {current.data}, next: {current.next.data if current.next else None}; "
                current = current.next
            result = result[:-2] + "]]"
            return result

    def pop(self):
        if self.head is None:
            raise IndexError("LinkedList is empty!")
        current = self.head
        if current.next is None:
            self.head = None
            self.length -= 1
            return current.data
        while current.next.next:
            current = current.next
        popped_data = current.next.data
        current.next = None
        self.length -= 1
        return popped_data
     
    def clear(self):
        self.head = None
        self.length = 0
        
    def delete_on_end(self, n):
        if (n < 1 or self.length < n):
            raise KeyError("<element> doesn't exist!")
        
        if (n == self.length):
            self.head = self.head.next
            self.length -= 1
            return
        
        current = self.head
        for i in range(self.length-n-1):
            current = current.next
        current.next = current.next.next
        self.length -= 1
