class Node:
    def __init__(self, data, next=None):
        self.data = data 
        self.next = next

    def get_data(self):
        return self.data
        
    def change_data(self, new_data):
        self.data = new_data

    def __str__(self):
        return f"data: {self.get_data()}, next: {self.next.get_data() if self.next else None}"  


class LinkedList:
    def __init__(self, head = None):
        self.head= Node(head)
        self.length = 1 if head else 0

    def __len__(self):
        return self.length

    def append(self, element):
        if self.length == 0:
            self.head = Node(element)
            self.length += 1
            return
        tmp = self.head
        while(tmp.next):
            tmp = tmp.next
        tmp.next = Node(element)
        self.length += 1

    def __str__(self):
        if self.length == 0:
            return 'LinkedList[]'
        else:
            res = f'LinkedList[length = {self.length}, ['
            tmp = self.head
            while tmp:
                res +=str(tmp) + '; '
                tmp = tmp.next
            res = res[:-2]
            res += ']]'
            return res

    def pop(self):
        tmp = self.head
        if self.length == 0:
            raise (IndexError("LinkedList is empty!"))
        elif self.length == 1:
            res = tmp
            tmp = None
            self.length = 0
            return res
        else:
            while(tmp.next.next):
                tmp = tmp.next
            res = tmp.next
            tmp.next = None
            self.length -= 1

    def change_on_end(self, n, new_data):
        if self.length < n:
            raise(KeyError("Element doesn't exist!"))
        if n <= 0:
            raise(ValueError('Negative number'))
        flag = 0
        tmp = self.head
        while flag != self.length - n:
            tmp = tmp.next
            flag += 1
        tmp.change_data(new_data)

    def clear(self):
        while self.length != 0:
            self.pop()