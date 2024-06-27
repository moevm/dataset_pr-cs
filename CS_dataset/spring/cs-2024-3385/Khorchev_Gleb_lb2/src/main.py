class Node:
    __data = 0
    next = None
    def __init__(self, data, next=None):
        self.__data = data
        self.next = next

    def get_data(self):
        return self.__data

    def change_data(self, new_data):
        self.__data = new_data

    def __str__(self):
        return f"data: {self.get_data()}, next: {self.next.get_data() if self.next else None}"


class LinkedList:
    head = None
    lenght = 0

    def __init__(self, head=None):
        self.head= Node(head)
        self.lenght = 1 if head else 0

    def __len__(self):
        return self.lenght

    def append(self, element):
        if (self.lenght == 0):
            self.head = Node(element)
            self.lenght += 1
            return
        tmp = self.head
        while(tmp.next):
            tmp = tmp.next
        tmp.next = Node(element)
        self.lenght += 1
            

    def __str__(self):
        if self.lenght == 0:
            return 'LinkedList[]'
        else:
            res = f'LinkedList[length = {self.lenght}, ['
            tmp = self.head
            while tmp:
                res += str(tmp) + '; '
                tmp = tmp.next
            res = res[:-2]
            res += ']]'
        return res

    def pop(self):
        if self.lenght == 0:
            raise IndexError("LinkedList is empty!")
        else:
            if self.lenght == 1:
                tmp = self.head
                self.head = None
                self.lenght = 0
                return tmp
            elif self.lenght != 1:
                tmp = self.head
                while(tmp.next.next):
                    tmp = tmp.next
                res = tmp.next
                tmp.next = None
                self.lenght -= 1
                return res


    def change_on_end(self, n, new_data):
        if n > self.lenght:
            raise KeyError("Element doesn't exist!")
        if n <= 0:
            raise  KeyError("Negative number cant be an index")
        tmp = self.head
        count = 0
        while count != self.lenght -n:
            tmp = tmp.next
            count += 1
        tmp.change_data(new_data)


    def clear(self):
        while(self.lenght != 0 ):
            self.pop()

