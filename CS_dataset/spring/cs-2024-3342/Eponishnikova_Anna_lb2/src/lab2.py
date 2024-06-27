class Node:
    def __init__(self, data, next=None):
        self.data = data
        self.next = next

    def get_data(self):
        return self.data

    def __str__(self):
        if self.next:
            return f"data: {self.data}, next: {self.next.data}"
        else:
            return f"data: {self.data}, next: {None}"


class LinkedList:
    def __init__(self, head=None):
        self.head = head
        if head is None:
            self.length = 0
        else:
            self.length = 1

    def __len__(self):
        return self.length

    def append(self, element):
        new_element = Node(element)
        if self.length == 0:
            self.head = new_element
        else:
            tmp = self.head
            while tmp.next is not None:
                tmp = tmp.next
            tmp.next = new_element
        self.length += 1


    def __str__(self):
        if self.length == 0:
            return f"LinkedList[]"
        tmp = self.head
        arr = []
        while tmp.next is not None:
            arr.append(str(tmp))
            tmp = tmp.next
        arr.append(str(tmp))
        return f'LinkedList[length = {self.length}, [{"; ".join(arr)}]]'


    def pop(self):
        if self.length == 0:
            raise IndexError("LinkedList is empty!")
        elif self.length == 1:
            self.length -=1
            self.head = None
        else:
            tmp = self.head
            while tmp.next.next is not None:
                tmp = tmp.next
            tmp.next = None
            self.length -=1


    def delete_on_end(self, n):
        if self.length < n or n <= 0:
            raise KeyError (f"Element doesn't exist!")
        elif self.length == n:
            self.head = self.head.next
        else:
            tmp = self.head 
            i = 2 
            idx = self.length - n + 1
            while i < idx:
                tmp = tmp.next
                i += 1 
            tmp.next = tmp.next.next
            
        self.length -=1



    def clear(self):
        while self.length != 0:
            self.pop()