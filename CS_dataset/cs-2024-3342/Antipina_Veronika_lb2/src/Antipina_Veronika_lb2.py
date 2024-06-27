class Node:
    def __init__(self, data, next=None):
        self.__data = data
        self.next = next

    def get_data(self):
        return self.__data

    def __str__(self):
        super().__str__()
        if(self.next!=None):
            return "data: {}, next: {}".format(self.__data,self.next.__data)
        else:
            return "data: {}, next: {}".format(self.__data,self.next)


class LinkedList:
    def __init__(self, head=None):
        self.head = head

    def __len__(self):
        if(self.head==None):
            return 0
        count = 1
        elem = self.head
        while(elem.next!=None):
            count+=1
            elem = elem.next
        return count

    def append(self, element):
        new_elem = Node(element)
        if(self.head==None):
            self.head = new_elem
        else:
            elem = self.head
            while(elem.next!=None):
                elem = elem.next
            elem.next = new_elem

    def __str__(self):
        if(self.head == None):
            return "LinkedList[]"
        else:
            result = "LinkedList[length = {}, [".format(len(self))
            elem = self.head
            
            while(elem.next!=None):
                result+=str(elem)+'; '
                elem = elem.next
            
            result+=str(elem)
        return result+']]'

    def pop(self):
        if(self.head==None):
            raise IndexError("LinkedList is empty!")
        else:
            if(len(self)==1):
                self.head=None
                return
            elem = self.head
            if(len(self)!=1):
                while(elem.next.next!=None):
                    elem = elem.next
            elem.next = None


    def delete_on_end(self, n):
        if(n>len(self) or n<=0):
            raise KeyError("Element doesn't exist!")
        else:
            length = len(self)
            idx = length - n
            counter = 0
            elem = self.head
            if(idx==0):
                self.head = self.head.next
            
            while(elem.next!=None):
                if(counter+1==idx):
                    elem.next = elem.next.next
                if(elem.next!=None):
                    elem = elem.next
                    counter+=1

    def clear(self):
        elem = self.head
        if(elem!=None):
            while(elem.next!=None):
                elem.date = None
                next_el = elem.next
                elem.next = None
                elem = next_el
            self.head = None
