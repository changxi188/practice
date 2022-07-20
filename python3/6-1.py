person ={'first_name':'cheng', 'last_name':'changxi', 'age': 25, 'city':'zhengjiang'}


print(person)

person['first_name'] = 'liu'

print(person['first_name'])


for key, value in person.items():
	print(key + ":" + str(value))

for key in person.keys():
	print(key)


keys = person.keys()

print(keys)


values = person.values()
print(values)


