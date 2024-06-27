class Node:
    def __init__(self, data, next=None):
        self.data = data
        self.next = next

    def get_data(self):
        return self.data
        
    def change_data(self, new_data):
        self.data = new_data
        
    def __str__(self):
        if self.next != None:
            return f'data: {self.data}, next: {self.next.data}'
        else:
            return f'data: {self.data}, next: None'


class LinkedList:
    def __init__(self, head = None):
        self.head = head
        self.length = len(self)

    def __len__(self):
        count = 0
        current_element = self.head
        while current_element != None:
            current_element = current_element.next
            count+=1
        return count

    def append(self, element):
        new_element = Node(element)
        if self.length == 0:
            self.__init__(new_element)
        else:
            current_element = self.head
            while current_element.next != None:
                current_element = current_element.next
            current_element.next = new_element
            self.length+=1
        
    def __str__(self):
        if self.length == 0:
            return "LinkedList[]"
        else:
            string = ''
            current_element = self.head
            while current_element != None:
                string+=str(current_element)+'; '
                current_element = current_element.next
            string = string[:-2]
            return f'LinkedList[length = {self.length}, [{string}]]'

    def pop(self):
        if self.length == 0:
            raise IndexError('LinkedList is empty!')
        else:
            current_element = self.head
            for i in range(self.length-2):
                current_element = current_element.next
            current_element.next = None
            self.length-=1

    def change_on_start(self, n, new_data):
        if self.length < n or n<=0:
            raise KeyError("Element doesn't exist!")
        else:
            current_element = self.head
            for i in range(n-1):
                current_element = current_element.next
            current_element.data = new_data

    def clear(self):
        self.head = None
        self.length = 0


