class Node:
    def __init__(self, data = None, next_node = None):
        self.data = data
        self.next = next_node
    def get_data(self):
        return self.data
    def __str__(self):
        if self.next is None:
            return f'data: {self.data}, next: {self.next}'
        else:
            return f'data: {self.data}, next: {self.next.get_data()}'

class LinkedList:
    '''Односвязанный список'''
    def __init__(self, head = None):
        if head is None: self.head = head
        else: self.head = Node(head)

    def __len__(self):
        curr_node = self.head
        count_of_elements = 0
        while curr_node is not None:
            count_of_elements += 1
            curr_node = curr_node.next
        return count_of_elements

    def append(self, elem):
        new_node = Node(elem)
        cur_node = self.head
        if cur_node is None:
            self.head = new_node
            return
        while cur_node.next:
            cur_node = cur_node.next
        cur_node.next = new_node
    
    def __str__(self):
        if self.head is None:
            return 'LinkedList[]'
        res_string = ''
        cur_node = self.head
        length = self.__len__()
        while cur_node.next != None:
            res_string += f'data: {cur_node.get_data()}, next: {cur_node.next.data}; '
            cur_node = cur_node.next
        res_string += f'data: {cur_node.get_data()}, next: {None}'
        return f'LinkedList[length = {length}, [' + res_string + ']]'
    
    def pop(self):
        if self.head is None:
            raise IndexError('LinkedList is empty!')
        cur_node = self.head
        prev_node =  None
        while cur_node.next:
            prev_node = cur_node
            cur_node = cur_node.next
        if prev_node is None:
            self.head = None
        else:
            prev_node.next = None
    
    def clear(self):
        self.head =  None
    
    def delete_on_start(self, n: int):
        length = self.__len__()
        if n > length or n < 1:
            raise KeyError("Element doesn't exist!")
        cur_index = 1
        prev_node = None
        cur_node = self.head
        while cur_index < n:
            prev_node = cur_node
            cur_node = cur_node.next
            cur_index += 1
        try:
            prev_node.next = cur_node.next
        except AttributeError:
            self.head = self.head.next