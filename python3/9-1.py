class Restaurant():
	def __init__(self, restaurant, cuisine_type):
		self.restaurant = restaurant
		self.cuisine_type = cuisine_type
		self.number_served = 0
		self.login_attempts = 0


	def describe_restaurant(self):
		print("name : " + self.restaurant)
		print("type : " + self.cuisine_type)

	def open_restaurant(self):
		print("open")

	def set_number_served(self, number_served):
		self.number_served = number_served
		print(self.number_served)

	def increment_number_served(self):
		self.number_served += 1
		print(self.number_served)

	def increment_login_attempts(self):
		self.login_attempts += 1
		print(self.login_attempts)
	
	def reset_login_attempts(self):
		self.login_attempts = 0
		print(self.login_attempts)
#
#
#restaurant = Restaurant("aaa", "apple")
#
#restaurant.describe_restaurant()
#restaurant.open_restaurant()
#
#restaurant2 = Restaurant("bbb", "banana")
#restaurant2.describe_restaurant()
#
#res3 = Restaurant("ccc", "chicken")
#res3.set_number_served(100)
#
#res3.increment_number_served()
#
#res3.increment_login_attempts()
#
#res3.increment_login_attempts()
#res3.increment_login_attempts()
#res3.increment_login_attempts()
#
#res3.reset_login_attempts()
#
#

class IceCreamStand(Restaurant):
	def __init__(self, flavors, restaurant, cuisine_type):
		super().__init__(restaurant, cuisine_type)
		self.flavors = flavors
	
	def showIce(self):
		print(self.flavors)

flavors = ['a','b','c']

ice = IceCreamStand(flavors, 'aaa', 'origian')
ice.showIce()	
