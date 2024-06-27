class Node:

    def __init__(self, data, next=None):
        self.data=data
        self.next=next

    def get_data(self):
        return self.data

    def __str__(self):
        if self.next is not None:
            return f'data: {self.data}, next: {self.next.data}'
        else:
            return f'data: {self.data}, next: {self.next}'


class LinkedList:
    def __init__(self, head = None):
        self.head=None
        self.length=0
        if head is not None:
            self.length=1

    def __len__(self):
        return self.length
    

    def append(self, element):
        nt=Node(element)
        if self.length==0:
            self.head=nt
            self.length=1
            return
        curr=self.head
        while curr.next is not None:
            curr=curr.next
        curr.next=nt
        self.length+=1

            
    def __str__(self):
        arr = []
        curr = self.head
        if self.length == 0:
            return "LinkedList[]"
        arr.append(f"data: {curr.get_data()}, next: {None if curr.next is None else curr.next.get_data()}")
        while curr.next is not None:
            curr = curr.next
            arr.append(f"data: {curr.get_data()}, next: {None if curr.next is None else curr.next.get_data()}")
        return f"LinkedList[length = {self.length}, [{'; '.join(arr)}]]"
    def pop(self):
        if self.length == 0:
            raise IndexError("LinkedList is empty!")
        else:
            curr = self.head
            prev = curr
            while curr.next:
                prev = curr
                curr = curr.next
            prev.next = None
        self.length -= 1

    def delete_on_start(self, n):
        if n > self.length or n <= 0:
            raise KeyError(f"{n} doesn't exist!")
        c = 1
        curr = self.head
        prev = curr
        while c != n:
            prev = curr
            curr = curr.next
            c += 1
        if n == 1 and self.head.next is not None:
            self.head = self.head.next
        prev.next = curr.next
        self.length -= 1

    def clear(self):
        self.head = None
        self.length = 0
