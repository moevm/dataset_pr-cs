class Node:
    def __init__(self, data, next = None):
        self.data = data
        self.next = next
    
    def get_data(self):
        return self.data
    
    def __str__(self):
        if self.next is not None:
            return f'data: {self.data}, next: {(self.next).data}'
        return f'data: {self.data}, next: None'
    

class LinkedList:
    def __init__(self, head = None):
        self.head = head
        c = 0
        cur_node = head
        while cur_node is not None:
            c += 1
            cur_node = cur_node.next
        self.length = c
    
    def __len__(self):
        return self.length
    
    def append(self, element):
        new_node = Node(element)
        if self.length == 0:
            self.head = new_node
        else:
            cur_node = self.head
            while cur_node.next is not None:
                cur_node = cur_node.next
            cur_node.next = new_node
        self.length += 1
    
    def __str__(self):
        if self.length == 0:
            return 'LinkedList[]'
        s = f'LinkedList[length = {self.length}, ['
        cur_node = self.head
        while cur_node.next is not None:
            s += f'{str(cur_node)}; '
            cur_node = cur_node.next
        s += f'{str(cur_node)}]]'
        return s
    
    def pop(self):
        if self.length == 0:
            raise IndexError('LinkedList is empty!')
        if self.length == 1:
            self.head = None
        else:
            cur_node = self.head
            while (cur_node.next).next is not None:
                cur_node = cur_node.next
            cur_node.next = None
        self.length -= 1
    
    def clear(self):
        self.head = None
        self.length = 0
    
    def delete_on_start(self, n):
        if self.length < n or n <= 0:
            raise KeyError("Element doesn't exist!")
        if n == 1:
            self.head = self.head.next
        else:
            cur_node = self.head
            for i in range(n - 2):
                cur_node = cur_node.next
            cur_node.next = cur_node.next.next
        self.length -= 1

