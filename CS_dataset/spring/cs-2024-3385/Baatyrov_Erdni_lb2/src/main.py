class Node:
    def __init__(self, data, next=None):
        self.data = data
        self.next = next

    def get_data(self):
        return self.data

    def __str__(self):
        if self.next is None:
            return "data: {}, next: None".format(self.data)
        else:
            return "data: {}, next: {}".format(self.data, self.next.data)


class LinkedList:
    def __init__(self, head=None):
        if head :
            self.head = Node(head)
            self.length = 1
        else :
            self.head = head
            self.length = 0

    def __len__(self):
        return self.length

    def append(self, element):
        temp = self.head
        
        if temp :
            while temp.next is not None :
                temp = temp.next
    
            newNode = Node(element)
            temp.next = newNode
        else :
            self.head = Node(element)
        
        self.length += 1
            
    def __str__(self):
        result = "LinkedList["
        
        if self.head :
            temp = self.head
            
            result += "length = " + str(self.length) + ", ["
        
            while temp.next != None :
                result += str(temp) + "; "
                temp = temp.next
                
            result += str(temp) + "]"
                
        result += "]"
        return result
        
    def delete_on_end(self, n):
        if n > self.length or n < 1:
            raise KeyError("Element doesn't exist!")
        
        n = self.length - n + 1
        if n == 1:
            self.head = self.head.next
            self.length -= 1
            return
        
        cur = self.head
        
        for i in range(n-2):
            cur = cur.next
            
        cur.next = cur.next.next
        self.length -= 1
            
    def pop(self):
        if self.length == 0:
            raise IndexError("LinkedList is empty!")
        self.delete_on_end(1)

    def clear(self):
        self.head = None
        self.length = 0
