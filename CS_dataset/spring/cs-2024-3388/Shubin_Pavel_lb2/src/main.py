class Node:
    def __init__(self, data, next=None):
        self.data = data
        self.next = next

    def get_data(self):
        return self.data
        
    def change_data(self, new_data):
        self.data = new_data

    def __str__(self):
        if self.next:
            return "data: " + str(self.data) + ", next: " + str(self.next.data)
        else:
            return "data: " + str(self.data) + ", next: None"


class LinkedList:
    def __init__(self, head=None):
        self.head = head
        self.length = 0
        if head:
            self.length = 1

    def __len__(self):
        return self.length

    def append(self, element):
        new_node = Node(element)
        if not self.head:
            self.head = new_node
        else:
            curr = self.head
            while curr.next:
                curr = curr.next
            curr.next = new_node
        self.length += 1

    def __str__(self):
        if not self.head:
            return "LinkedList[]"
        else:
            result = "LinkedList[length = " + str(self.length) + ", ["
            curr = self.head
            while curr:
                result += "data: " + str(curr.get_data()) + ", next: "
                if curr.next:
                    result += str(curr.next.get_data()) + "; "
                else:
                    result += "None"
                curr = curr.next
            result += "]]"
            return result

    def pop(self):
        if not self.head:
            raise IndexError("Список Пуст!")
        elif self.length == 1:
            self.head = None
            self.length = 0
        else:
            current = self.head
            while current.next.next:
                current = current.next
            current.next = None
            self.length -= 1

    def change_on_end(self, n, new_data):
        if n <= 0 or n > self.length:
            raise KeyError("Элемента не существует!")
        elif n == self.length:
            self.head.data = new_data
        else:
            current = self.head
            for _ in range(self.length - n):
                current = current.next
            current.data = new_data

    def clear(self):
        self.head = None
        self.length = 0
