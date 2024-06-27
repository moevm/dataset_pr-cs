class Node:
    def __init__(self, data, next=None):
        self.data = data
        self.next = next
        pass

    def get_data(self):
        return self.data
        pass

    def change_data(self, new_data):
        self.data = new_data
        pass

    def __str__(self):
        if self.next != None:
            return f"data: {self.data}, next: {self.next.data}"
        else: return f"data: {self.data}, next: None"
        pass


class LinkedList:
    def __init__(self, head=None):
        self.head = head
        if self.head!=None: self.length = 1
        else: self.length = 0
        pass

    def __len__(self):
        return self.length
        pass

    def append(self, element):
        a = Node(element)
        if self.head!=None:
            cur = self.head
            for i in range(self.length-1):
                cur = cur.next
            cur.next = a
        else: self.head = a
        self.length = self.length + 1
        pass

    def __str__(self):
        if self.length == 0:
            return f"LinkedList[]"
        else:
            st = f"LinkedList[length = {self.length}, [{str(self.head)}"
            cur = self.head
            for i in range(self.length-1):
                cur = cur.next
                st +=';'+ ' ' + str(cur)
            st+= "]]"
            return st
        pass

    def pop(self):
        if self.length==0:
            raise IndexError("LinkedList is empty!")
        elif self.length==1:
            self.head = None
            self.length -=1
        else:
            cur = self.head
            for i in range(self.length-2):
                cur = cur.next
            cur.next = None
            self.length -=1


    def change_on_start(self, n, new_data):
        if n<1:
            raise KeyError("Element doesn't exist!")
        if self.length<n:
            raise KeyError("Element doesn't exist!")
        else:
            cur = self.head
            n = n-1
            for i in range(n):
                cur = cur.next
            cur.data = new_data
        pass

    def clear(self):
        self.head = None
        self.length = 0
        pass