class Node:
    def __init__(self, data, next=None):
        self.data = data
        self.next = next

    def get_data(self):
        return self.data
        
    def change_data(self, new_data):
        self.data = new_data

    def __str__(self):
        return f"data: {self.get_data()}, next: {self.next.get_data() if self.next else None}"


class LinkedList:
    def __init__(self, head = None):
        self.length = 0
        self.head = head
        
        temp = self.head
        while temp:
            temp = temp.next
            self.length += 1

    def __len__(self):
        return self.length

    def append(self, element):
        self.length += 1
        if self.head:
            temp = self.head
            while temp.next:
                temp = temp.next
            temp.next = Node(element)
        else:
            self.head = Node(element)
  
    def __str__(self):
        if self.head:
            LinkedList = f"LinkedList[length = {self.length}, ["
            temp = self.head
            while temp:
                LinkedList += f"data: {temp.get_data()}, next: {temp.next.get_data() if temp.next else None}"
                if temp.next:
                    LinkedList += "; "
                temp = temp.next
            LinkedList += "]]"
            return LinkedList
        else:
            return "LinkedList[]"

    def pop(self):
        if self.head:
            self.length -= 1
            if self.head.next:
                temp = self.head
                while temp.next.next:
                    temp = temp.next
                temp.next = None
            else:
                self.head = None
        else:
            raise IndexError("LinkedList is empty!")

    def change_on_end(self, n, new_data):
        if 0 < n <= self.length:
            count = 0
            temp = self.head
            while count != self.length - n and temp.next:
                temp = temp.next
                count += 1
            temp.change_data(new_data)
        else:
            raise KeyError("Element doesn't exist!")

    def clear(self):
        self.__init__()