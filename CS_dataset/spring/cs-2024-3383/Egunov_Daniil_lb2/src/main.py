from typing import Generic, Optional, TypeVar

T = TypeVar("T")


class Node(Generic[T]):
    def __init__(self, data: T, next_: Optional["Node[T]"] = None) -> None:
        self.__data = data
        self.__next = next_

    @property
    def next(self) -> Optional["Node[T]"]:
        return self.__next

    @next.setter
    def next(self, new_next: Optional["Node[T]"]) -> None:
        self.__next = new_next

    def get_data(self) -> T:
        return self.__data

    def change_data(self, new_data: T) -> None:
        self.__data = new_data

    def __str__(self) -> str:
        return f"data: {self.__data}, next: {self.next and self.next.get_data()}"


class LinkedList(Generic[T]):
    def __init__(self, head: Optional[Node[T]] = None) -> None:
        self.__head = head
        self.__length = 1 if head else 0

    def __len__(self) -> int:
        return self.__length

    def append(self, element: T) -> None:
        new_node = Node(element)
        if self.__head is None:
            self.__head = new_node
        else:
            cur = self.__head
            while cur.next:
                cur = cur.next
            cur.next = new_node
        self.__length += 1

    def __str__(self) -> str:
        if self.__length == 0:
            return "LinkedList[]"
        nodes = []
        cur = self.__head
        while cur:
            nodes.append(cur)
            cur = cur.next
        nodes_str = "; ".join(
            f"data: {node.get_data()}, next: {node.next and node.next.get_data()}"
            for node in nodes
        )
        return f"LinkedList[length = {self.__length}, [{nodes_str}]]"

    def pop(self) -> T:
        if self.__head is None:
            raise IndexError("LinkedList is empty!")

        if self.__head.next is None:
            data = self.__head.get_data()
            self.__head = None
        else:
            prev = self.__head
            cur = self.__head.next
            while cur.next:
                prev = cur
                cur = cur.next
            data = cur.get_data()
            prev.next = None

        self.__length -= 1
        return data

    def change_on_start(self, n: int, new_data: T) -> None:
        if not (self.__head and 0 < n <= self.__length):
            raise KeyError("Element doesn't exist!")
        cur = self.__head
        for _ in range(n - 1):
            if cur.next is not None:
                cur = cur.next
        cur.change_data(new_data)

    def clear(self) -> None:
        self.__head = None
        self.__length = 0

