class Node:
    def __init__(self, data, next=None):
        self.data = data
        self.next = next
        pass

    def get_data(self):
        return self.data
        pass

    def __str__(self):
        if self.next == None:
            return "data: "+str(self.data)+", next: "+str(self.next)
        else:
            return "data: " + str(self.data) + ", next: " + str(self.next.data)
        pass


class LinkedList:
    def __init__(self, head=None):
        if head == None:
            self.head = head
            self.length = 0
        else:
            self.head=head
            self.length = 1
        pass

    def __len__(self):
        return self.length
        pass

    def append(self, element):
        self.length = self.length + 1
        new_node=Node(element)
        if self.head is None:
            self.head = new_node
            return
        current_node=self.head
        while current_node.next:
            current_node = current_node.next
        current_node.next = new_node
        pass

    def __str__(self):
        if self.length == 0:
            return "LinkedList[]"
        pass
        curr = self.head
        ans = "LinkedList[length = "+str(self.length) + ", ["
        first = True
        while curr.next:
            if first:
                ans = ans+"data: " + str(curr.data) + ", next: " + str(curr.next.data) + ";"
                first = False
            else: ans = ans+" data: " + str(curr.data) + ", next: " + str(curr.next.data) + ";"
            curr = curr.next
        if self.length != 1:
            ans = ans+" data: " + str(curr.data) + ", next: " + str(curr.next) + "]]"
        else:
            ans = ans + "data: " + str(curr.data) + ", next: " + str(curr.next) + "]]"
        return ans
        pass

    def pop(self):
        if self.length == 0:
            #print("LinkedList is empty!")
            raise IndexError
        if self.length == 1:
            self.head=None
            self.length = 0
            return
        current_node = self.head
        while (current_node.next.next):
            current_node = current_node.next
        current_node.next = None
        self.length = self.length - 1
        pass

    def delete_on_start(self, n):
        if self.length < n or n <1:
            #print("Element doesn't exist!")
            raise KeyError
        if n == 1:
            self.head = self.head.next
        else:
            current_node = self.head
            pos=0
            while pos+1 != n-1 and current_node.next:
                pos = pos+1
                current_node = current_node.next
            if current_node.next:
                current_node.next = current_node.next.next
        self.length = self.length - 1
        pass

    def clear(self):
        self.head.data = None
        self.head.next = None
        self.length = 0
        pass