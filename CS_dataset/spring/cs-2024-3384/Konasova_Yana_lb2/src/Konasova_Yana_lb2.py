class Node:
    def __init__(self, data, next=None):
        self._data=data
        self.next=next

    def get_data(self):
        return self._data

    def change_data(self, new_data):
        self._data=new_data

    def __str__(self):
        if self.next:
            return ('data: '+ str(self.get_data())+ ', next: '+ str(self.next.get_data()))
        return ('data: '+ str(self.get_data())+ ', next: None')



class LinkedList:
    def __init__(self, head=None):
        if head == None:
            self.head = head
            self.length = 0
        else:
            self.head = head
            self.length = 1

    def __len__(self):
        return self.length

    def append(self, element):
        end = Node(element)
        s = self.head
        if s==None:
            self.head=end
            self.length+=1
        else:
            while (s.next):
                s = s.next
            s.next = end
            self.length+=1
    def __str__(self):
        if self.head==None:
            return 'LinkedList[]'
        else:
            string="LinkedList[length = " +str(self.length)+', ['
            buf=self.head
            k=0
            while (buf!=None):
                string+=buf.__str__()
                if k<self.length-1:
                    string+='; '
                k+=1
                buf=buf.next
            string+=']]'
            return  string

    def pop(self):
        if self.length==0:
            raise IndexError("LinkedList is empty!")
        else:
            if self.length==1:
                self.head=None
                self.length =0 
            else:
                buf=self.head
                for i in range(self.length-2):
                    buf=buf.next
                buf.next=None
                self.length-=1

    def change_on_end(self, n, new_data):
        if self.length<n or n<1:
            raise KeyError("Element doesn't exist!")
        else:
            if n==self.length:
                buf=self.head
                buf._data=new_data
            else:
                buf = self.head
                for i in range(self.length-n):
                    buf=buf.next
                buf._data=new_data

    def clear(self):
        self.head=None
        self.length=0
