class Node:
    def __init__(self, data, next=None):
        self.__data = data
        self.next = next

    def get_data(self):
        return self.__data

    def __str__(self):
        return f"data: {self.get_data()}, next: {self.next.get_data() if self.next else None}"


class LinkedList:
    def __init__(self, head = None):
        self.head = head
        self.length = 1 if self.head else 0

    def __len__(self):
        return self.length

    def append(self, element):
        if not self.head:
            self.head = Node(element)
        else:
            cur_el = self.head
            while(cur_el.next != None):
               cur_el = cur_el.next
               
            cur_el.next = Node(element)
        self.length += 1
            
    def __str__(self):
        if not self.head:
            return "LinkedList[]"
        else:
            elements = [self.head]
            for i in range(self.length - 1):
                elements.append(elements[-1].next)
            return f"LinkedList[length = {self.length}, [{'; '.join(map(str, elements))}]]"

    def pop(self):
        if not self.head:
            raise IndexError("LinkedList is empty!")
        
        if not self.head.next:
            self.head = None
            self.length -= 1
        
        else:
            cur_el = self.head
            while(cur_el.next.next != None):
                cur_el = cur_el.next
            cur_el.next = None
            self.length -= 1

    def delete_on_start(self, n):
        if self.length < n or n < 1:
            raise KeyError("Element doesn't exist!")
        
        if n == 1:
            self.head = self.head.next
            self.length -= 1
            return
            
        index = 1
        cur_el = self.head
        while(cur_el.next and index <= n):
            if n == index + 1:
                cur_el.next = cur_el.next.next
                self.length -= 1
                break
            cur_el = cur_el.next
            index += 1
        

    def clear(self):
        self.head = None
        self.length = 0