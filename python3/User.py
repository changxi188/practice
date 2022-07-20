class User():
	def __init__(self, first_name, last_name):
		self.first_name = first_name
		self.last_name = last_name

	def describe_user(self):
		print("hello")
	
	def greet_user(self):
		print("hello, " + first_name + " " + last_name)


