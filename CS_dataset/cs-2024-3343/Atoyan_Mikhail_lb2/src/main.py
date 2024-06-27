class Node:
    def __init__(self, data, next=None):
        self.__data = data
        self.next = next

    def get_data(self):
        return self.__data

    def __str__(self):
        return f"data: {self.__data}, next: {self.next.__data if self.next else None}"


class LinkedList:
    def __init__(self, head = None):
        self.head = head
        self.length = 1 if head else 0

    def __len__(self):
        return self.length

    def append(self, data):
        if (self.head):
            current = self.head
            while (current.next):
                current = current.next
            current.next = Node(data)
        else:
            self.head = Node(data)
        self.length += 1

    def __str__(self):
        current = self.head
        if (current == None):
            return "LinkedList[]"
        list_of_nodes = []
        while current:
            list_of_nodes.append(str(current))
            current = current.next
        return f"LinkedList[length = {len(self)}, [{'; '.join(list_of_nodes)}]]"
    
    def pop(self):
        if (len(self) == 0):
            raise IndexError("LinkedList is empty!")
        current = self.head
        if (len(self) == 1):
            self.head = None
        else:
            while(current.next.next):
                current = current.next
            current.next = None
        self.length -= 1
    
    def clear(self):
        self.head = None
        self.length = 0
    
    def delete_on_start(self, n):
        if (n > len(self) or n < 1):
            raise KeyError("Element doesn't exist!")
        current = self.head
        if (n == 1):
            self.head = self.head.next
        else:
            for _ in range(n-2):
                current = current.next
            current.next = current.next.next
        self.length -= 1