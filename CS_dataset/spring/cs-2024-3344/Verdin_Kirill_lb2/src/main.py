class Node():
    
	def __init__(self, data, next=None):
		self.__data = data
		self.next = next
  
	def get_data(self):
		return self.__data

	def __str__(self):
		return f"data: {self.get_data()}, next: {self.next.get_data() if self.next else None}"
	
class LinkedList():
    
	def __init__(self, head=None):
		self.head = head
		self.length = 1 if self.head else 0

	def __len__(self):
		return self.length
	
	def append(self, element):
		if self.head:
			current = self.head
			while current.next: current = current.next
			current.next = Node(element)
		else: self.head = Node(element)
		self.length += 1
	
	def __str__(self):
		if not self.head:
			return "LinkedList[]"
		current = self.head
		array = [self.head]
		for i in range(self.length - 1):
			current = current.next
			if current: array.append(current)
		return f"LinkedList[length = {self.length}, [{'; '.join(map(str,array))}]]"
	
	def pop(self):
		if not self.head:
			raise IndexError("LinkedList is empty!")
		elif not self.head.next:
			self.head = None
			self.length -=1
		else:
			current = self.head
			while current.next.next:
				current = current.next
			current.next = None
			self.length -= 1

	def clear(self):
		self.head = None
		self.length = 0
	
	def delete_on_start(self, n):
		if self.length < n or n<=0:
			raise KeyError("Element doesn't exist!")
			return
		elif n == 1:
			self.head = self.head.next
		else:
			current = self.head
			for i in range(n-2):
				current = current.next
			if not current.next.next: current.next = None
			else: current.next = current.next.next
		self.length-=1