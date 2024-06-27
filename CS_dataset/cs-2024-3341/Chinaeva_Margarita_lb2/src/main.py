class Node:
    def __init__(self, data, next=None):
        self.__data = data
        self.next = next

    def get_data(self):
        return self.__data

    def __str__(self):
        return f"data: {self.__data}, next: {None if self.next==None else self.next.__data}"


class LinkedList:
    def __init__(self, head = None):
        if head == None:
            self.head = None
            self.length=0
        else:
            self.head = head
            self.length = 1

    def __len__(self):
        return self.length

    def append(self, element):
        new_node = Node(element)
        if self.length == 0:
            self.head = new_node
            self.length = 1
        else: 
            present = self.head
            while(present.next != None):
                present = present.next
            present.next = new_node
            self.length += 1
            
    def __str__(self):
        if self.length == 0:
            return "LinkedList[]"
        else:
            str_list = f"LinkedList[length = {self.length}, ["
            present = self.head
            while(present.next!=None):
                str_list += str(present)
                str_list += '; '
                present = present.next
            str_list += str(present) + ']]'
            return str_list

    def pop(self):
        if self.length == 0:
            raise IndexError("LinkedList is empty!")
        elif self.length == 1:
            self.head = None
            self.length = 0
        else: 
            present = self.head
            while (present.next.next != None):
                present = present.next
            present.next = None
            self.length -= 1

    def delete_on_start(self, n):
        if n < 1 or n > self.length:
            raise KeyError("Element doesn't exist!")
        elif n == 1:
            present = self.head
            self.head = present.next
            self.length -= 1
        else:
            present = self.head
            present_index = 1
            while (n != present_index+1):
                present = present.next
                present_index += 1
            present.next = present.next.next
            self.length -= 1

    def clear(self):
        self.head = None
        self.length = 0
