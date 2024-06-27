class Node:
    def __init__(self, data, next=None):
        self.__data = data
        if isinstance(next, Node) or next is None:
            self.next = next
        else:
            raise TypeError(f"type of {next} should be Node or its subclass, not {type(next)}")

    def get_data(self):
        return self.__data

    def change_data(self, new_data):
        self.__data = new_data

    def __str__(self):
        if (self.next is None):
            next_str = None
        else:
            next_str = self.next.get_data()
        return f"data: {self.__data}, next: {next_str}"


class LinkedList:
    def __init__(self, head=None):
        self.head = head
        if head is None:
            self.length = 0
        else:
            self.length = 1

    def __len__(self):
        len_count = 0
        node_tmp = self.head
        while node_tmp:
            node_tmp = node_tmp.next
            len_count+=1
        return len_count

    def append(self, element):
        self.length += 1
        if self.head is None:
            self.head = Node(element)
            return
        node_tmp = self.head
        while node_tmp.next != None:
            node_tmp = node_tmp.next
        node_tmp.next = Node(element)

    def __str__(self):
        if self.length == 0:
            return "LinkedList[]"
        node_data = []
        node_tmp = self.head
        while node_tmp is not None:
            node_data.append(str(node_tmp))
            node_tmp = node_tmp.next
        string_arr = f"LinkedList[length = {self.length}, [{'; '.join(node_data)}]]"
        return string_arr

    def pop(self):
        if self.length == 0:
            raise IndexError("LinkedList is empty!")
        if self.length == 1:
            self.head = None
        else:
            node_tmp = self.head
            while node_tmp.next.next:
                node_tmp = node_tmp.next
            node_tmp.next = None
        self.length -= 1

    def change_on_start(self, n, new_data):
        if n > self.length or n <= 0:
            raise KeyError("Element doesn't exist!")
        node_tmp = self.head
        count = 1
        while count < n:
            node_tmp = node_tmp.next
            count += 1
        node_tmp.change_data(new_data)

    def clear(self):
        self.head = None
        self.length = 0
