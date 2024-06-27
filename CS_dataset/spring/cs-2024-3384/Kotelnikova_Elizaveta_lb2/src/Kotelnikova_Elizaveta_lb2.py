class Node:
    def __init__(self, data, next=None):
        self.__data = data
        self.next = next

    def get_data(self):
        return self.__data

    def change_data(self, new_data):
        self.__data = new_data

    def __str__(self):
        if self.next:
            return f"data: {self.__data}, next: {self.next.__data}"
        return f"data: {self.__data}, next: None"


class LinkedList:
    def __init__(self, head=None):
        self.__head__ = head
        if (head == None):
            self.__length = 0
        else:
            self.__length = 1

    def __len__(self):
        return self.__length

    def append(self, element):
        n = Node(element)
        hd = self.__head__
        if (hd == None):
            self.__head__ = n
        else:
            while (hd.next != None):
                hd = hd.next
            hd.next = n
        self.__length += 1

    def __str__(self):
        if self.__length == 0:
            return "LinkedList[]"
        else:
            hd = self.__head__
            s=''
            while (hd != None):
                s+=(hd.__str__())
                if (hd.next != None):
                    s+='; '
                else:
                    break
                hd = hd.next
            s = 'LinkedList[length = ' + str(self.__length) + ', [' + s + ']]'
            return s

    def pop(self):
        if (self.__length == 0):
            raise (IndexError("LinkedList is empty!"))
        elif (self.__length == 1):
            self.__head__ = None
            self.__length = 0
        else:
            hd = self.__head__
            while (hd.next != None):
                if (hd.next.next == None):
                    hd.next = None
                else:
                    hd = hd.next
            self.__length-=1

    def change_on_start(self, n, new_data):
        if (self.__length < n or n<=0):
            raise (KeyError("Element doesn't exist!"))
        elif (n == 1):
            hd = self.__head__
            hd.change_data(new_data)
        else:
            hd = self.__head__
            c = 0
            while (c < n-1):
                hd = hd.next
                c += 1
            hd.change_data(new_data)

    def clear(self):
        self.__head__ = None
        self.__length = 0
