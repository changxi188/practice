class User():
	def __init__(self, first_name, last_name):
		self.first_name = first_name
		self.last_name = last_name

	def describe_user(self):
		print("hello")
	
	def greet_user(self):
		print("hello, " + first_name + " " + last_name)


class Admin(User):
	def __init__(self, first_name, last_name):
		super().__init__(first_name, last_name)
		self.privileges = Privileges()


class Privileges():
	def __init__(self):
		self.privileges = ['can add post', 'can delete post', 'can ban user']
		
	def show_priviledges(self):
		print(self.privileges)


admin = Admin('cheng', 'xi')

admin.privileges.show_priviledges();
