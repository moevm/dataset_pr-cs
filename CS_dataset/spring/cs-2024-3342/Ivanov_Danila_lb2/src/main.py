class Node:
    def __init__(self, data, next=None):
        self.__data = data
        self.next = next

    def get_data(self):
        return self.__data

    def __str__(self):
        if self.next != None:
            return f"data: {self.__data}, next: {self.next.get_data()}"
        return f"data: {self.__data}, next: {self.next}"


class LinkedList:
    def __init__(self, head=None):
        if head == None:
            self.lis = []
        else:
            head_lis = Node(head)
            self.lis = [head_lis]

    def __len__(self):
        return len(self.lis)

    def append(self, element):
        el = Node(element)
        if len(self.lis) == 0:
            self.lis.append(el)
        else:
            self.lis[-1].next = el
            self.lis.append(el)

    def __str__(self):
        if len(self.lis) == 0:
            return "LinkedList[]"
        st = f"LinkedList[length = {len(self.lis)}, ["
        for i in self.lis:
            if i.next != None:
                st += f"data: {i.get_data()}, next: {i.next.get_data()}"
                st += '; '
            else:
                st += f"data: {i.get_data()}, next: {i.next}"
        st += ']]'
        return st

    def pop(self):
        if len(self.lis) == 0:
            raise IndexError("LinkedList is empty!")
        elif len(self.lis) == 1:
            el = self.lis[0].get_data()
            self.lis = []
            return el
        el = self.lis[-1].get_data()
        self.lis[-2].next = None
        self.lis.pop(len(self.lis) - 1)
        return el

    def delete_on_start(self, n):
        if len(self.lis) < n or n <= 0:
            raise KeyError("Element doesn't exist!")
        elif len(self.lis) == n:
            if n > 1:
                self.lis[n - 2].next = None
        else:
            if n > 1:
                self.lis[n - 2].next = self.lis[n]
        self.lis.pop(n - 1)

    def clear(self):
        self.lis = []
