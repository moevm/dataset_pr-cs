class Node:
    def __init__(self,data,next=None) -> None:
        self.data = data
        self.next = next
    
    def get_data(self):
        return self.data
    
    def __str__(self) -> str:
        return f'data: {self.data}, next: {self.next.data if self.next!=None else None}'
    
class LinkedList:
    def __init__(self, head = None):
        self.length = 0
        self.head = None
        if not(head == None):
            self.head = Node(head)
            self.length+=1

    def __len__(self):
        return self.length

    def append(self, element):
        if self.length==0:
            self.head = Node(element)
        else:
            a = self.head
            while(not(a.next==None)):
                a = a.next
            a.next = Node(element)
        self.length+=1

    def __str__(self):
        if self.length==0:
            return 'LinkedList[]'
        else:
            r = f'LinkedList[length = {self.length}, ['
            a = self.head
            while(not(a.next==None)):
                r+=str(a)+'; '
                a = a.next
            r+=str(a)
            r+=']]'
            return r

    def pop(self):
        if self.length==0:
            raise IndexError('LinkedList is empty!')
        if self.length==1:
            self.head = None
        else:
            a = self.head
            a1 = None
            while(not(a.next==None)):
                a1 = a
                a = a.next
            a1.next=None
        self.length-=1

    def delete_on_start(self, n):
        if n > self.length or n<1:
            raise KeyError('Element doesn\'t exist!')
        if(n==1):
            self.head = self.head.next
        else:
            a = self.head
            for i in range(n-2):
                a = a.next
            a.next = a.next.next
        self.length-=1

    def clear(self):
        self.head=None
        self.length = 0
