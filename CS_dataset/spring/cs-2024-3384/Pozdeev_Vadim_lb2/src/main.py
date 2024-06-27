class Node:
    def __init__(self, data, next=None):
        self._data = data
        self.next = next

    def get_data(self):
        return self._data

    def __str__(self):
        pData = self.next
        if(isinstance(self.next, Node)):
            pData = self.next.get_data()
        return f"data: {self._data}, next: {pData}"


class LinkedList(Node):
    def __init__(self, head=None):
        self.head = head

    def __len__(self):
        if self.head == None:
            return 0
        length = 1
        tempNode = self.head
        while tempNode.next != None:
            tempNode = tempNode.next
            length += 1
        return length

    def append(self, element):
        if self.head == None:
            self.head = Node(element)
        else:
            tempNode = self.head
            while tempNode.next != None:
                tempNode = tempNode.next
            tempNode.next = Node(element)
    
    def __str__(self):
        if len(self) == 0:
            return "LinkedList[]"
        tempNode = self.head
        pData = []
        while tempNode.next != None:
            pData.append(f"data: {tempNode._data}, next: {tempNode.next.get_data()}")
            tempNode = tempNode.next
        pData.append(f"data: {tempNode._data}, next: {tempNode.next}")
        return f"LinkedList[length = {len(self)}, [{'; '.join(pData)}]]"
    

    def pop(self):
        if len(self) == 0:
            raise IndexError("LinkedList is empty!")
        tempNode = self.head
        if tempNode.next == None:
            self.head = None
            return
        while tempNode.next.next != None:
            tempNode = tempNode.next
        tempNode.next = None

    def delete_on_end(self, n):
        if len(self) - n < 0 or n <= 0:
            raise KeyError("Element doesn't exist!")
        index = len(self) - n
        k = 1
        if index == 0:
            self.head = self.head.next
            return
        tempNode = self.head
        while k < index:
            tempNode = tempNode.next
            k += 1
        if tempNode.next.next == None:
            tempNode.next = None
        else:
            tempTempNode = tempNode.next.next
            tempNode.next = tempTempNode

    def clear(self):
        self.head = None
