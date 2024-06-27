
class Node:
    def __init__(self, data, nxt=None):  # Careful built-in func name
        self.data = data
        self.next = nxt


    def get_data(self):
        return self.data
        

    def change_data(self, new_data):  # set data
        self.data = new_data


    def __str__(self):
        return f'data: {self.data}, next: {self.next.data}' if self.next != None else f'data: {self.data}, next: None'


class LinkedList:
    def __init__(self, head=None):  # No example for init with arg / head -> var
        self.head = None
        self.length = 0

        if head != None:
            self.append(head)


    def __len__(self):
        return self.length
    

    def __str__(self):
        if self.length == 0:
            return 'LinkedList[]'
        
        res = f'LinkedList[length = {self.length}, ['
        node = self.head
        while node != None:
        
            if node != self.head:
                res += ' '

            if node.next == None:
                res += f'data: {node.data}, next: None'  # Check formating
            else:
                res += f'data: {node.data}, next: {node.next.data};'  # Check formating
            node = node.next
    
        res += ']]'

        return res


    def append(self, element):
        if self.head == None:
            self.head = Node(element)  # Python names specific - binding, no poiter logic
            self.length += 1
            return

        last = self.head
        while last.next != None:
            last = last.next

        last.next = Node(element)
        self.length += 1


    def pop(self):
        if self.length == 0:  # self.head = None
            raise IndexError('LinkedList is empty!')
        elif self.length == 1:
            self.head = None
            self.length -= 1
            return

        penult = self.head
        for _ in range(self.length - 2):  # required len - 1, also starting from zero
            penult = penult.next

        penult.next = None  # Garbage collector
        self.length -= 1

        
    def change_on_start(self, n, new_data):
        if n > self.length or n <= 0:
            raise KeyError('Element doesn\'t exist!')

        node = self.head
        for _ in range(n - 1):
            node = node.next

        node.data = new_data


    def clear(self):  # How handle self.head?...
        self.length = 0
        self.head = None  # Garbage collector...

