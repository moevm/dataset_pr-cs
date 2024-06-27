class Node:
    def __init__(self, data, next=None):
        self.data = data
        self.next = next
        pass

    def get_data(self):
        return self.data

    def __str__(self):
        return 'data: ' + str(self.data) + ', next: ' + (str(self.next.data) if self.next != None else 'None')


class LinkedList:
    def __init__(self, head = None):
        if head == None:
            self.head = None
        else:
            self.head = head

    def __len__(self):
        if self.head == None:
            return 0
        else:
            count = 1
            current = self.head
            while current.next != None:
                count += 1
                current = current.next
            return count

    def append(self, element):
        el = Node(element)
        if len(self) == 0:
            self.head = el
            return None
        current = self.head
        while current.next != None:
            current = current.next
        current.next = el

    def __str__(self):
        res = 'LinkedList'
        res1 = ''
        if len(self) == 0:
            return 'LinkedList[]'
        current = self.head
        while current.next != None:
            res1 += str(current) + '; '
            current = current.next
        res1 += str(current)
        return res + '[length = ' + str(len(self)) + ', [' +  res1 + ']]'

    def pop(self):
        if len(self) == 0:
            return
        if len(self) == 1:
            self.head = None
            return
        current = self.head
        while current.next.next != None:
            current = current.next
        current.next = None

    def delete_on_start(self, n):
        if len(self) < n or n <= 0:
            raise KeyError("Element doesn't exist!")
        else:
            if n == 1:
                self.head = self.head.next
                return
            current = self.head
            c = 1
            while (c + 1) != n:
                current = current.next
                c += 1
            current.next = current.next.next

    def clear(self):
        self.head = None
