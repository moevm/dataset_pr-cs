from typing import Any


class Node:
    def __init__(self, data: Any, next=None) -> None:
        self.data = data
        self.next = next

    def get_data(self) -> Any:
        return self.data

    def __str__(self) -> str:
        _next_data = self.next.data if self.next is not None else None
        return f"data: {self.get_data()}, next: {_next_data}"
    
    def change_data(self, new_data):
        self.data = new_data
    


class LinkedList:
    def __init__(self, head=None) -> None:
        self.head = None
        self.length = 0
        
        if head is None:
            return
        
        self.append(head)

    def __len__(self) -> int:
        return self.length

    def append(self, element: Any) -> None:
        if not len(self):
            self.head = Node(element)
            self.length += 1
            return
        
        _node = self.head

        while _node.next != None:
            _node = _node.next
        
        _node.next = Node(element)
        self.length += 1

            
    def __str__(self) -> str: # LinkedList[length = 2, [data: 10, next:20; data: 20, next: None]]
        _res = 'LinkedList['

        if not len(self):
            return _res + ']'

        _res += f"length = {len(self)}, ["

        _node = self.head
        while _node != None:
            _res += str(_node) + '; '
            _node = _node.next
        
        return _res[:-2] + ']]'

    def pop(self) -> None:
        if not len(self):
            raise IndexError("LinkedList is empty!")
        
        if self.head.next is None:
            self.head = None
            self.length = 0
            return

        _node = self.head
        while _node.next.next != None:
            _node = _node.next
        
        _node.next = None
        self.length -= 1

    def change_on_end(self, n: int, new_data) -> None:
        if len(self) < n or n < 1:
            raise KeyError(f"{n} doesn't exist!")
        
        n = len(self) - n
        
        if not n:
            self.head.data = new_data
            return

        _node = self.head
        for _ in range(n):
            _node = _node.next

        _node.data = new_data

    def clear(self) -> None:
        self.head = None
        self.length = 0
