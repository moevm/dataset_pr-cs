class Node:
    def __init__(self, data, next=None):
        self.data = data
        self.next = next

    def get_data(self):
        return self.data
        
    def change_data(self, new_data):
        self.data = new_data

    def __str__(self):
        if self.next == None:
            return f'data: {self.data}, next: None'
        else:
            return f'data: {self.data}, next: {self.next.get_data()}'


class LinkedList:
    def __init__(self, head = None):
        self.head = head
        self.length = len(self)

    def __len__(self):
        length = 0
        head = self.head
        while head != None:
            head = head.next
            length += 1
        return length
        
    def append(self, element):
        new_element = Node(element)
        if len(self) == 0:
            self.__init__(new_element)
        else:
            head = self.head
            for i in range(len(self) - 1):
                head = head.next
            head.next = new_element

    def __str__(self):
        if len(self) == 0:
            return 'LinkedList[]'
        else:
            list_data = []
            head = self.head
            while head != None:
                list_data.append(str(head))
                head = head.next
            list_data = '; '.join(list_data)
            return f'LinkedList[length = {len(self)}, [{list_data}]]'
            
    def pop(self):
        if len(self) == 0:
            raise IndexError("LinkedList is empty!")
        elif len(self) == 1:
            self.head = None
        else:
            head = self.head
            for i in range(len(self) - 2):
                head = head.next
            head.next = None
            
    def change_on_start(self, n, new_data):
        if((len(self) < n) or (n <= 0)):
            raise KeyError("Element doesn't exist!")
        else:
            head = self.head
            for i in range(n - 1):
                head = head.next
            head.change_data(new_data)

    def clear(self):
        self.head = None