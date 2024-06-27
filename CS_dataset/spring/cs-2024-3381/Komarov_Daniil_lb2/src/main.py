class Node:
    def __init__(self, data, next=None):
        self.data = data
        self.next = next

    def get_data(self):
        return self.data

    def change_data(self, new_data):
        self.data = new_data

    def __str__(self):
        return f"data: {self.data}, next: {self.next.data if self.next else None}"

class LinkedList:
    def __init__(self, head=None):
        self.head = head
        self.length = (1 if head != None else 0)

    def __len__(self):
        return self.length

    def append(self, element):
        new_el = Node(element)
        if(self.head != None): # Append to the end
            last = self.head
            while(last.next != None): last = last.next
            last.next = new_el
        else: # Create new list with 1 element
            self.head = new_el
        self.length += 1

    def __str__(self):
        if(self.length):
            els_str = []
            last = self.head
            while(last != None):
                els_str.append(str(last))
                last = last.next
            return f"LinkedList[length = {self.length}, [{'; '.join(els_str)}]]"
        else:
            return "LinkedList[]"

    def pop(self):
        if(self.length == 0): raise IndexError("LinkedList is empty!")
        elif(self.length == 1): self.head = None
        else:
            pre_last = self.head
            while(pre_last.next.next != None): pre_last = pre_last.next
            pre_last.next = None
        self.length -= 1

    def clear(self):
        self.head = None
        self.length = 0

    def change_on_end(self, n, new_data):
        if(self.length < n or n < 1): raise KeyError("Element doesn't exist!")
        i = self.length - n
        el = self.head
        for _ in range(i): el = el.next
        el.data = new_data

