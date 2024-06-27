class Node:
    def __init__(self, data, next=None):
        self.data = data
        self.next = next
        pass

    def get_data(self):
        return self.data
        pass

    def __str__(self):
        return f"data: {self.data}, next: {None if self.next==None else self.next.get_data()}"
        pass


class LinkedList:
    def __init__(self, head=None):
        if head == None:
            self.head = None
            self.length = 0
        else:
            self.head = head
            self.length = 1
        pass

    def __len__(self):
        return self.length
        pass

    def append(self, element):
        new = Node(element)
        if self.head == None:
            self.head = new
            new.next = None
        else:
            prom = self.head
            while prom.next!=None:
                prom = prom.next
            prom.next = new
            new.next = None
        self.length += 1

        pass

    def __str__(self):
        if self.head == None:
            return "LinkedList[]"
        else:
            result = "LinkedList[length = {}, [".format(self.length)
            current = self.head
            while current is not None:
                result += "data: {}, next: {}; ".format(current.get_data(), current.next.get_data() if current.next is not None else "None")
                current = current.next
            result = result[:-2]  # Remove the extra "; "
            result += "]]"
            return result
            
        pass

    def pop(self):
        if self.head == None:
            raise IndexError("LinkedList is empty!")
        elif(self.head.next==None):
            self.head = None
            self.length = 0
        else:
            prom = self.head
            while prom.next.next!=None:
                prom = prom.next
            prom.next = None
            self.length -= 1
            
        pass

    def delete_on_end(self, n):
        if self.length<n or n<=0:
            raise KeyError("Element doesn't exist!")
        else:
            g = self.length - n
            prom = self.head
            i=1
            if g==0:
                self.head = prom.next
            else:
                while(i!=g):
                    prom = prom.next
                    i+=1
                prom.next = prom.next.next
            self.length -= 1
        pass

    def clear(self):
        self.head = None
        self.lenght = 0
        pass
