class Node():
    def __init__(self, data, next=None):
        self.__data = data
        self.next = next

    def get_data(self):
        return self.__data

    def __str__(self):
        return f"data: {self.get_data()}, next: {self.next.get_data() if self.next else None}"

class LinkedList():
    def __init__(self, head=None):
        self.head = head
        if head:
            self.length = 1
        else:
            self.length = 0

    def __len__(self):
        return self.length

    def append(self, element):
        newElement = Node(element)
        boof = self.head
        if boof:
            while boof.next:
                boof = boof.next
            boof.next = newElement
        else:
            self.head = newElement
        self.length += 1

    def __str__(self):
        boof = self.head
        if not boof:
            return "LinkedList[]"
        Arr = []
        while boof:
            Arr.append(boof)
            boof = boof.next
        return f"LinkedList[length = {self.length}, [{'; '.join(map(str, Arr))}]]"

    def pop(self):
        if not self.head:
            raise IndexError("LinkedList is empty!")
        elif not self.head.next:
            self.head = None
            self.length -= 1
        else:
            boof = self.head
            while boof.next.next:
                boof = boof.next
            boof.next = None
            self.length -= 1

    def clear(self):
        self.head = None
        self.length = 0

    def delete_on_start(self, n):
        if self.length < n or n <= 0:
            raise KeyError("Element doesn't exist!")
        elif n == 1:
            self.head = self.head.next
        else:
            boof = self.head
            for _ in range(n-2):
                boof = boof.next
            boof.next = boof.next.next
        self.length -= 1