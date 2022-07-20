people_eat = ['cheng', 'li', 'wang', 'zhang']


for person in people_eat:
	print("hello, " + person + " eat together")

print("sorry, " + people_eat[3] + " cannot come here")

people_eat[3] = 'liu'

for person in people_eat:
	print("hello, " + person + " eat together")

print("hello everyone, we have a bigger desktop")

people_eat.insert(0, 'jin')
people_eat.insert(3, 'chen')
people_eat.append('kun')

for person in people_eat:
	print("hello, " + person + " eat together")



print("\n \n \n")
print("sorry everyone , only can invaite two people")

while(len(people_eat) > 2):
	people_eat.pop()


for person in people_eat:
	print("hello, " + person + " you stilll in list")


for i in range(len(people_eat)):
	del people_eat[i - 1]

print(people_eat)
