class Node:
    def __init__(self, data, next=None):
        self.data = data
        self.next = next

    def get_data(self):
        return self.data

    def __str__(self):
        if self.next == None:
            return f"data: {self.data}, next: None"
        else:
            return f"data: {self.data}, next: {self.next.data}"


class LinkedList:
    def __init__(self, head = None):
        self.head = head
        self.length = len(self)

    def __len__(self):
        cnt = 0
        tmp = self.head
        while tmp is not None:
            cnt += 1
            tmp = tmp.next
        return cnt
    
    def append(self, element):
        tmp = self.head
        end = Node(element)
        if len(self) == 0:
            self.head = end
        else:
            while tmp.next is not None:
                tmp = tmp.next
            tmp.next = end

            
    def __str__(self):
        if len(self) == 0:
            return "LinkedList[]"
        else:
            s = f"LinkedList[length = " + str(len(self)) + ", ["
            tmp = self.head
            while tmp.next is not None:
                s += str(tmp) + "; "
                tmp = tmp.next
            s += str(tmp)
            return s + "]]"

    def pop(self):
        if self.head is None:
            raise IndexError("LinkedList is empty!")
        elif len(self) == 1:
            self.head = None
        else:
            tmp = self.head
            while tmp.next.next is not None:
                tmp = tmp.next
            tmp.next = None

    def delete_on_start(self, n):
        if n > len(self) or n <= 0:
            raise KeyError("Element doesn't exist!")
        elif n == len(self):
            self.pop()
        elif n == 1:
            self.head = self.head.next
        else:
            tmp = self.head
            for i in range(n - 2):
                tmp = tmp.next
            tmp.next = tmp.next.next

    def clear(self):
        self.head = None