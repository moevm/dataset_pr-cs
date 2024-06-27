class Node:
    def __init__(self, data, next=None):
        self.__data = data
        self.next = next

    def get_data(self):
        return self.__data

    def __str__(self):
         return "data: {node_data}, next: {node_next}".format(node_data=self.get_data(), node_next=(self.next.get_data() if self.next else None))


class LinkedList:
    def __init__(self, head = None):
        self.head = head
        self.length = 0
        if head != None:
            self.length = 1

    def __len__(self):
        return self.length

    def append(self, element):
        new_element = Node(element)
        if self.head == None:
            self.head = new_element
        else:
            cur_element = self.head
            while cur_element.next != None:
                cur_element = cur_element.next
            cur_element.next = new_element
        self.length += 1
            
    def __str__(self):
        arr = []
        curr_element = self.head
        if self.head == None:
            return "LinkedList[]"
        else:
            while curr_element != None:
                arr.append(str(curr_element))
                curr_element = curr_element.next
            return f"LinkedList[length = {self.length}, [{'; '.join(arr)}]]"  

    def pop(self):
        if self.head == None:
            raise IndexError("LinkedList is empty")
        if self.head.next == None:
            self.head = None
        else:
            curr_element = self.head
            while curr_element.next != None:
                prev_element = curr_element
                curr_element = curr_element.next
            prev_element.next = None
        self.length -= 1

    def delete_on_start(self, n):
        if n > self.length or n < 1:
            raise KeyError("Element doesn't exist!")
        else:
            if n == 1 and self.head.next != None:
                self.head = self.head.next
            else:
                count = 1
                curr_element = self.head
                while count != n:
                    prev_element = curr_element
                    curr_element = curr_element.next
                    count += 1
                prev_element.next = curr_element.next
            self.length -= 1

    def clear(self):
        self.head = None
        self.length = 0 