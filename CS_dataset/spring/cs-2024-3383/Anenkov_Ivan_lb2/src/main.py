class Node:
    def __init__(self, data, next=None):
        self.__data = data
        self.next = next

    def get_data(self):
        return self.__data

    def change_data(self, new_data):
        self.__data = new_data

    def __str__(self):
        return f"data: {self.__data}, next: {self.next.__data if self.next else None}"
        
        
class LinkedList:
    def __init__(self, head=None):
        if head == None:
            self.__head__ = head
            self.__length = 0
        else:
            self.__head__ = head
            self.__length = 1

    def __len__(self):
        return self.__length

    def append(self, element):
        node = Node(element)
        tmp = self.__head__
        if tmp == None:
            self.__head__ = node
        else:
            while (tmp.next != None):
                tmp = tmp.next
            tmp.next = node
        self.__length += 1


    def __str__(self):
        if self.__length == 0:
            return "LinkedList[]"
        else:
            res = []
            tmp = self.__head__
            while (tmp != None):
                res.append(tmp.__str__())
                tmp = tmp.next
            return "LinkedList[length = {}, [{}]]".format(self.__length, '; '.join(res))

    def pop(self):
        if self.__length == 0:
            raise (IndexError('LinkedList is empty!'))
        elif self.__length == 1:
            self.__head__ = None
            self.__length = 0
        elif self.__length > 1:
            tmp = self.__head__
            while (tmp.next.next != None):
                tmp = tmp.next
            tmp.next = None
            self.__length -= 1

    def change_on_end(self, n, new_data):
        if self.__length < n or n <= 0:
            raise (KeyError(f"{n} doesn't exist!"))
        else:
            tmp = self.__head__
            cnt = 0
            while cnt != self.__length-n:
                tmp = tmp.next
                cnt += 1
            tmp.change_data(new_data)

    def clear(self):
        self.__head__ = None
        self.__length = 0