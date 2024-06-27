class Node:
    def __init__(self, data, next=None):
        self.__data=data
        self.next=next

    def get_data(self):
        return self.__data
        
    def change_data(self, new_data):
        self.__data=new_data

    def __str__(self):
        if self.next==None:
            return f"data: {self.__data}, next: None"
        return f"data: {self.__data}, next: {self.next.__data}"

class LinkedList:

    def __init__(self, head = None):
        self.__head__=head
        self.__length=0
        while head:
            self.__length+=1
            head=head.next

    def __len__(self):
        return self.__length

    def append(self, element):
        a=Node(element,None)
        self.__length+=1
        if self.__head__==None:
            self.__head__=a
            return
        tek=self.__head__
        while (tek.next!=None): tek=tek.next
        tek.next=a
            
    def __str__(self):
        if self.__length==0:
            return "LinkedList[]"
        tek=self.__head__
        s=[]
        for i in range(self.__length):
            s+=[tek.__str__()]
            tek=tek.next
        return f"LinkedList[length = {self.__length}, ["+'; '.join(s)+"]]"

    def pop(self):
        if self.__length==0:
            raise IndexError("LinkedList is empty!")
        elif self.__length==1:
            self.__head__=None
        else:
            tek=self.__head__
            while(tek.next.next!=None):
                tek=tek.next
            tek.next=None
        self.__length-=1

    def change_on_end(self, n, new_data):
        if self.__length<n or n<=0:
            raise KeyError("Element doesn't exist!")
        k=self.__length-n
        tek=self.__head__
        while(k!=0):
            tek=tek.next
            k-=1
        tek.change_data(new_data)

    def clear(self):
        self.__head__=None
        self.__length=0
