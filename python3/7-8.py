sandwich_orders =['a', 'd', 'b', 'd', 'c', 'd']

sandwich_orders.reverse()

finished_sandwiches =[]
while sandwich_orders:
	finished_sandwiches.append(sandwich_orders.pop())
	print(finished_sandwiches[-1])


print(finished_sandwiches)


while 'd' in finished_sandwiches:
	finished_sandwiches.remove('d')
print(finished_sandwiches)

dream_place = input("where do you want go : ")
print(dream_place)
