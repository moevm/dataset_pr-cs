class Node:
    def __init__(self, data, next=None):
        self.__data = data
        self.next = next

    def get_data(self):
        return self.__data

    def __str__(self):
        return f"data: {self.get_data()}, next: {None if self.next is None else self.next.get_data()}"


class LinkedList:
    def __init__(self, head:Node = None):
        self.head = head


    def __len__(self):
        iterator = self.head
        len = 0
        if iterator is None:
            return 0
        while iterator is not None:
            len+=1
            iterator = iterator.next
        return len

    def append(self, element):
        iter = self.head
        if iter is None:
            self.head = Node(element, None)
        else:
            while iter.next is not None:
                iter = iter.next
            iter.next = Node(element,None)

    def __str__(self):
        if self.head is None:
            return "LinkedList[]"
        else:
            li = []
            iterator = self.head
            while iterator is not None:
                li.append(str(iterator))
                iterator = iterator.next
            strd = '; '.join(li)
            return f"LinkedList[length = {len(self)}, [{strd}]]"

    def pop(self):
        if self.head is None:
            raise KeyError("LinkedList is empty!")
        else:
            iter = self.head
            if len(self)  > 1:
                for _ in range(len(self) - 1-1):
                    iter = iter.next
                iter.next = None
            else:
                self.head = None
        pass

    def delete_on_start(self, n):
        index = n-1
        if len(self)-1 < index or index < 0:
            raise KeyError("Element doesn't exist!")
        iterator = self.head
        for _ in range(index-1):
            iterator = iterator.next


        if index == 0:
            self.head = self.head.next
        if len(self)-1 == index:
            iterator.next = None
        else:
            iterator.next = iterator.next.next


    def clear(self):
        self.head = None
        pass