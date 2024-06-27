class Node:
    def __init__(self, data, next=None):
        self.__data = data
        self.next = next

    def get_data(self):
        return self.__data

    def change_data(self, new_data):
        self.__data = new_data

    def __str__(self):
        return f'data: {self.__data}, next: {self.next.__data if self.next else None}'


class LinkedList:
    def __init__(self, head=None):
        if head is None:
            self.head = head
            self.length = 0
        else:
            self.head = head
            self.length = 1

    def __len__(self):
        return self.length

    def append(self, element):
        node = Node(element)
        tmp = self.head
        if tmp is None:
            self.head = node
        else:
            while tmp.next:
                tmp = tmp.next
            tmp.next = node
        self.length += 1

    def __str__(self):
        if self.length == 0:
            return 'LinkedList[]'
        else:
            tmp = self.head
            data_list = []
            while tmp:
                data_list.append(tmp.__str__())
                tmp = tmp.next
            return f'LinkedList[length = {self.length}, [' + '; '.join(data_list) + ']]'

    def pop(self):
        if self.length == 0:
            raise IndexError('LinkedList is empty!')
        elif self.length == 1:
            self.head = None
            self.length = 0
        else:
            tmp = self.head
            while tmp.next.next:
                tmp = tmp.next
            tmp.next = None
            self.length -= 1

    def change_on_end(self, n, new_data):
        if not isinstance(n, int):
            raise TypeError(f'{n} is not a number!')
        if self.length < n or n <= 0:
            raise KeyError(f"{n} doesn't exist!")
        else:
            tmp = self.head
            count = 0
            while count < self.length - n:
                tmp = tmp.next
                count += 1
            tmp.change_data(new_data)

    def clear(self):
        self.head = None
        self.length = 0
