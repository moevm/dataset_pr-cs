class Node:
    def __init__(self, data, next_node = None):
        self.__data = data
        self.next = next_node

    def get_data(self):
        return self.__data
        
    def change_data(self, new_data):
        self.__data = new_data

    def __str__(self):
        if (self.next is not None):
            return f"data: {self.__data}, next: {self.next.__data}"
        else:
            return f"data: {self.__data}, next: None"
class LinkedList:
    def __init__(self, head = None):
        self.head = head
        self.__length = 0 if head is None else 1

    def __len__(self):
        return self.__length

    def append(self, element):
        self.__length += 1
        new_node = Node(element)
        if (self.head is None):
            self.head = new_node
        else:
            curr_node = self.head
            while (curr_node.next):
                curr_node = curr_node.next
            curr_node.next = new_node
            
    def __str__(self):
        if self.__length == 0:
            return "LinkedList[]"
        else:
            s = f"LinkedList[length = {self.__length}, ["
            curr_node = self.head
            while (curr_node):
                s += curr_node.__str__()
                curr_node = curr_node.next
                if curr_node is not None:
                    s += "; "
            s += "]]"
            return s

    def pop(self):
        if (self.__length == 0):
            raise IndexError("LinkedList doesn't exist!")
        elif (self.__length == 1):
            self.__length -= 1
            self.head = None
        else:
            curr_node = self.head
            for i in range(self.__length):
                if (i == self.__length - 2):
                    curr_node.next = None
                    self.__length -= 1
                    break
                curr_node = curr_node.next

    def change_on_start(self, n, new_data):
        if (n > self.__length or n <= 0):
            raise KeyError("Element doesn't exist!")

        counter = 1
        curr_node = self.head
        while (curr_node):
            if (counter == n):
                curr_node.change_data(new_data)
                break
            curr_node = curr_node.next
            counter += 1

    def clear(self):
        self.__length = 0
        self.head = None
