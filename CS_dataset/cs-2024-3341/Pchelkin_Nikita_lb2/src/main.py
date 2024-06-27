class Node:
    def __init__(self, data, next=None):
        self.__data = data
        self.next = next

    def get_data(self):
        return self.__data

    def change_data(self, new_data):
        self.__data = new_data

    def __str__(self):
        return f"data: {self.__data}, next: {self.next.__data if self.next != None else None}"


class LinkedList:
    def __init__(self, head=None):
        self.head = head
        self.length = 1 if head != None else 0

    def __len__(self):
        return self.length

    def append(self, element):
        cur_element = self.head
        if cur_element == None:
            self.head = Node(element)
            self.length = 1
        else:
            while(cur_element.next != None):
                cur_element = cur_element.next
            cur_element.next = Node(element)
            self.length += 1

    def __str__(self):
        if self.length == 0:
            return "LinkedList[]"
        else:
            result = f"LinkedList[length = {self.length}, ["
            cur = self.head
            while(cur != None):
                result += str(cur)
                cur = cur.next
                if(cur != None):
                    result += "; "
            result += "]]"
        return result

    def pop(self):
        if self.length == 0:
            raise IndexError ("LinkedList is empty!")
        elif self.length == 1:
            self.clear()
        else:
            cur = self.head
            while (cur.next.next != None):
                cur = cur.next
            cur.next = None
            self.length -= 1

    def change_on_end(self, n, new_data):
        if self.length < n or n <= 0:
            raise KeyError("Element doesn't exist!")
        else:
            cur = self.head
            for i in range(self.length - n):
                cur = cur.next
            cur.change_data(new_data)

    def clear(self):
        self.head = None
        self.length = 0