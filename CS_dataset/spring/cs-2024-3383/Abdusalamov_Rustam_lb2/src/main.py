class Node:
    __data = None
    next = None
    def __init__(self,data,next=None):
        self.__data = data
        self.next = next
    def get_data(self):
        return self.__data
    def __str__(self):
        if (self.next): d = self.next.__data
        else: d = 'None'
        return f"data: {self.__data}, next: {d}"

class LinkedList:
    head = None
    length = 0
    def __init__(self, head=None):
        self.head = head
        self.length = 1 if (head != None) else 0
    def __len__(self):
        return self.length
    def append(self, element):
        new = Node(element)
        if self.head == None:
            self.head = new
        else:
            cur = self.head
            while(cur.next != None):
                cur = cur.next
            cur.next = new
        self.length += 1

    def __str__(self):
        if self.head == None and self.length == 0: return "LinkedList[]"
        else:
            s = f"LinkedList[length = {self.length}, ["
            cur = self.head
            while(cur.next):
                s += f"data: {cur.get_data()}, next: {cur.next.get_data()}; "
                cur = cur.next
            s += f"data: {cur.get_data()}, next: None]]"
        return s
    def pop(self):
        if self.length == 0: raise IndexError("LinkedList is empty!")
        cur = self.head
        if (cur.next == None):
            self.head = None
            self.length = 0
            return
        else:
            cur = self.head
            while(cur.next.next):
                cur = cur.next
            cur.next = None
        self.length -= 1

    def delete_on_end(self, n):
        if n > self.length or n <= 0:
            raise KeyError("Element doesn't exist!")
        if n == self.length:
            self.head = self.head.next
            self.length -= 1
            return
        prev_node = None
        current_node = self.head
        count = 0
        while current_node:
            if count == self.length - n:
                if prev_node:
                    prev_node.next = current_node.next
                else:
                    self.head = current_node.next
                self.length -= 1
                return
            prev_node = current_node
            current_node = current_node.next
            count += 1


    def clear(self):
        self.head = None
        self.length = 0