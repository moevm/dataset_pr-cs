class Node():
    def __init__(self, data, next=None):
        self.__data = data
        self.next = next
    def get_data(self):
        return self.__data
    def __str__(self):
        if self.next == None:
            return (f"data: {self.__data}, next: None")
        else:
            return (f"data: {self.__data}, next: {self.next.__data}")


class LinkedList():
    def __init__(self, head=None):
        self.head = head
    def __len__(self):
        if self.head == None:
            return 0
        else:
            ptr = self.head
            c = 0
            while (ptr):
                c+=1
                ptr = ptr.next
            return c
    def append(self, element):
        new_el = Node(element)
        if self.head == None:
            self.head = new_el
        else:
            ptr = self.head
            while(ptr.next):
                ptr = ptr.next
            ptr.next = new_el
    def __str__(self):
        if self.head == None:
            return f"LinkedList[]"
        else:
            ptr = self.head
            l = []
            while (ptr):
                l.append(ptr.__str__())
                ptr =ptr.next
            return f"LinkedList[length = {len(self)}, [{'; '.join(l)}]]"
    def pop(self):
        if len(self) == 0:
            raise IndexError('LinkedList is empty!')
        elif len(self) == 1:
            self.head = None
        else:
            ptr = self.head
            while(ptr.next.next):
                ptr = ptr.next
            ptr.next = None

    def clear(self):
        if len(self)>0:
            while(self.head):
                t = self.head.next
                self.next = None
                self.head = t

    def delete_on_end(self, n):
        if len(self) < n or n<=0:
            raise KeyError("Element doesn't exist!")
        else:
            id = len(self)-n+1
            if id==1:
                t = self.head.next
                self.head = None
                self.head = t
            else:
                c= 1
                ptr = self.head
                while(c +1 !=id and ptr.next.next != None):
                    ptr = ptr.next
                    c+=1
                t = ptr.next.next
                ptr.next = None
                ptr.next = t
