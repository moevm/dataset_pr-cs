class Node:
    def __init__(self, data, next=None):
        self.__data = data
        self.next = next

    def get_data(self):
        return self.__data

    def change_data(self, new_data):
        self.__data = new_data

    def __str__(self):
        next_data = self.next.get_data() if self.next else None
        return f"data: {self.__data}, next: {next_data}"

        

class LinkedList:
    def __init__(self, head=None):
        self.__head__ = head
        elem = self.__head__
        i = 0
        while elem:
            i+=1
            elem = elem.next
        self.__length = i

    def __len__(self):
        return self.__length

    def append(self, element):
        self.__length += 1
        new_el = Node(element)
        head = self.__head__
        if head:
            while head.next:
                head = head.next
            head.next = new_el
        else: self.__head__ = new_el

    def __str__(self):
        if self.__length == 0:
            return 'LinkedList[]'
        head = self.__head__
        arr = []
        while head.next:
            arr.append(str(head))
            head = head.next
        arr.append(str(head))
        return f'LinkedList[length = {self.__length}, [{"; ".join(arr)}]]'

    def pop(self):
        if self.__length == 1:
            self.__length -= 1
            self.__head__ = None
        elif self.__length:
            head = self.__head__
            while head.next.next:
                head = head.next
            head.next = None
            self.__length -= 1
        else: raise IndexError("LinkedList is empty!")

    def change_on_end(self, n, new_data):
        if n>self.__length or n<=0: raise KeyError(f"{n} doesn't exist!")
        else:
            i = 0
            head = self.__head__
            while i < self.__length-n:
                head = head.next
                i += 1
            head.change_data(new_data)



    def clear(self):
        while self.__length:
            self.pop()




	
