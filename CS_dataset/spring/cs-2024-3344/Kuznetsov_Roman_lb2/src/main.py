class Node:
    def __init__(self, data, next=None):
        self.data, self.next = data, next

    def get_data(self):
        return self.data
        
    def change_data(self, new_data):
        self.data = new_data

    def __str__(self):
        return f"data: {self.get_data()}, next: {self.next.get_data() if self.next else None}"


class LinkedList:
    def __init__(self, head = None):
        self.lenght, self.head = 0, head
        
        tmp = self.head
        while tmp:
            tmp, self.lenght = self.next, self.lenght + 1

    def __len__(self):
        return self.lenght

    def append(self, element):
        self.lenght, tmp = self.lenght + 1, self.head
        
        if self.head:
            while tmp.next:
                tmp = tmp.next
            tmp.next = Node(element)
        else:
            self.head = Node(element)    

    def __str__(self):
        tmp, link = self.head, "LinkedList["

        if self.head:
            link += f"length = {self.lenght}, ["
            
            while tmp:
                link += f"data: {tmp.get_data()}, next: {tmp.next.get_data() if tmp.next else None}"
                if tmp.next:
                    link += "; "
                tmp = tmp.next
            
            link += "]]"
        else:
            link += "]"

        return link


    def pop(self):
        if not self.head:
            raise IndexError("LinkedList is empty!")

        self.lenght -= 1
        if self.head.next:
            tmp = self.head
            
            while tmp.next.next:
                tmp = tmp.next
            
            tmp.next = None
        else:
            self.head = None


    def change_on_end(self, n, new_data):
        if not 0 < n <= self.lenght:
            raise KeyError("Element doesn't exist!")
    
        cnt, tmp = 0, self.head
        
        while tmp.next and cnt != self.lenght - n:
            tmp, cnt = tmp.next, cnt + 1
    
        tmp.change_data(new_data)


    def clear(self):
        self.__init__()
