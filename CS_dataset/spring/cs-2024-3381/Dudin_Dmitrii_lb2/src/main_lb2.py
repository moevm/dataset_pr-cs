class Node:
    def __init__(self, data, next=None):
        if next is not None and not isinstance(next, Node):
            raise TypeError()
        self.__data__ = data
        self.next = next

    def get_data(self):
        return self.__data__

    def __repr__(self):
        return f'Node({self.__data__})'

    def __str__(self):
        next = self.next.get_data() if isinstance(self.next, Node) else self.next
        return f'data: {self.__data__}, next: {next}'

    def __del__(self):
        del self.__data__


class LinkedList:
    def __init__(self, head:Node=None):
        if (head is not None) and not isinstance(head, Node):
            raise ValueError()
        self.head = head
        self.recalc_length()

    def recalc_length(self):
        self.length = len(self)
        return self.length

    def __len__(self):
        i = 0
        np = self.head
        while np is not None:
            i += 1
            np = np.next
        return i

    def append(self, element):
        if self.head is None:
            self.head = Node(element)
            self.length += 1
            return
        np = self.head
        while np.next is not None:
            np = np.next
        np.next = Node(element)
        self.length += 1

    def __str__(self):
        le = len(self)
        if le:
            np = self.head
            datastr = ''
            while np is not None:
                datastr += str(np)
                np = np.next
                if np is not None:
                    datastr += '; '
            return f'LinkedList[length = {le}, [{datastr}]]'
        else:
            return 'LinkedList[]'

    def pop(self):
        le = len(self)
        if le == 0:
            raise IndexError('LinkedList is empty!')
        if le == 1:
            rv = self.head
            self.head = None
            self.length -= 1
            return rv
        np = self.head
        while np.next.next is not None:
            np = np.next
        rv = np.next
        np.next = None
        self.length -= 1
        return rv

    def clear(self):
        self.head = None
        self.length = 0

    def delete_on_start(self, n):
        n -= 1
        if n >= len(self) or n < 0:
            raise KeyError('Element doesn\'t exist!')
        if n == 0:
            self.head = self.head.next
            self.length -= 1
            return
        np = self.head
        for i in range(n-1):
            np = np.next
        np.next = np.next.next
        self.length -= 1