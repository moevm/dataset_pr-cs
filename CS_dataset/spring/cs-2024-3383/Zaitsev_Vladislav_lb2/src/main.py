class Node:
    def __init__(self, data, next=None):
        self.data = data
        self.next = next

    def get_data(self):
        return self.data

    def __str__(self):
        return "data: {node_data}, next: {node_next}".format(node_data=self.data, node_next= (self.next and self.next.data))


class LinkedList:
    def __init__(self, head = None):
        self.head = head
        self.leng = 0
        if head != None:
            self.leng += 1
    def __len__(self):
        return self.leng

    def append(self, element):
        new_el = Node(element)
        if len(self) == 0:
            self.head = new_el
        else:
            cur = self.head
            while cur.next != None:
                cur = cur.next
            cur.next = new_el
        self.leng += 1
            
    def __str__(self):
        if self.head == None:
            return "LinkedList[]"
        else:
            cur = self.head
            res = ""
            if cur.next == None:
                res += str(cur) + ']'
            else:
                while cur.next != None:
                    res += str(cur) + "; "
                    cur = cur.next
                res += str(cur) + ']'             
            return  "LinkedList[length = {len}, [{elements}]".format(len = self.__len__(), elements = res)
    def pop(self):
        if self.head == None:
            raise IndexError("LinkedList is empty!")
        elif len(self) == 1:
            self.head = None
        else:
            cur = self.head
            for i in range(0, self.leng - 2):
                cur = cur.next
            cur.next = None
        self.leng -= 1
            
    def delete_on_start(self, n):
        if n > self.leng or n <= 0:
            raise KeyError("Element doesn't exist!")
        else:
            if n == 1 and self.leng >= 2:
                self.head = self.head.next
            elif self.leng == 1:
                self.head = None
            else:
                main_head = self.head
                cur = self.head
                for i in range(0, n - 1):
                    cur = cur.next
                new_next = cur.next
                for i in range(0, n - 2):
                    main_head = main_head.next
                main_head.next = new_next
            self.leng -= 1  
    def clear(self):
        if self.head != None:
            self.head = None
            self.leng = 0