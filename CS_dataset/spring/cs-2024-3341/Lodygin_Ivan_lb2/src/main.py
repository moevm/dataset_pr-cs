class Node:
	def __init__(self, data, next=None):
		self.__data = data
		self.next = next
  
	def get_data(self):
		return self.__data

	def __str__(self):
		if(self.next == None): return f"data: {self.__data}, next: None"
		return f"data: {self.__data}, next: {self.next.get_data()}"

	def set_data(self, data):
		self.__data = data

class LinkedList:
	def __init__(self, head=None):
		self.head = head
		self.length = 1 if head else 0

	def __len__(self):
		return self.length

	def append(self, element):
		if self.head is None:
			self.head = Node(element)
		else:
			current = self.head
			while current.next:
				current = current.next
			current.next = Node(element)
		self.length += 1

	def __str__(self):
		if self.length == 0:
			return "LinkedList[]"
		result = f"LinkedList[length = {self.length}, ["
		current = self.head
		while current:
			result += f"data: {current.get_data()}, next: {current.next.get_data() if current.next else None}; "
			current = current.next
		result = result[:-2]
		result += "]]"
		return result

	def pop(self):
		if self.head is None:
			raise IndexError("LinkedList is empty!")
		if self.head.next is None:
			self.head = None
		else:
			current = self.head
			while current.next.next:
				current = current.next
			current.next = None
		self.length -= 1
  
	def delete_on_end(self, n):
		if n > self.length or n <= 0: 
			raise KeyError("Element doesn't exist!") 
		else: 
			current = self.head 
			prev = None 
			for _ in range(self.length - n): 
				prev = current 
				current = current.next 
			if current.next is None: 
				prev.next = None
			else: 
				current.set_data(current.next.get_data())
				current.next = current.next.next
		self.length -= 1
  
	def clear(self):
		self.head = None
		self.length = 0