class Node:
    def __init__(self, data, next=None):
        self._data = data
        self.next = next

    def get_data(self):
        return self._data

    def __str__(self):
        return f'data: {self.get_data()}, next: {self.next.get_data()}' if self.next else f'data: {self.get_data()}, next: {None}'


class LinkedList:
    def __init__(self, head = None):
        self.head = head
        self.length = 1 if self.head else 0

    def __len__(self):
        if self.length == 0: return 0
        amount = 0
        current_el = self.head
        while current_el != None:
            current_el = current_el.next
            amount+=1
        return amount

    def append(self, element):
        new_elem = Node(element)
        current_el = self.head
        if current_el != None:
            while current_el.next != None:
                current_el = current_el.next
            current_el.next = new_elem
        else: self.head = new_elem
        self.length += 1
            
    def __str__(self):
        if self.length <= 0: return "LinkedList[]"
        else: 
            nodes_data = []
            current_el = self.head
            while current_el != None:
                nodes_data.append(str(current_el))
                current_el = current_el.next
            return f"LinkedList[length = {len(self)}, [{'; '.join(nodes_data)}]]"

    def pop(self):
        if not self.length: 
            raise IndexError("LinkedList is empty!")
        if self.length == 1: 
                self.head = None
                
        else:
            current_el = self.head
            while current_el.next.next != None:
                current_el = current_el.next
            current_el.next = None
        self.length -=1


    def delete_on_start(self, n):
        current_el = self.head
        if (n > self.length or n<=0) :
            raise KeyError("Element doesn't exist!")
        else:
            if n == 1:
                self.head = current_el.next
            else: 
                for i in range(n-2):
                    current_el = current_el.next
                current_el.next = current_el.next.next if current_el.next != None else None
            self.length -=1

    def clear(self):
        current_el = self.head
        tmp = self.head
        while current_el != None:
            tmp = current_el.next
            current_el.next = None
            current_el = tmp
        self.length = 0
        self.head = None