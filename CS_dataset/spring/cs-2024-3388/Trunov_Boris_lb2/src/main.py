class Node:
    def __init__(self, data, next=None):
        self.__data = data
        self.next = next

    def get_data(self):
        return self.__data

    def __str__(self):
        return f'data: {self.__data}, next: {self.next.__data if self.next else None}'

class LinkedList:
    __str_template = "LinkedList[{content}]"
    __content_template = "length = {length}, [{nodes}]"

    def __init__(self, head=None):
        if head is not None:
            self.head = Node(head)
            self.length = 1
        else:
            self.head = head
            self.length = 0

    def __len__(self):
        counter = 0
        tmp = self.head
        while tmp is not None:
            counter += 1
            tmp = tmp.next
        return counter

    def append(self, element):
        if self.head is None:
            self.head = Node(element)
        else:
            tmp = self.head
            while tmp.next is not None:
                tmp = tmp.next

            tmp.next = Node(element)

        self.length += 1

    def __str__(self):
        if self.length == 0:
            return self.__str_template.format(content='')

        nodes = ''
        tmp = self.head
        for i in range(self.length):
            nodes += f'{tmp.__str__()}; '
            tmp = tmp.next

        return self.__str_template.format(content=self.__content_template.format(length=self.length, nodes=nodes[:-2]))

    def pop(self):
        if self.length == 0:
            raise IndexError("LinkedList is empty!")
        if self.length == 1:
            self.head = None
        else:
            tmp = self.head
            while tmp.next.next is not None:
                tmp = tmp.next
            tmp.next = None
        self.length -= 1

    def delete_on_end(self, n):
        if self.length < n or n <= 0:
            raise KeyError("Element doesn't exist!")
        if self.length == n:
            self.head = self.head.next
        else:
            tmp = self.head
            Prevtmp = None
            for i in range(self.length - n):
                Prevtmp = tmp
                tmp = tmp.next
            Prevtmp.next = tmp.next
        self.length -= 1

    def clear(self):
        self.head = 0
        self.length = 0
