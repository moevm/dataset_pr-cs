class Node:
    def __init__(self, data, next=None):
        self.__data = data
        self.next = next

    def get_data(self):
        return self.__data

    def __str__(self):
        return f'data: {self.__data}, next: {self.next and self.next.__data}'


class LinkedList:
    def __init__(self, head=None):
        self.head = head
        self.length = 0
        if head is not None:
            self.length += 1

    def __len__(self):
        return self.length

    def append(self, element):
        node = Node(element, None)
        if len(self) == 0:
            self.head = node
        else:
            everyNode = self.head
            while everyNode.next:
                everyNode = everyNode.next
            everyNode.next = node
        self.length += 1

    def __str__(self):
        if self.length == 0:
            return f"LinkedList[]"
        else:
            returningValue = []
            currentNode = self.head
            while currentNode:
                returningValue.append(str(currentNode))
                currentNode = currentNode.next
            returningStr = "; ".join(returningValue)
            return f"LinkedList[length = {self.length}, [{returningStr}]]"

    def pop(self):
        if self.length == 0:
            raise IndexError("LinkedList is empty!")
        else:
            currentNode = self.head
            beforeCurrentNode = currentNode
            while currentNode.next:
                beforeCurrentNode = currentNode
                currentNode = currentNode.next
            beforeCurrentNode.next = None
        self.length -= 1

    def delete_on_start(self, n):
        if self.length < n or n <= 0:
            raise KeyError("Element doesn't exist!")
        else:
            currentNode = self.head
            previousNode = currentNode
            for i in range(n - 1):
                previousNode = currentNode
                currentNode = currentNode.next
            if n == 1 and self.head.next is not None:
                self.head = self.head.next
            previousNode.next = currentNode.next
            self.length -= 1

    def clear(self):
        self.length = 0
        self.head = None
