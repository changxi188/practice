for i in range(1, 20):
	print(i)


num_list = []

for i in range(1, 1000000):
	num_list.append(i)
	#print(i)

#print(num_list)

print(min(num_list))

print(max(num_list))

print(sum(num_list))

sum1 = 0

for i in range(1, 1000000):
	sum1 += i

print(sum1)



odd_nums = []

for i in range(1, 20, 2):
	print(i)
	odd_nums.append(i)

dev_by_three = []

for i in range(3, 31, 3):
	print(i)
	dev_by_three.append(i)

dev_by_three = [i for i in range(3, 31, 3)]
print(dev_by_three)


cube = [i**3 for i in range(1, 11)]
print(cube)


