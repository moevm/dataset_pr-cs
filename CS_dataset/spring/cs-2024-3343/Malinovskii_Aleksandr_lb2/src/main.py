class Node:
    def __init__(self, data, next = None):
        self.__data = data
        self.next = next

    def get_data(self):
        return self.__data

    def change_data(self, new_data):
        self.__data = new_data

    def __str__(self):
        return f'data: {self.__data}, next: {None if self.next is None else self.next.get_data()}'

class LinkedList():

    def __init__(self, head=None):
        if(head):
            self.head=Node(head)
            self.length=1
        else:
            self.head=None
            self.length=0
    def __len__(self):
        return self.length
    def append(self, element):
        tmp = Node(element)
        if self.length == 0:
            self.head = tmp
            self.length = 1
            return
        curr = self.head
        while curr.next :
            curr = curr.next
        curr.next = tmp
        self.length += 1

    def __str__(self):
        pt = self.head
        if self.head is None:
            return 'LinkedList[]'

        else:
            value = []
            while pt != None:
                value.append(pt.__str__())
                pt = pt.next
            return f'LinkedList[length = {len(self)}, [{"; ".join(value)}]]'

    def pop(self):
        if len(self)==0:
            raise IndexError("LinkedList is empty!")
        elif len(self)==1:
            self.length=0
            self.head=None
            return self
        else:
            tmp=self.head
            while(tmp.next.next):
                tmp=tmp.next
            tmp.next=None
            self.length-=1


    def change_on_start(self, n, new_data):
        if len(self)<n or n<=0:
            raise KeyError("Element doesn't exist!")
        temp=self.head
        curr=Node(new_data)
        prev=temp
        if n==1:
           curr.next=self.head.next
           self.head=curr
        else:
            i=1
            while(i<n):
                prev=temp
                temp=temp.next
                i+=1
            prev.next = curr
            curr.next=temp.next


    def clear(self):
        self.head=None
        self.length=0



