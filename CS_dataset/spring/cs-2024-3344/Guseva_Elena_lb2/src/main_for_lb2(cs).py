class Node:
    def __init__(self, data, next=None):
        self.data, self.next = data, next

    def get_data(self):
        return self.data

    def __str__(self):
        if self.next:
            return (f"data: {self.data}, next: {self.next.data}")
        return (f"data: {self.data}, next: None")

class LinkedList:
    def __init__(self, head=None):
        self.head, self.length = head, 0
        while head:
            head=head.next
            self.length+=1

    def __len__(self):
        return self.length

    def append(self, element):
        self.length += 1
        if self.head:
            tmp = self.head
            while tmp.next:
                tmp = tmp.next
            tmp.next = Node(element)
        else:
            self.head = Node(element)

    def __str__(self):
        if self.head is not None:
            res = f'LinkedList[length = {self.length}, ['
            tmp = self.head
            while tmp:
                res += str(tmp) + '; '
                tmp = tmp.next
            res = res[:-2] + ']]'
            return res
        else:
            return 'LinkedList[]'

    def pop(self):
        if not self.head:
            raise IndexError("LinkedList is empty!")

        if self.length == 1:
            self.__init__()
        if self.head:
            tmp=self.head
            while tmp.next.next:
                tmp=tmp.next
            tmp.next=None
            self.length-=1

    def clear(self):
        self.__init__()

    def delete_on_end(self, n):
        if self.length < n or n <= 0:
            raise KeyError("Element doesn't exist!")
        else:
            index = self.length - n
            tmp = self.head
            if index == 0:
                self.head = tmp.next
            else:
                for i in range(1, index):
                    tmp = tmp.next
                tmp.next = tmp.next.next
            self.length -= 1