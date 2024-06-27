class Node:

    def __init__(self, data, next=None):
        self.data = data
        self.next = next

    def get_data(self):
        return self.data

    def change_daya(self, new_data):
        self.data = new_data

    def __str__(self):
        return "data: {}, next: {}".format(self.data, self.next.data if self.next else self.next)


class LinkedList:
    def __init__(self, head=None):
        if head is None:
            self.head = []
        else:
            self.head = [head]

    def __len__(self):
        return len(self.head)

    def append(self, element):
        new_element = Node(element)
        if len(self.head) != 0:
            self.head[-1].next = new_element
        self.head.append(new_element)

    def __str__(self):
        return "LinkedList[]" if len(self.head) == 0 \
            else ("LinkedList[length = {}, [".format(len(self.head)) +
                  "; ".join(["data: {}, next: {}".format(node.data, node.next.data if node.next else node.next)
                             for node in self.head]) + "]]")

    def pop(self):
        if len(self.head) == 0:
            raise IndexError("LinkedList is empty!")
        else:
            self.head.pop(-1)
        if len(self.head) > 0:
            self.head[-1].next = None

    def clear(self):
        self.head.clear()

    def change_on_end(self, n, new_data):
        if n <= 0 or (n > 0 and n > len(self.head)):
            raise KeyError("Element doesn't exist!")
        else:
            self.head[-n].data = new_data

