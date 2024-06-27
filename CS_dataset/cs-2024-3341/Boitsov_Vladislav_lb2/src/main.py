class Node:
    def __init__(self, data, next=None):
        self.__data=data
        self.next=next

    def get_data(self):
        return self.__data
        
    def change_data(self, new_data):
        self.__data=new_data

    def __str__(self):
        return f"data: {self.__data}, next: {None if self.next==None else self.next.__data}"


class LinkedList:
    def __init__(self, head = None):
        if head == None:
            self.head=None
            self.length=0 
        else:
            self.head=head
            self.length=1

    def __len__(self):
        return self.length

    def append(self, element):
        new_node = Node(element)
        if self.length==0:
            self.head=Node(element)
            self.length=1
        else:
            tail=self.head
            while(tail.next != None):
                tail=tail.next
            tail.next=new_node
            self.length+=1

            
    def __str__(self):
        if self.length==0:
            return "LinkedList[]"
        else:
            output = f"LinkedList[length = {self.length}, ["
            current=self.head
            while(current!=None):
                output=output+str(current)+"; "
                current=current.next
            output=output[:-2]+"]]"
            return output
            

    def pop(self):
        if self.length==0:
            raise IndexError("LinkedList is empty!")
        else:
            current=self.head
            if self.length == 1:
                self.head=None
            else:
                while(current.next.next!=None):
                    current=current.next
                current.next=None
            self.length-=1
                    

    def change_on_end(self, n, new_data):
        if not(1<=n<=self.length):
            raise KeyError("Element doesn't exist!")
        else:
            element = self.head
            for i in range(self.length-n):
                element=element.next
            element.change_data(new_data)
            

    def clear(self):
        self.head=None
        self.length=0